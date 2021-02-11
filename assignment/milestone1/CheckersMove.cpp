#include <regex>
#include <ctype.h>
#include "MyLib.h"
#include "CheckersMove.h"
#include "CheckersBoard.h"

using namespace std;

vector<unique_ptr<CheckersMove, FreeListDeleter>> CheckersMove::mFreeList;

void *CheckersMove::operator new(size_t sz) {
   void *temp;

   if (mFreeList.size()) {
      temp = (void *) mFreeList.back().release();
      mFreeList.pop_back();
   } 
   else {
      temp = ::new char[sz];
   }

   mOutstanding++;
   return temp;
}

void CheckersMove::operator delete(void *p) {
   unique_ptr<CheckersMove, FreeListDeleter> ptr((CheckersMove *)p, FreeListDeleter());
   mFreeList.push_back(move(ptr));

   mOutstanding--;
}

CheckersMove::CheckersMove(const vector<CheckersBoard::Loc> &seq)
 : mSeq(seq), mWasKinged(false) {
}

bool CheckersMove::operator==(const Board::Move &rhs) const {
   const CheckersMove &oRhs = dynamic_cast<const CheckersMove &>(rhs);
   vector<CheckersBoard::Loc>::const_iterator itr1, itr2;
   
   for (itr1 = mSeq.begin(), itr2 = oRhs.mSeq.begin(); 
    itr1 != mSeq.end() && itr2 != oRhs.mSeq.end() && *itr1 == *itr2;
    itr1++, itr2++)
      ;
   
   return itr1 == mSeq.end() && itr2 == oRhs.mSeq.end();
}

bool CheckersMove::operator<(const Board::Move &rhs) const {
   const CheckersMove &oRhs = dynamic_cast<const CheckersMove &>(rhs);
   vector<CheckersBoard::Loc>::const_iterator itr1, itr2;
   for(itr1 = mSeq.begin(), itr2 = oRhs.mSeq.begin();
    itr1 != mSeq.end() && itr2 != oRhs.mSeq.end() && *itr1 == *itr2;
    itr1++, itr2++)
      ;
   return (itr1 == mSeq.end() && itr2 != oRhs.mSeq.end())
      || (itr1 != mSeq.end() && itr2 != oRhs.mSeq.end() && *itr1 < *itr2);
}

CheckersMove::operator string() const {
   string rtn;
   vector<CheckersBoard::Loc>::const_iterator itr;
   
   itr = mSeq.begin();
   if (itr != mSeq.end()) {
      rtn = FString("%c%d", (*itr).row + 'A', (*itr).col + 1);
      for (itr++; itr != mSeq.end(); itr++)
         rtn += FString(" -> %c%d", (*itr).row + 'A', (*itr).col + 1);
   }

   return rtn;
}

void CheckersMove::operator=(const string &src) {
   static regex wholeStrCheck(R"(^\s*[A-Za-z]\s*[0-9]+(?:\s*->\s*[A-Za-z]\s*[0-9]+)+\s*$)");
   static regex parser(R"(([A-Za-z])\s*([0-9]+))");
   string curr;
   smatch matches;
   vector<CheckersBoard::Loc> seq;
   regex_iterator<string::const_iterator> itr(src.begin(), src.end(), parser);
   regex_iterator<string::const_iterator> end;

   if(!regex_match(src, wholeStrCheck)) {
      throw BaseException("Bad Checkers move: " + src);
   }

   for(;itr != end; itr++) {
      curr = (*itr).str();
      regex_match(curr, matches, parser);

      short row = toupper(matches[1].str()[0]) - 'A';
      short col = stoi(matches[2]) - 1;
      if(!InRange(0, (int)row, CheckersBoard::DIM) || !InRange(0, (int)col, CheckersBoard::DIM)) {
         throw BaseException("Out of bounds Checkers move: " + src);
      }
      seq.push_back(CheckersBoard::Loc(row, col));
   }

   assert(seq.size() >= 2); // Invalid moves should be caught by the wholeStrCheck

   mSeq = seq;
}

unique_ptr<Board::Move> CheckersMove::Clone() const {
   return unique_ptr<Move>(new CheckersMove(*this));
}

istream &CheckersMove::Read(istream &is) {
   char numSteps, row, col;
   mSeq.clear();
   is.read((char *)&numSteps, sizeof(numSteps));
   assert(numSteps >= 0);
   mSeq.reserve(numSteps);
   for(int i = 0; i < numSteps; i++) {
      is.read((char *)&row, sizeof(row));
      is.read((char *)&col, sizeof(col));
      assert(InRange((char) 0, row, (char) CheckersBoard::DIM));
      assert(InRange((char) 0, col, (char) CheckersBoard::DIM));
      mSeq.push_back(CheckersBoard::Loc(row, col));
   }
   return is;
}

ostream &CheckersMove::Write(ostream &os) const {
   char numSteps, row, col;
   vector<CheckersBoard::Loc>::const_iterator itr;

   numSteps = mSeq.size();
   os.write((char *)&numSteps, sizeof(numSteps));

   for (itr = mSeq.begin(); itr != mSeq.end(); itr++) {
      row = (char)(*itr).row;
      col = (char)(*itr).col;
      os.write((char *)&row, sizeof(row));
      os.write((char *)&col, sizeof(col));
   }

   return os;
}
