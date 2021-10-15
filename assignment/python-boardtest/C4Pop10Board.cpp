#include "C4Pop10Board.h"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>

#include "BasicKey.h"
#include "C4Pop10Dlg.h"
#include "C4Pop10View.h"
#include "C4Pop10PyView.h"
#include "MyLib.h"

using namespace std;

const BoardClass C4Pop10Board::mClass("C4Pop10Board", C4Pop10Board::CreateBoard,
 "C4Pop10", &C4Pop10View::mClass, &C4Pop10PyView::mClass, &C4Pop10Dlg::mClass,
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

   if (mRedScore.keptDisks == WIN_DISC_COUNT)
      return -kWinVal;
   if (mYellowScore.keptDisks == WIN_DISC_COUNT)
      return kWinVal;
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
         for (i = 0; i < count; i++)
            mBottomRowVal[curr + i] = C4Pop10Board::PieceVal::SAFE_ROW;
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
       && mBottomRowVal[curr] == C4Pop10Board::PieceVal::UNKNOWN; nDir++) {
         count = 0;
         for (row = 0, col = curr; InRange(0, row, DIM_H)
          && InRange(0, col, DIM_W) && mBoard[row][col] == piece;
          row += mDirs[nDir].dRow, col += mDirs[nDir].dCol)
            count++;
         if (count >= 4)
            mBottomRowVal[curr] = C4Pop10Board::PieceVal::THREAT;
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

   assert(mRedScore.keptDisks < WIN_DISC_COUNT
    && mYellowScore.keptDisks < WIN_DISC_COUNT);

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
   shared_ptr<const C4Pop10Move> move;

   move = mMoveHist.back();
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
   int ndir, row, col, currCount, maxCount = 0;

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
   vector<int> openCols;

   assert(moves->size() == 0);

   if (mRedScore.keptDisks == WIN_DISC_COUNT
    || mYellowScore.keptDisks == WIN_DISC_COUNT) {
      return;
   }

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
               moves->push_back(unique_ptr<Move>(
                new C4Pop10Move(C4Pop10Move::MoveType::TAKE_PLACE, col, col)));
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
   if (moves->empty())
      moves->push_back(
       unique_ptr<Move>(new C4Pop10Move(C4Pop10Move::MoveType::PASS)));
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
   BasicKey<3> *key = new BasicKey<3>;
   int row, col;
   int count = 0;
   unsigned long *curr = key->vals;
   char piece, val;

   *curr = 0;
   for (row = DIM_H - 1; row >= 0; row--) {
      for (col = 0; col < DIM_W; col++) {
         piece = mBoard[row][col];
         if (!(piece & PIECE))
            val = 1;
         else if (piece & RED)
            val = 0;
         else
            val = 2;
         *curr = (*curr << SHIFT_COUNT) | val;
         count++;
         if (count == MAX_CELLS_PER_KEY) {
            count = 0;
            curr++;
            *curr = 0;
         }
      }
   }
   assert(curr == key->vals + 2);
   assert(count < MAX_CELLS_PER_KEY);
   *curr = (*curr << 1) | ((mMoveFlg & RED) ? 0 : 1);

   return unique_ptr<const Board::Key>(key);
}

void C4Pop10Board::Rules::EndSwap() {
   safeWgt = EndianXfer(safeWgt);
   threatWgt = EndianXfer(threatWgt);
   keptWgt = EndianXfer(keptWgt);
   moveWght = EndianXfer(moveWght);
}

istream &C4Pop10Board::Read(istream &is) {
   int row, col;
   int size;
   unsigned short rowBits;
   Rules rules;
   C4Pop10Move *move;

   is.read((char *)&rules, sizeof(Rules));
   rules.EndSwap();
   SetOptions(&rules);

   for (row = 0; row < DIM_H; row++) {
      is.read((char *)&rowBits, sizeof(rowBits));
      rowBits = EndianXfer(rowBits);
      for (col = DIM_W - 1; col >= 0; col--) {
         mBoard[row][col] = rowBits & SHIFT_MASK;
         rowBits = rowBits >> SHIFT_COUNT;
      }
   }

   is.read(&mMoveFlg, sizeof(mMoveFlg));
   is.read(&mFreeCols, sizeof(mFreeCols));
   is.read((char *)&mRedScore, sizeof(mRedScore));
   is.read((char *)&mYellowScore, sizeof(mYellowScore));

   is.read((char *)&size, sizeof(size));
   size = EndianXfer(size);

   assert(size >= 0);
   mMoveHist.clear();
   while (is && size--) {
      move = new C4Pop10Move();
      move->Read(is);
      mMoveHist.push_back(shared_ptr<C4Pop10Move>(move));
   }

   mValidScores = false;

   return is;
}

ostream &C4Pop10Board::Write(ostream &os) const {
   int row, col;
   int size = mMoveHist.size();
   unsigned short rowBits;
   Rules *rules = reinterpret_cast<Rules *>(GetOptions());

   rules->EndSwap();
   os.write((char *)rules, sizeof(Rules));

   for (row = 0; row < DIM_H; row++) {
      for (col = rowBits = 0; col < DIM_W; col++)
         rowBits = (rowBits << SHIFT_COUNT) | (mBoard[row][col] & SHIFT_MASK);
      rowBits = EndianXfer(rowBits);
      os.write((char *)&rowBits, sizeof(rowBits));
   }

   os.write(&mMoveFlg, sizeof(mMoveFlg));
   os.write(&mFreeCols, sizeof(mFreeCols));
   os.write((char *)&mRedScore, sizeof(mRedScore));
   os.write((char *)&mYellowScore, sizeof(mYellowScore));

   size = EndianXfer(size);
   os.write((char *)&size, sizeof(size));
   for (auto &mv : mMoveHist)
      mv->Write(os);

   delete rules;

   return os;
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