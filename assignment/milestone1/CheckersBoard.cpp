#include "CheckersBoard.h"

#include <assert.h>
#include <limits.h>

#include <algorithm>
#include <iostream>
#include <memory>

#include "BasicKey.h"
#include "CheckersDlg.h"
#include "CheckersMove.h"
#include "CheckersView.h"
#include "MyLib.h"

using namespace std;

set<CheckersBoard *> CheckersBoard::mRoster;
CheckersBoard::Rules CheckersBoard::mRules;

BoardClass CheckersBoard::mClass("CheckersBoard", CheckersBoard::CreateBoard,
 "Checkers", &CheckersView::mClass, &CheckersDlg::mClass,
 CheckersBoard::SetOptions, CheckersBoard::GetOptions);

Object *CheckersBoard::CreateBoard() {
   return new CheckersBoard();
}

CheckersBoard::Direction CheckersBoard::mDirs[]
 = {{1, -1}, {1, 1}, {-1, -1}, {-1, 1}};

CheckersBoard::CheckersBoard(void)
 : mValue(0), mMoveFlg(0), mMovesValid(false) {
   int row, col;

   for (row = 0; row < DIM; row++)
      for (col = 0; col < DIM; col++)
         if (row != DIM / 2 - 1 && row != DIM / 2 && (row + col) % 2 == 0)
            mBoard[row][col] = PIECE | (row > DIM / 2 ? WHITE : 0);
         else
            mBoard[row][col] = NONE;

   mRoster.insert(this);

   mValue = (mMoveFlg & WHITE) ? -mRules.moveWgt : mRules.moveWgt;
}

CheckersBoard::~CheckersBoard() {
   mRoster.erase(this);
}

int CheckersBoard::GetValue() const {
   if (!mMovesValid)
      CalcMoves();

   return mMoves.size() > 0 ? mValue : (mMoveFlg == WHITE) ? kWinVal : -kWinVal;
}

void CheckersBoard::ApplyMove(unique_ptr<Move> uMove) {
   shared_ptr<Move> ourMove{move(uMove)};
   shared_ptr<CheckersMove> mv = dynamic_pointer_cast<CheckersMove>(ourMove);
   Loc here, there, original;
   char piece, jmpPiece;
   int step, sense = (mMoveFlg == WHITE ? -1 : 1);

   assert(mv->mSeq.size() > 1);
   auto itr = mv->mSeq.begin();
   original = here = *itr;
   assert(InRange(here));

   piece = mBoard[here.row][here.col];

   assert(piece != NONE && (piece & WHITE) == mMoveFlg);

   assert(mv->mWereKings.empty());

   mv->mWasKinged = false;

   // If moving up a back row piece
   if (IsBackRow(piece, here))
      mValue -= sense * mRules.backWgt;

   step = mv->mSeq[0].row - mv->mSeq[1].row;
   if (step > 1 || step < -1)  // Do jumps
      for (itr++; itr != mv->mSeq.end(); itr++) {
         there = *itr;
         assert(InRange(there));

         jmpPiece
          = mBoard[(here.row + there.row) / 2][(here.col + there.col) / 2];
         mBoard[(here.row + there.row) / 2][(here.col + there.col) / 2] = 0;
         assert(jmpPiece != NONE && (jmpPiece & WHITE) != (piece & WHITE));
         mv->mWereKings.push_back((jmpPiece & KING));

         mValue += sense * (jmpPiece & KING ? mRules.kingWgt : PIECEWGT);

         here = there;
      }
   else  // Do simple move
      here = mv->mSeq.back();

   // King me
   if ((((piece & WHITE) && here.row == 0)
    || (!(piece & WHITE) && here.row == DIM - 1))
    && !(piece & KING)) {
      mValue += sense * (mRules.kingWgt - PIECEWGT);
      piece |= KING;
      mv->mWasKinged = true;
   }

   if (IsBackRow(piece, here))
      mValue += sense * mRules.backWgt;

   mBoard[original.row][original.col] = 0;
   mBoard[here.row][here.col] = piece;

   mMoveFlg ^= WHITE;
   mValue -= 2 * sense * mRules.moveWgt;
   mMovesValid = false;
   mMoveHist.push_back(ourMove);
}

