#include <iostream>
#include <limits.h>
#include <algorithm>
#include <memory>
#include <assert.h>

#include "CheckersDlg.h"
#include "CheckersView.h"
#include "CheckersBoard.h"
#include "CheckersMove.h"
#include "MyLib.h"
#include "BasicKey.h"

using namespace std;

set<CheckersBoard *> CheckersBoard::mRoster;
CheckersBoard::Rules CheckersBoard::mRules;

Object *CheckersBoard::CreateBoard() {return new CheckersBoard();}

CheckersBoard::Direction CheckersBoard::mDirs[] = {
 {1, -1}, {1, 1}, {-1, -1}, {-1, 1}
};

CheckersBoard::CheckersBoard(void) : mValue(0), mMoveFlg(0), mMovesValid(false) {
   int row, col;
   
   for (row = 0; row < DIM; row++)
      for (col = 0; col < DIM; col++)
         if (row != DIM/2-1 && row != DIM/2 && (row + col) % 2 == 0)
            mBoard[row][col] = PIECE | (row > DIM/2 ? WHITE : 0);
         else
            mBoard[row][col] = NONE;
   
   mRoster.insert(this);
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
   
   mv->mWasKinged = false;
   
   // If moving up a back row piece
   if (IsBackRow(piece, here))
      mValue -= sense * mRules.backWgt;

   step = mv->mSeq[0].row - mv->mSeq[1].row;
   if (step > 1 || step < -1) // Do jumps
      for (itr++; itr != mv->mSeq.end(); itr++) {
         there = *itr;
         assert(InRange(there));

         jmpPiece = mBoard[(here.row + there.row)/2][(here.col + there.col)/2];
         mBoard[(here.row + there.row)/2][(here.col + there.col)/2] = 0;      
         assert(jmpPiece != NONE && (jmpPiece & WHITE) != (piece & WHITE));
         mv->mWereKings.push_back((jmpPiece & KING));

         mValue += sense * (jmpPiece & KING ? mRules.kingWgt : PIECEWGT);
         
         here = there;
      }
   else // Do simple move
      here = mv->mSeq.back();

   // King me
   if (((piece & WHITE) && here.row == 0)
    || (!(piece & WHITE) && here.row == DIM-1)) {
         mValue += sense * (mRules.kingWgt - PIECEWGT);
      piece |= KING;
   }

   mBoard[here.row][here.col] = piece;
   mBoard[original.row][original.col] = 0;

   mMoveFlg ^= WHITE;
   mValue -= 2*sense*mRules.moveWgt;
   mMovesValid = false;
   mMoveHist.push_back(ourMove);
}

void CheckersBoard::UndoLastMove() {
   // FIXME: implement this stub
   throw BaseException("CheckersMove::UndoLastMove is not implemented");
}

void CheckersBoard::GetAllMoves(list<unique_ptr<Move>> *moves) const {
   if (!mMovesValid)
      CalcMoves();
   assert(moves->empty());
   for(auto& m : mMoves) {
      moves->push_back(move(m.Clone()));
   }
}

unique_ptr<Board::Move> CheckersBoard::CreateMove() const {
   return unique_ptr<Move>(new CheckersMove(vector<Loc>()));
}

unique_ptr<Board> CheckersBoard::Clone() const {
   CheckersBoard *rtn = new CheckersBoard(*this);

   return unique_ptr<Board>(rtn);
}

unique_ptr<const Board::Key> CheckersBoard::GetKey() const {
   // FIXME: implement this stub
   throw BaseException("CheckersBoard::GetKey is not implemented");
   return unique_ptr<const Key>(nullptr);
}

void *CheckersBoard::GetOptions() {
   return new Rules(mRules);
}

void CheckersBoard::SetOptions(const void *opts) {
   // FIXME: implement this stub
   throw BaseException("CheckersMove::SetOptions is not implemented");
}

void CheckersBoard::Rules::EndSwap() {
   kingWgt = EndianXfer(kingWgt);
   backWgt = EndianXfer(backWgt);
   moveWgt = EndianXfer(moveWgt);
}

