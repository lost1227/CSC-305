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

C4Pop10Board::Rules C4Pop10Board::mRules;

const C4Pop10Board::Dir C4Pop10Board::mDirs[ALL_DIRS]
   = {{1, 1}, {1, -1}, {0, 1}, {1, 0}};

C4Pop10Board::C4Pop10Board()
    : mMoveFlg{0}, mFreeCols{DIM_W}, mValidScores{false} {
   memset(mBoard, 0, sizeof(mBoard));
}

C4Pop10Board::~C4Pop10Board() {
}

int C4Pop10Board::GetValue() const {
   int val;
   if (!mValidScores)
      RecalculateScores();
   val = (mMoveFlg & RED) ? -mRules.moveWght : mRules.moveWght;
   val += mYellowScore.keptDisks * mRules.keptWgt;
   val += mYellowScore.safeDisks * mRules.safeWgt;
   val += mYellowScore.threatDisks * mRules.threatWgt;
   val -= mRedScore.keptDisks * mRules.keptWgt;
   val -= mRedScore.safeDisks * mRules.safeWgt;
   val -= mRedScore.threatDisks * mRules.threatWgt;
   return val;
}

inline int C4Pop10Board::CountCol(int col) const {
   int lookAhead;
   char piece = mBoard[0][col];
   for (lookAhead = 0; lookAhead < DIM_H && mBoard[lookAhead][col] == piece;
        lookAhead++)
      ;
   return lookAhead;
}

void C4Pop10Board::RecalculateScores() const {
   int row, col;
   int curr, lookAhead, count;
   int i;
   char piece;
   int nDir;
   bool redHasSafeRow = false, yellowHasSafeRow = false;
   PlayerScore *currPlayerScore;
   for (auto &val : mBottomRowVal)
      val = C4Pop10Board::PieceVal::UNKNOWN;

   mRedScore.safeDisks = mRedScore.threatDisks = 0;
   mYellowScore.safeDisks = mYellowScore.threatDisks = 0;

   for (curr = 0; curr < DIM_W; curr++) {
      // Check if we've already identified the type
      if (mBottomRowVal[curr] != C4Pop10Board::PieceVal::UNKNOWN)
         continue;
      piece = mBoard[0][curr];
      if (!(piece & PIECE)) {
         mBottomRowVal[curr] = C4Pop10Board::PieceVal::NONE;
         continue;
      }
      // Check for safe discs in a row along the bottom
      for (lookAhead = curr; lookAhead < DIM_W && mBoard[0][lookAhead] == piece;
           lookAhead++)
         ;
      count = lookAhead - curr;
      if (count >= 4) {
         for (i = 0; i < count; i++) {
            mBottomRowVal[curr + i] = C4Pop10Board::PieceVal::SAFE_ROW;
         }
         if (piece & RED)
            redHasSafeRow = true;
         else
            yellowHasSafeRow = true;
         continue;
      }
      // Check for safe discs in a vertical row
      count = CountCol(curr);
      if (count >= 4) {
         mBottomRowVal[curr] = C4Pop10Board::PieceVal::SAFE_COL;
         continue;
      }
      // Check for threat disks
      for (nDir = 0; nDir < DIAG_DIRS
           && mBottomRowVal[curr] == C4Pop10Board::PieceVal::UNKNOWN;
           nDir++) {
         count = 0;
         for (row = 0, col = curr; InRange(0, row, DIM_H)
              && InRange(0, col, DIM_W) && mBoard[row][col] == piece;
              row += mDirs[nDir].dRow, col += mDirs[nDir].dCol)
            count++;
         if (count >= 4) {
            mBottomRowVal[curr] = C4Pop10Board::PieceVal::THREAT;
         }
      }
      // If all checks fail, the piece has no value
      if (mBottomRowVal[curr] == C4Pop10Board::PieceVal::UNKNOWN)
         mBottomRowVal[curr] = C4Pop10Board::PieceVal::NONE;
   }

   for (curr = 0; curr < DIM_W; curr++) {
      assert(mBottomRowVal[curr] != C4Pop10Board::PieceVal::UNKNOWN);
      piece = mBoard[0][curr];
      currPlayerScore = (piece & RED) ? &mRedScore : &mYellowScore;
      if (mBottomRowVal[curr] == C4Pop10Board::PieceVal::SAFE_ROW) {
         currPlayerScore->safeDisks += CountCol(curr);
      } else if (mBottomRowVal[curr] == C4Pop10Board::PieceVal::SAFE_COL) {
         count = CountCol(curr);
         assert(count >= 4);
         currPlayerScore->safeDisks += count - 3;
      } else if (mBottomRowVal[curr] == C4Pop10Board::PieceVal::THREAT) {
         currPlayerScore->threatDisks++;
      }
   }

   if (redHasSafeRow)
      mRedScore.safeDisks -= 3;
   if (yellowHasSafeRow)
      mYellowScore.safeDisks -= 3;
   mValidScores = true;
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
         col = uMove->GetDstCol();
         assert(col < DIM_W);
         assert(!mBoard[DIM_H - 1][col]);
         for (row = DIM_H - 1; row > 0 && !mBoard[row - 1][col]; row--)
            ;
         if (row == DIM_H - 1) {
            uMove->SetDidFillCol(true);
            mFreeCols--;
         }
         mBoard[row][col] = piece;
         break;
      case C4Pop10Move::MoveType::KEEP:
         if (mMoveFlg & RED)
            mRedScore.keptDisks++;
         else
            mYellowScore.keptDisks++;
      case C4Pop10Move::MoveType::TAKE_PLACE:
         col = uMove->GetSrcCol();
         piece = mBoard[0][col];
         assert((piece & PIECE) && ((piece & RED) == mMoveFlg));
         for (row = 1; row < DIM_H && mBoard[row][col]; row++)
            mBoard[row - 1][col] = mBoard[row][col];
         mBoard[row - 1][col] = 0;
         if (uMove->GetType() == C4Pop10Move::MoveType::KEEP) {
            break;
         }
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
   mValidScores = false;
}

