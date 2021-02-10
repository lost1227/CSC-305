#include <assert.h>
#include <memory.h>
#include "OthelloDlg.h"
#include "OthelloView.h"
#include "OthelloBoard.h"
#include "OthelloMove.h"
#include "MyLib.h"
#include "BasicKey.h"


////////////////////////////////////////////////////////////////////////////////
using namespace std;

BoardClass OthelloBoard::mClass(
   "OthelloBoard",
   OthelloBoard::CreateBoard,
   "Othello",
   &OthelloView::mClass,
   &OthelloDlg::mClass,
   OthelloBoard::SetOptions,
   OthelloBoard::GetOptions
);

short OthelloBoard::mWeights[dim][dim] = {
   {16, 0, 8, 8, 8, 8, 0, 16},
   { 0, 0, 0, 0, 0, 0, 0,  0},
   { 8, 0, 1, 1, 1, 1, 0,  8},
   { 8, 0, 1, 1, 1, 1, 0,  8},
   { 8, 0, 1, 1, 1, 1, 0,  8},
   { 8, 0, 1, 1, 1, 1, 0,  8},
   { 0, 0, 0, 0, 0, 0, 0,  0},
   {16, 0, 8, 8, 8, 8, 0, 16} 
};



// Directions are row, column
OthelloBoard::Direction OthelloBoard::mDirs[numDirs] = {
   {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}
};

const Class *OthelloBoard::GetClass() const {
   return &mClass;
} 

// This is a definition. It doesn't look like it, but this is calling the default constructor
set<OthelloBoard *> OthelloBoard::mRoster {};

Object *OthelloBoard::CreateBoard() {return new OthelloBoard();}

OthelloBoard::OthelloBoard() : mNextMove(mBPiece), mPassCount(0), mWeight(0) {
   int row, col;

   for (row = 0; row < dim; row++)
      for (col = 0; col < dim; col++)
         mBoard[row][col] = 0;

   mBoard[dim/2-1][dim/2-1] = mBoard[dim/2][dim/2] = mWPiece;
   mBoard[dim/2-1][dim/2] = mBoard[dim/2][dim/2-1] = mBPiece;
   mRoster.insert(this);
}

OthelloBoard::~OthelloBoard() {
   mRoster.erase(this);
}

int OthelloBoard::GetValue() const {
   int row, col, total = 0;

   if (mPassCount < 2)  // Game not over
      return mWeight;
   else {               // Game over
      for (row = 0; row < dim; row++)
         for (col = 0; col < dim; col++)
            total += mBoard[row][col];

      return total > 0 ? kWinVal : total < 0 ? -kWinVal : 0;
   }
}

void OthelloBoard::ApplyMove(unique_ptr<Move> uMove) {
   shared_ptr<Move> ourMove{move(uMove)};      // Take ownership
   shared_ptr<OthelloMove> om = dynamic_pointer_cast<OthelloMove>(ourMove);
   int dNdx, row, col, switched;
   Direction *dir;

   if (om->IsPass()) {
      mPassCount++;
   }
   else {
      assert(mBoard[om->mRow][om->mCol] == 0);

      mPassCount = 0;
      mBoard[om->mRow][om->mCol] = mNextMove;
      mWeight += mNextMove * mWeights[om->mRow][om->mCol];

      // Repeat considering each cardinal direction
      for (dNdx = 0; dNdx < numDirs; dNdx++) {
         dir = mDirs + dNdx;
         row = om->mRow;
         col = om->mCol;

         // Walk from the new disc location outwards in the direction under consideration
         // Keep walking so long as we encounter tiles of the opposite color
         do {
            row += dir->rDelta;
            col += dir->cDelta;
         } while (InBounds(row, col) && mBoard[row][col] == -mNextMove);
         
         // Walk back towards the move location, flipping tiles as necesary
         // Keep track of how many tiles were flipped
         if (InBounds(row, col) && mBoard[row][col] == mNextMove) {
            if(row != om->mRow || col != om->mCol)
               row -= dir->rDelta, col -= dir->cDelta;
            switched = 0;
            while(row != om->mRow || col != om->mCol) {
               mBoard[row][col] = mNextMove;
               mWeight += mNextMove * mWeights[row][col] * 2;
               switched++;
               row -= dir->rDelta, col -= dir->cDelta;
            }
            if (switched > 0)
               om->AddFlipSet(OthelloMove::FlipSet(switched, dir));
         }
      }
      assert(om->GetFlipSets().size() > 0);
   }
   mMoveHist.push_back(ourMove);
   mNextMove = -mNextMove;
}

