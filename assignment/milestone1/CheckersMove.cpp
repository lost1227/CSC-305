#include <regex>
#include <ctype.h>
#include "MyLib.h"
#include "CheckersMove.h"
#include "CheckersBoard.h"

using namespace std;


void *CheckersMove::operator new(size_t sz) {

}

void CheckersMove::operator delete(void *p) {

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
   
   return itr1 == mSeq.end();
}

bool CheckersMove::operator<(const Board::Move &rhs) const {






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






   
}

unique_ptr<Board::Move> CheckersMove::Clone() const {
   return unique_ptr<Move>(new CheckersMove(*this));
}

istream &CheckersMove::Read(istream &is) {
   
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