void CheckersBoard::UndoLastMove() {
   int sense;
   Loc movEndPos, movStartPos, jumpPos;
   char piece, jumpedPiece;
   vector<CheckersBoard::Loc>::iterator mvIter, prevMvIter;
   vector<bool>::iterator wereKingsIter;
   shared_ptr<CheckersMove> mv
    = dynamic_pointer_cast<CheckersMove>(mMoveHist.back());
   mMoveHist.pop_back();
   movEndPos = mv->mSeq.back();
   movStartPos = mv->mSeq.front();

   assert(mv->mSeq.size() >= 2);

   mMovesValid = false;

   // Set who's turn it is
   mMoveFlg ^= WHITE;
   sense = (mMoveFlg == WHITE ? -1 : 1);

   // Update the bonus points for it being your turn
   mValue += 2 * sense * mRules.moveWgt;

   piece = mBoard[movEndPos.row][movEndPos.col];
   assert(piece != NONE);
   assert((piece & WHITE) == mMoveFlg);

   if (IsBackRow(piece, movEndPos))
      mValue -= sense * mRules.backWgt;

   // Unking the piece if it was kinged
   if (mv->mWasKinged) {
      assert(piece & KING);
      piece = piece & ~KING;
      mValue -= sense * (mRules.kingWgt - PIECEWGT);
   }

   // Move the piece back
   mBoard[movEndPos.row][movEndPos.col] = NONE;
   mBoard[movStartPos.row][movStartPos.col] = piece;

   prevMvIter = mv->mSeq.begin();
   mvIter = mv->mSeq.begin() + 1;
   wereKingsIter = mv->mWereKings.begin();
   for (; mvIter != mv->mSeq.end(); prevMvIter++, mvIter++) {
      // Check a piece was jumped
      if (abs((*prevMvIter).row - (*mvIter).row) == 2) {
         // Get the jumped piece's location
         jumpPos.row = ((*prevMvIter).row + (*mvIter).row) / 2;
         jumpPos.col = ((*prevMvIter).col + (*mvIter).col) / 2;

         assert(!mBoard[jumpPos.row][jumpPos.col]);

         // Rebuild the jumped piece (color and King?)
         jumpedPiece = PIECE;
         jumpedPiece |= (mMoveFlg & WHITE) ? 0 : WHITE;
         assert(!(wereKingsIter == mv->mWereKings.end()));
         if (*wereKingsIter) {
            jumpedPiece |= KING;
         }
         wereKingsIter++;

         // Restore the jumped piece
         mBoard[jumpPos.row][jumpPos.col] = jumpedPiece;
         mValue -= sense * (jumpedPiece & KING ? mRules.kingWgt : PIECEWGT);
      }
   }

   if (IsBackRow(piece, movStartPos))
      mValue += sense * mRules.backWgt;
}

void CheckersBoard::GetAllMoves(list<unique_ptr<Move>> *moves) const {
   if (!mMovesValid)
      CalcMoves();
   assert(moves->empty());
   for (auto &m : mMoves)
      moves->push_back(move(m.Clone()));
}

unique_ptr<Board::Move> CheckersBoard::CreateMove() const {
   return unique_ptr<Move>(new CheckersMove(vector<Loc>()));
}

unique_ptr<Board> CheckersBoard::Clone() const {
   CheckersBoard *rtn = new CheckersBoard(*this);

   return unique_ptr<Board>(rtn);
}

unique_ptr<const Board::Key> CheckersBoard::GetKey() const {
   BasicKey<KEY_LEN> *key = new BasicKey<KEY_LEN>();
   ulong *dataptr = key->vals;
   char piece;
   int saved = 0;
   int row, col;

   *dataptr = (mMoveFlg == WHITE) ? 1 : 0;
   for (row = DIM - 1; row >= 0; row--) {
      for (col = 0; col < DIM / 2; col++) {
         piece = mBoard[row][(col * 2) + (row % 2)];
         if (saved == 10) {
            saved = 0;
            dataptr++;
            *dataptr = 0;
         }
         *dataptr = (*dataptr << BITS_PER_PIECE) | (piece & 0x7);
         saved++;
      }
   }
   return unique_ptr<const Board::Key>(key);
}

void *CheckersBoard::GetOptions() {
   return new Rules(mRules);
}

void CheckersBoard::SetOptions(const void *opts) {
   const Rules *rOpts = reinterpret_cast<const Rules *>(opts);

   mRules = *rOpts;
   for (auto &board : mRoster) {
      board->NewOptions();
   }
}

void CheckersBoard::Rules::EndSwap() {
   kingWgt = EndianXfer(kingWgt);
   backWgt = EndianXfer(backWgt);
   moveWgt = EndianXfer(moveWgt);
}

istream &CheckersBoard::Read(istream &is) {
   Rules rls;
   int mvCount;
   unique_ptr<CheckersMove> currMove;

   is.read((char *)&rls, sizeof(rls));
   rls.EndSwap();
   SetOptions(&rls);

   is.read((char *)&mvCount, sizeof(mvCount));
   mvCount = EndianXfer(mvCount);
   assert(mvCount >= 0);

   while (!mMoveHist.empty()) {
      UndoLastMove();
   }

   for (int i = 0; i < mvCount; i++) {
      currMove = unique_ptr<CheckersMove>(
       new CheckersMove(vector<CheckersBoard::Loc>()));
      currMove->Read(is);
      ApplyMove(move(currMove));
   }

   return is;
}

ostream &CheckersBoard::Write(ostream &os) const {
   Rules rls = mRules;
   int mvCount = EndianXfer((int)mMoveHist.size());

   rls.EndSwap();
   os.write((char *)&rls, sizeof(rls));

   os.write((char *)&mvCount, sizeof(mvCount));
   for (auto &itr : mMoveHist)
      itr->Write(os);

   return os;
}