void C4Pop10Board::UndoLastMove() {
   int row, col;
   // char piece;
   shared_ptr<const C4Pop10Move> move = mMoveHist.back();
   mMoveHist.pop_back();

   mMoveFlg = (mMoveFlg == RED) ? 0 : RED;

   switch (move->GetType()) {
      case C4Pop10Move::MoveType::PASS:
         break;
      case C4Pop10Move::MoveType::PLACE:
         col = move->GetDstCol();
         for (row = DIM_H - 1; !mBoard[row][col]; row--)
            assert(row >= 0);
         assert((mBoard[row][col] & RED) == mMoveFlg);
         mBoard[row][col] = 0;
         break;
      case C4Pop10Move::MoveType::TAKE_PLACE:
         col = move->GetDstCol();
         for (row = DIM_H - 1; !mBoard[row][col]; row--)
            assert(row >= 0);
         assert((mBoard[row][col] & RED) == mMoveFlg);
         mBoard[row][col] = 0;
      case C4Pop10Move::MoveType::KEEP:
         col = move->GetSrcCol();
         assert(!mBoard[DIM_H - 1][col]);
         for (row = DIM_H - 1; row > 0; row--)
            mBoard[row][col] = mBoard[row - 1][col];
         mBoard[0][col] = PIECE | mMoveFlg;
         if (move->GetType() == C4Pop10Move::MoveType::KEEP) {
            if (mMoveFlg & RED)
               mRedScore.keptDisks--;
            else
               mYellowScore.keptDisks--;
         }
         break;
      default:
         assert(false);
   }

   if (move->GetDidFillCol())
      mFreeCols++;

   mValidScores = false;
}

bool C4Pop10Board::IsPartOf4(int parCol) const {
   int ndir;

   int row, col;
   int currCount, maxCount = 0;

   assert(InRange(0, parCol, DIM_W));

   for (ndir = 0; ndir < ALL_DIRS; ndir++) {
      currCount = 0;
      for (row = 0, col = parCol;
           InRange(0, row, DIM_H) && InRange(0, col, DIM_W) && mBoard[row][col]
           && ((mBoard[row][col] & RED) == mMoveFlg);
           row += mDirs[ndir].dRow, col += mDirs[ndir].dCol)
         ;
      for (row -= mDirs[ndir].dRow, col -= mDirs[ndir].dCol;
           InRange(0, row, DIM_H) && InRange(0, col, DIM_W) && mBoard[row][col]
           && ((mBoard[row][col] & RED) == mMoveFlg);
           row -= mDirs[ndir].dRow, col -= mDirs[ndir].dCol)
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
      // Must pass after keep
      moves->push_back(
         unique_ptr<Move>(new C4Pop10Move(C4Pop10Move::MoveType::PASS)));
   } else if (mFreeCols > 0) {
      // Initial play: Place moves only
      for (col = 0; col < DIM_W; col++) {
         if (!(mBoard[DIM_H - 1][col] & PIECE))
            moves->push_back(unique_ptr<Move>(
               new C4Pop10Move(C4Pop10Move::MoveType::PLACE, -1, col)));
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
   C4Pop10Board *board = new C4Pop10Board(*this);
   return unique_ptr<Board>(board);
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
   return new Rules(mRules);
}

void C4Pop10Board::SetOptions(const void *opts) {
   const Rules *rules = reinterpret_cast<const Rules *>(opts);
   mRules = *rules;
}

const Class *C4Pop10Board::GetClass() const {
   return &mClass;
}

const char C4Pop10Board::GetLoc(int row, int col) const {
   return mBoard[row][col];
}