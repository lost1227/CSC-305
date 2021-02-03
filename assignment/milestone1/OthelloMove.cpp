#include "MyLib.h"
#include "OthelloMove.h"
#include "OthelloBoard.h"
#include <regex>

using namespace std;

vector<OthelloMove *> OthelloMove::mFreeList;

void *OthelloMove::operator new(size_t sz) {
   void *temp;

   if (mFreeList.size()) {
      temp = mFreeList.back();
   } 
   else {
      temp = ::new char[sz];
   }

   mOutstanding++;
   return temp;
}

void OthelloMove::operator delete(void *p) {
   mFreeList.push_back((OthelloMove *)p);

   mOutstanding--;
}

bool OthelloMove::operator==(const Board::Move &rhs) const {
   const OthelloMove &oRhs = dynamic_cast<const OthelloMove &>(rhs);

   return mRow == oRhs.mRow && mCol == oRhs.mCol;
}

bool OthelloMove::operator<(const Board::Move &rhs) const {
   const OthelloMove &oRhs = dynamic_cast<const OthelloMove &>(rhs);

   return mRow < oRhs.mRow || mCol < oRhs.mCol;
}

OthelloMove::operator string() const {
   return mRow == -1 && mCol == -1 ? "Pass" : FString("[%d, %d]", mRow, mCol);
}

void OthelloMove::operator=(const string &src) {
   // regex reOth("^ *((Pass)|\\[ *(\\d+), *(\\d+) *\\]) *$"); No raw string
   regex reOth(R"(^ *((Pass)|\[ *(\d+), *(\d+) *\]) *$)");

   const int kPassPtn = 2, kRowPtn = 3, kColPtn = 4; // RE Pattern indexes
   smatch reRes;
   int tRow = -1, tCol = -1;  // Assume a "pass"

   if (regex_search(src, reRes, reOth)) {
      if (reRes[kPassPtn].length() == 0) {  // If not pass
         tRow = stoi(reRes[kRowPtn]);
         tCol = stoi(reRes[kColPtn]);

         if (!InRange<short>(0, tRow, OthelloBoard::dim+1)
          || !InRange<short>(0, tCol, OthelloBoard::dim+1))
            throw BaseException(FString("Out of bounds Othello move: %s",
             src.c_str()));
      }
   }
   else 
      throw BaseException(FString("Bad Othello move: %s", src.c_str()));
   
   mRow = (char)tRow;
   mCol = (char)tCol;
}

unique_ptr<Board::Move> OthelloMove::Clone() const {
   return unique_ptr<Move>{new OthelloMove(this)};
}

istream &OthelloMove::Read(istream &is) {
   char size, count, dirNum;
   
   mFlipSets.clear();
   is.read(&mRow, sizeof(mRow));
   is.read(&mCol, sizeof(mCol));
   is.read(&size, sizeof(size));
   while (--size) {
      is.read(&count, sizeof(count)).read(&dirNum, sizeof(dirNum));
      mFlipSets.push_back(
       FlipSet(count, OthelloBoard::mDirs + dirNum));
   }
      
   return is;
}

ostream &OthelloMove::Write(ostream &os) const {
   char count, dirNum, size = mFlipSets.size();
   FlipList::const_iterator itr;

   os.write(&mRow, sizeof(mRow));
   os.write(&mCol, sizeof(mCol));
   os.write(&size, sizeof(size));

   for (itr = mFlipSets.begin(); itr != mFlipSets.end(); itr++) {
      dirNum = (*itr).dir - OthelloBoard::mDirs;
      count = (*itr).count;
      os.write(&count, sizeof(count)).write(&dirNum, sizeof(dirNum));
   }

   return os;
}