void CheckersBoard::NewOptions() {
   list<Move *>::iterator itr;
   char piece;
   int row, col;

   mValue = mMoveFlg == WHITE ? -mRules.moveWgt : mRules.moveWgt;

   for (row = 0; row < DIM; row++)
      for (col = 0; col < DIM; col++)
         if ((piece = mBoard[row][col])) {
            mValue += (piece & WHITE ? -1 : 1)
             * (piece & KING ? mRules.kingWgt : PIECEWGT);
            if ((row == 0 && !(piece & WHITE))
             || (row == DIM - 1 && (piece & WHITE)))
               mValue += (piece & WHITE ? -1 : 1) * mRules.backWgt;
         }
}

/*
A Checkers jump is valid if and only if:
   - The destination is valid (in range && not on top of another piece)
   - The destination is not the spot we just jumped from
   - The piece we jumped over is the opposite color
   - The same jump is not already in the move history
*/
void CheckersBoard::CalcMoves() const {
   int row, col, forward = mMoveFlg == WHITE ? -1 : 1, numDirs;
   char piece, jumpPiece;
   Loc thisLoc, jumpLoc, toLoc;
   vector<Loc> locs;  // Series of locations moved to
   vector<int> dirs;  // Series of directions moved
   bool upStep, isValidMove;  // Did we just make a new step forward?

   mMoves.clear();
   for (row = 0; row < DIM; row++)
      for (col = 0; col < DIM; col++) {
         piece = mBoard[row][col];

         if (piece && (piece & WHITE) == mMoveFlg) {
            locs.clear();
            locs.push_back(Loc(row, col));
            numDirs = piece & KING ? KING_MOVES : PC_MOVES;
            dirs.push_back(0);
            upStep = false;

            // Run a DFS exploring all possible jump moves.
            while (!locs.empty()) {
               if (dirs.back() == numDirs) {  // If we've explored all dirs
                  if (upStep)
                     mMoves.insert(locs);

                  locs.pop_back();  // Pop back to earlier position
                  dirs.pop_back();

                  if (!dirs.empty())  // Advance backtracked dir by one
                     dirs.back()++;
                  upStep = false;
               } else {
                  thisLoc = locs.back();
                  toLoc
                   = Loc(thisLoc.row + 2 * forward * mDirs[dirs.back()].rDelta,
                   thisLoc.col + 2 * mDirs[dirs.back()].cDelta);

                  isValidMove = true;
                  isValidMove = isValidMove && InRange(toLoc)
                   && (!mBoard[toLoc.row][toLoc.col]);
                  isValidMove
                   = isValidMove || ((toLoc.row == row) && (toLoc.col == col));
                  // These checks are relatively expensive, and only need to be
                  // done for king pieces
                  if (piece & KING) { 
                     // The destination can't be the spot we just jumped from
                     isValidMove = isValidMove
                      && !(locs.size() > 1 && *(locs.end() - 2) == toLoc);
                     // The jump has already occurred
                     for (auto itr = locs.begin(); itr != locs.end(); itr++) {
                        if (thisLoc == *itr) {
                           if (itr != locs.begin() && *(itr - 1) == toLoc) {
                              isValidMove = false;
                              break;
                           }
                           if (itr != (locs.end() - 1) && *(itr + 1) == toLoc) {
                              isValidMove = false;
                              break;
                           }
                        }
                     }
                  }
                  if (isValidMove) {
                     jumpLoc = Loc((thisLoc.row + toLoc.row) / 2,
                      (thisLoc.col + toLoc.col) / 2);
                     jumpPiece = mBoard[jumpLoc.row][jumpLoc.col];
                     if (jumpPiece && (jumpPiece & WHITE) != mMoveFlg) {
                        upStep = true;
                        locs.push_back(move(toLoc));
                        dirs.push_back(0);
                        continue;
                     }
                  }
                  dirs.back()++;
               }
            }
         }
      }

   if (mMoves.size() == 0)  // If no capture moves
      FindNormalMoves();

   mMovesValid = true;
}

// Find non-jumping moves
void CheckersBoard::FindNormalMoves() const {
   vector<Loc> locs = vector<Loc>(2);
   int piece, row, col, ndx, forward = mMoveFlg == WHITE ? -1 : 1, numDirs;
   Loc toLoc;

   for (row = 0; row < DIM; row++)
      for (col = 0; col < DIM; col++) {
         piece = mBoard[row][col];

         if (piece && (piece & WHITE) == mMoveFlg) {
            numDirs = piece & KING ? KING_MOVES : PC_MOVES;
            locs[0] = Loc(row, col);
            for (ndx = 0; ndx < numDirs; ndx++) {
               toLoc = Loc(
                row + forward * mDirs[ndx].rDelta, col + mDirs[ndx].cDelta);
               if (InRange(toLoc) && mBoard[toLoc.row][toLoc.col] == 0) {
                  locs[1] = toLoc;
                  mMoves.insert(CheckersMove(locs));
               }
            }
         }
      }
}

const Class *CheckersBoard::GetClass() const {
   return &mClass;
}