istream &CheckersBoard::Read(istream &is) {
   // FIXME: implement this stub
   throw BaseException("CheckersMove::Read is not implemented");
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

   mValue = mMoveFlg == WHITE ? -mRules.moveWgt : mRules.moveWgt;
   
   for (int row = 0; row < DIM; row++)
      for (int col = 0; col < DIM; col++)
         if ((piece = mBoard[row][col])) {
            mValue += (piece & WHITE ? -1 : 1)
             * (piece & KING ? mRules.kingWgt : PIECEWGT);
            if ((row == 0 && !(piece & WHITE))
             || (row == DIM-1 && (piece & WHITE)))
               mValue += (piece & WHITE ? -1 : 1) * mRules.backWgt;
         }
}

// Precompute all possible moves.  Do not alter any existing code here!!  All
// provided code is correct.  Fill in the move-forward section only.
void CheckersBoard::CalcMoves() const {
   int row, col, forward = mMoveFlg == WHITE ? -1 : 1, numDirs;
   // uint ndx;
   char piece, jumpPiece;
   Loc thisLoc, jumpLoc, toLoc;
   vector<Loc> locs;  // Series of locations moved to
   vector<int> dirs;  // Series of directions moved
   bool upStep;       // Did we just make a new step forward?

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

                  locs.pop_back();           // Pop back to earlier position
                  dirs.pop_back();
                  
                  if (!dirs.empty())         // Advance backtracked dir by one
                     dirs.back()++;
                  upStep = false; 
               }
               else {
                  thisLoc = locs.back();
                  toLoc = Loc(
                   thisLoc.row + 2*forward*mDirs[dirs.back()].rDelta,
                   thisLoc.col + 2*mDirs[dirs.back()].cDelta
                  );

                  /*
                     The move is only valid if:
                        - The destination is valid (in range && not on top of another piece)
                        - The destination is not the spot we just jumped from
                        - The piece we jumped over is the opposite color
                        - The same jump is not already in the move history
                  */
                  if ((InRange(toLoc) && (!mBoard[toLoc.row][toLoc.col]))
                   || ((toLoc.row == row) && (toLoc.col == col))) {  // Piece has moved
                     // Fill in forward-step logic in DFS here.  Should be
                     // 1-2 dozen lines of code

                     // These checks are relatively expensive, and only need to be done for 
                     // king pieces
                     if(piece & KING) {
                        // The destination is the spot we just jumped from
                        if(locs.size() > 1 && *(locs.end()-2) == toLoc) {
                           goto end;
                        }
                        // The jump has already occurred
                        for(auto itr = locs.begin(); itr != locs.end()-1; itr++) {
                           if(thisLoc == *itr && toLoc == *itr) {
                              goto end;
                           }
                        }
                     }

                     jumpLoc = Loc(
                        (thisLoc.row + toLoc.row) / 2,
                        (thisLoc.col + toLoc.col) / 2
                     );
                     jumpPiece = mBoard[jumpLoc.row][jumpLoc.col];
                     if(jumpPiece && (jumpPiece & WHITE) != mMoveFlg) {
                        upStep = true;
                        locs.push_back(move(jumpLoc));
                        dirs.push_back(0);
                     }
                      
                  }
                  end:
                  dirs.back()++;
               }
            }
         }
      }
      
   if (mMoves.size() == 0) // If no capture moves
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
               toLoc = Loc
                  (row + forward*mDirs[ndx].rDelta, col + mDirs[ndx].cDelta);
               if (InRange(toLoc) && mBoard[toLoc.row][toLoc.col] == 0) {
                  locs[1] = toLoc;
                  mMoves.insert(CheckersMove(locs));
               }
            }
         }
      }
   }        

const Class *CheckersBoard::GetClass() const {
   // FIXME: implement this method stub
   throw BaseException("CheckersBoard::GetClass is not implemented");
   return nullptr;
}