void OthelloBoard::UndoLastMove() {
   assert(mMoveHist.size() > 0);
   shared_ptr<OthelloMove> om = dynamic_pointer_cast<OthelloMove>(mMoveHist.back());
   int baseRow = om->mRow, baseCol = om->mCol;
   int row, col, flip;
   OthelloMove::FlipSet flipSet;
   OthelloMove::FlipList::iterator itr;

   mMoveHist.pop_back();

   if (om->IsPass())
      mPassCount--;
   else {
      mBoard[baseRow][baseCol] = 0;
      mWeight += mNextMove * mWeights[baseRow][baseCol];
      for (itr = om->mFlipSets.begin(); itr != om->mFlipSets.end(); itr++) {
         flipSet = *itr;
         row = baseRow + flipSet.dir->rDelta;
         col = baseCol + flipSet.dir->cDelta;
         for (flip = 0; flip < flipSet.count; flip++) {
            mBoard[row][col] = mNextMove;
            mWeight += 2*mNextMove*mWeights[row][col];
            row += flipSet.dir->rDelta;
            col += flipSet.dir->cDelta;
         }
      }
   }

   mNextMove = -mNextMove;
}

void OthelloBoard::GetAllMoves(list<unique_ptr<Move>> *moves) const {
   int testRow, testCol, row, col, dNdx, steps;
   Direction *dir;

   assert(moves->size() == 0);

   // If the game is over, there are no moves available
   if(mPassCount == 2)
      return;

   for (row = 0; row < dim; row++)
      for (col = 0; col < dim; col++) {
         if (mBoard[row][col] != 0)
            continue;

         for (dNdx = 0; dNdx < numDirs; dNdx++) {
            dir = mDirs + dNdx;
            testRow = row;
            testCol = col;
            steps = 0;
            do {
               testRow += dir->rDelta;
               testCol += dir->cDelta;
               steps++;
            } while (InBounds(testRow, testCol)
             && mBoard[testRow][testCol] == -mNextMove);
      
            if (InBounds(testRow, testCol)
             && mBoard[testRow][testCol] == mNextMove && steps > 1) {
               moves->push_back(unique_ptr<Move>{new OthelloMove(row, col)});
               break;
            }
         }
      }

   if (moves->size() == 0)
      moves->push_back(unique_ptr<Move>{new OthelloMove(-1, -1)});
}

unique_ptr<Board::Move> OthelloBoard::CreateMove() const {
   return unique_ptr<Move>{new OthelloMove(0, 0)};
}

unique_ptr<Board> OthelloBoard::Clone() const {
   OthelloBoard *rtn = new OthelloBoard(*this);

   return unique_ptr<Board>(rtn);
}

unique_ptr<const Board::Key> OthelloBoard::GetKey() const {
   BasicKey<5> *rtn = new BasicKey<5>();
   int row, col;
   ulong *vals = rtn->vals;

   for (row = 0; row < dim; row++)
      for (col = 0; col < dim; col++)
         vals[row/2] = (vals[row/2] << sqrShift) | (mBoard[row][col] + 1);

   vals[row/2] = 0;
   vals[row/2] |= mNextMove + 1;

   return unique_ptr<const Board::Key>(rtn);
}

