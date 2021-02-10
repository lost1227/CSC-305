#include "CheckersDlg.h"
#include "CheckersBoard.h"

#include <limits>

using namespace std;

Class CheckersDlg::mClass("CheckersDlg", CheckersDlg::Create);

bool CheckersDlg::Run(istream &in, ostream &out, void *data) {
   CheckersBoard::Rules *rules = reinterpret_cast<CheckersBoard::Rules *>(data);
   char resp;
   out << "(Piece weight is always " << CheckersBoard::PIECEWGT << ")" << endl
      << "King weight: " << rules->kingWgt << endl
      << "Back row weight: " << rules->backWgt << endl
      << "Move weight: " << rules->moveWgt << endl;

   out << endl << "Modify? [y/n] ";
   if ((in >> resp).eof())
      throw BaseException("Unexpected EOF");

   in.ignore(numeric_limits<streamsize>::max(), '\n');

   if(resp == 'y') {
      out << endl;
      ReadLimitInt(in, out, &rules->kingWgt, KING_MIN, KING_MAX, "Enter king weight");
      ReadLimitInt(in, out, &rules->backWgt, BACK_MIN, BACK_MAX, "Enter back-row weight");
      ReadLimitInt(in, out, &rules->moveWgt, MOVE_MIN, MOVE_MAX, "Enter move weight");
   }
   
   return resp == 'y';
}

const Class *CheckersDlg::GetClass() const {
   return &mClass;
}
