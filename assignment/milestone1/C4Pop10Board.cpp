#include "C4Pop10Board.h"

#include <algorithm>
#include <cassert>
#include <cstring>

#include "C4Pop10Dlg.h"
#include "C4Pop10View.h"
#include "MyLib.h"

using namespace std;

const BoardClass C4Pop10Board::mClass("C4Pop10Board", C4Pop10Board::CreateBoard,
   "C4Pop10", &C4Pop10View::mClass, &C4Pop10Dlg::mClass,
   C4Pop10Board::SetOptions, C4Pop10Board::GetOptions);

const int C4Pop10Board::mDirs[NUM_DIRS][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}};

C4Pop10Board::C4Pop10Board(): mMoveFlg{0}, mFreeCols{DIM_W} {
   memset(mBoard, 0, sizeof(mBoard));
}

C4Pop10Board::~C4Pop10Board() {
}

int C4Pop10Board::GetValue() const {
   throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

void C4Pop10Board::ApplyMove(unique_ptr<Move> move) {
   shared_ptr<Move> ourMove{::move(move)};
   shared_ptr<C4Pop10Move> uMove = dynamic_pointer_cast<C4Pop10Move>(ourMove);

   char piece;
   int row, col;

   switch (uMove->GetType()) {
      case C4Pop10Move::MoveType::PASS:
         break;
      case C4Pop10Move::MoveType::PLACE:
         piece = PIECE | mMoveFlg;
         col = uMove->GetSrcCol();
         assert(col < DIM_W);
         assert(!mBoard[DIM_H - 1][col]);
         for (row = DIM_H - 1; row > 0 && !mBoard[row - 1][col]; row--)
            ;
         if (row == DIM_H - 1)
            mFreeCols--;
         mBoard[row][col] = piece;
         break;
      case C4Pop10Move::MoveType::KEEP:
      case C4Pop10Move::MoveType::TAKE_PLACE:
         col = uMove->GetSrcCol();
         piece = mBoard[0][col];
         assert((piece & PIECE) && ((piece & RED) == mMoveFlg));
         for (row = 1; row < DIM_H && mBoard[row][col]; row++)
            mBoard[row - 1][col] = mBoard[row][col];
         mBoard[DIM_H - 1][col] = 0;
         if (uMove->GetType() == C4Pop10Move::MoveType::KEEP) {
            break;
         }
         col = uMove->GetSrcCol();
         piece = mBoard[0][col];
         assert((piece & PIECE) && ((piece & RED) == mMoveFlg));
         for (row = 1; row < DIM_H && mBoard[row][col]; row++)
            mBoard[row - 1][col] = mBoard[row][col];
         mBoard[DIM_H - 1][col] = 0;
         col = uMove->GetDstCol();
         assert(mBoard[DIM_H - 1][col] == 0);
         for (row = DIM_H - 2; row >= 0 && !mBoard[row][col]; row--)
            ;
         mBoard[row + 1][col] = piece;
         break;
      default:
         assert(false);
   }

   mMoveHist.push_back(uMove);
   mMoveFlg = (mMoveFlg == RED) ? 0 : RED;
}

void C4Pop10Board::UndoLastMove() {
   throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

bool C4Pop10Board::IsPartOf4(int parCol) const {
   int ndir;

   int row, col;
   int currCount, maxCount = 0;

   assert(InRange(0, parCol, DIM_W));

   for (ndir = 0; ndir < NUM_DIRS; ndir++) {
      currCount = 0;
      for (row = 0, col = parCol; InRange(0, row, DIM_H)
           && InRange(0, col, DIM_W) && ((mBoard[row][col] & RED) == mMoveFlg);
           row += mDirs[ndir][0], col += mDirs[ndir][1])
         ;
      for (row -= mDirs[ndir][0], col -= mDirs[ndir][1]; InRange(0, row, DIM_H)
           && InRange(0, col, DIM_W) && ((mBoard[row][col] & RED) == mMoveFlg);
           row -= mDirs[ndir][0], col -= mDirs[ndir][1])
         currCount++;
      maxCount = max(maxCount, currCount);
   }
   return maxCount >= 4;
}

void C4Pop10Board::GetAllMoves(list<unique_ptr<Move>> *moves) const {
   int col;
   char piece;
   bool kept[DIM_W];
   assert(moves->size() == 0);

   vector<int> openCols;

   if (mMoveHist.size() > 0
      && mMoveHist.back()->GetType() == C4Pop10Move::MoveType::KEEP) {
      moves->push_back(
         unique_ptr<Move>(new C4Pop10Move(C4Pop10Move::MoveType::PASS)));
   } else if (mFreeCols > 0) {
      // Initial play: Place moves only
      for (col = 0; col < DIM_W; col++) {
         if (!(mBoard[DIM_H - 1][col] & PIECE))
            moves->push_back(unique_ptr<Move>(
               new C4Pop10Move(C4Pop10Move::MoveType::PLACE, col)));
      }
   } else {
      openCols.clear();
      for (col = 0; col < DIM_W; col++) {
         piece = mBoard[DIM_H - 1][col];
         if (!(piece & PIECE))
            openCols.push_back(col);
      }
      for (col = 0; col < DIM_W; col++) {
         kept[col] = false;
         piece = mBoard[0][col];
         if ((piece & PIECE) && (piece & RED) == mMoveFlg
            && (kept[col] = IsPartOf4(col))) {
            moves->push_back(unique_ptr<Move>(
               new C4Pop10Move(C4Pop10Move::MoveType::KEEP, col)));
         }
      }
      for (col = 0; col < DIM_W; col++) {
         piece = mBoard[0][col];
         if ((piece & PIECE) && (piece & RED) == mMoveFlg && !kept[col]) {
            if (openCols.size() == 0) {
               moves->push_back(unique_ptr<Move>(new C4Pop10Move(
                  C4Pop10Move::MoveType::TAKE_PLACE, col, col)));
            } else if (openCols.size() == 1) {
               moves->push_back(unique_ptr<Move>(new C4Pop10Move(
                  C4Pop10Move::MoveType::TAKE_PLACE, col, openCols.front())));
            } else {
               for (auto &toCol : openCols) {
                  if (toCol != col)
                     moves->push_back(unique_ptr<Move>(new C4Pop10Move(
                        C4Pop10Move::MoveType::TAKE_PLACE, col, toCol)));
               }
            }
         }
      }
   }
}

unique_ptr<Board::Move> C4Pop10Board::CreateMove() const {
   return unique_ptr<Board::Move>(new C4Pop10Move());
}

int C4Pop10Board::GetWhoseMove() const {
   return (mMoveFlg & RED) ? 1 : 0;
}

const list<shared_ptr<const Board::Move>> &C4Pop10Board::GetMoveHist() const {
   return *(std::list<std::shared_ptr<const Move>> *)(&mMoveHist);
}

unique_ptr<Board> C4Pop10Board::Clone() const {
   throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

unique_ptr<const Board::Key> C4Pop10Board::GetKey() const {
   throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

istream &C4Pop10Board::Read(istream &in) {
   throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

ostream &C4Pop10Board::Write(ostream &out) const {
   throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

Object *C4Pop10Board::CreateBoard() {
   return new C4Pop10Board;
}

void *C4Pop10Board::GetOptions() {
   throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

void C4Pop10Board::SetOptions(const void *opts) {
   throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

const Class *C4Pop10Board::GetClass() const {
   return &mClass;
}

const char C4Pop10Board::GetLoc(int row, int col) const {
   return mBoard[row][col];
}