istream &OthelloBoard::Read(istream &is) {
   int row, col;
   unsigned char size = 0;
   unsigned short rowBits;
   OthelloMove *move;
   Rules temp;

   mMoveHist.clear();
   mWeight = 0;

   is.read((char *)&temp, sizeof(Rules));
   temp.cornerWgt = EndianXfer(temp.cornerWgt);
   temp.sideWgt = EndianXfer(temp.sideWgt);
   temp.nearSideWgt = EndianXfer(temp.nearSideWgt);
   temp.innerWgt = EndianXfer(temp.innerWgt);

   for (row = 0; row < dim; row++) {
      is.read((char *)&rowBits, sizeof(rowBits));
      rowBits = EndianXfer(rowBits);
      for (col = dim-1; col >= 0; col--) {
         mBoard[row][col] = rowBits & sqrMask;
         rowBits >>= sqrShift;
         if (mBoard[row][col] == (mWPiece & sqrMask)) // If cell was -1 (mWPiece)
            mBoard[row][col] = mWPiece;               // .. restore all bits
      }
   }

   SetOptions(&temp);

   is.read(&mNextMove, sizeof(mNextMove));
   is.read(&mPassCount, sizeof(mPassCount));

   is.read((char *)&size, sizeof(size));

   RecalcWeight();
   while (is && size--) {
      move = new OthelloMove();
      move->Read(is);
      mMoveHist.push_back(shared_ptr<OthelloMove>(move));
   }
   
   return is;
}

ostream &OthelloBoard::Write(ostream &os) const {
   int row, col; 
   unsigned char sz = mMoveHist.size();
   unsigned short rowBits;
   Rules *rls = reinterpret_cast<Rules *>(GetOptions());

   rls->cornerWgt = EndianXfer(rls->cornerWgt);
   rls->sideWgt = EndianXfer(rls->sideWgt);
   rls->nearSideWgt = EndianXfer(rls->nearSideWgt);
   rls->innerWgt = EndianXfer(rls->innerWgt);
   os.write((char *)rls, sizeof(Rules));

   for (row = 0; row < dim; row++) {
      for (col = rowBits = 0; col < dim; col++)
         rowBits = (rowBits << sqrShift) | (mBoard[row][col] & sqrMask);
      rowBits = EndianXfer(rowBits);
      os.write((char *)&rowBits, sizeof(rowBits));
   }

   os.write(&mNextMove, sizeof(mNextMove));
   os.write(&mPassCount, sizeof(mPassCount));

   os.write((char *)&sz, sizeof(sz));
   for (auto itr = mMoveHist.begin(); itr != mMoveHist.end(); itr++)
      (*itr)->Write(os);

   delete rls;
   
   return os;
}

void OthelloBoard::RecalcWeight() {
   int row, col;

   mWeight = 0;

   for (row = 0; row < dim; row++)
      for (col = 0; col < dim; col++)
         mWeight += mBoard[row][col] * mWeights[row][col];
}

void *OthelloBoard::GetOptions() {
   Rules *rtn = new Rules;
   
   rtn->cornerWgt = mWeights[0][0];
   rtn->sideWgt = mWeights[0][2];
   rtn->nearSideWgt = mWeights[1][1];
   rtn->innerWgt = mWeights[2][2];

   return rtn;
}

void OthelloBoard::SetOptions(const void *data) {
   const Rules *rules = reinterpret_cast<const Rules *>(data);
   int row, col;
   set<OthelloBoard *>::iterator itr;

   for (row = 0; row < dim; row++) {
      for (col = 0; col < dim; col++)
         if (row == 1 || col == 1 || row == dim-2 || col == dim-2)
            mWeights[row][col] = rules->nearSideWgt;
         else if (row == 0 || col == 0 || row == dim-1 || col == dim-1)
            mWeights[row][col] = rules->sideWgt;
         else
            mWeights[row][col] = rules->innerWgt;

   }
   mWeights[0][0] = mWeights[0][dim-1] = mWeights[dim-1][0]
    = mWeights[dim-1][dim-1] = rules->cornerWgt;

   for (itr = mRoster.begin(); itr != mRoster.end(); itr++)
      (*itr)->RecalcWeight();
}
