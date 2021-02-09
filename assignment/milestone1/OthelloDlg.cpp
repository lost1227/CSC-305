#include "OthelloDlg.h"
#include "OthelloBoard.h"

#include <limits>

using namespace std;

Class OthelloDlg::mClass("OthelloDlg", OthelloDlg::Create);

bool OthelloDlg::Run(istream &in, ostream &out, void *data) {
   OthelloBoard::Rules *rules = reinterpret_cast<OthelloBoard::Rules *>(data);
   char resp;

   out << "Side weight: " << rules->sideWgt << endl
      << "Near side weight: " << rules->nearSideWgt << endl
      << "Corner weight: " << rules->cornerWgt << endl
      << "Inner weight: " << rules->innerWgt << endl;

   out << endl << "Modify? [y/n] ";
   if ((in >> resp).eof())
      throw BaseException("Unexpected EOF");

   in.ignore(numeric_limits<streamsize>::max(), '\n');
   
   if (resp == 'y') {
      out << endl;
      ReadLimitInt(in, out, &rules->sideWgt, 0, 100, "Enter side weight");
      ReadLimitInt(in, out, &rules->nearSideWgt, 0, 100,
       "Enter near side weight");
      ReadLimitInt(in, out, &rules->cornerWgt, 0, 100, "Enter corner weight");
      ReadLimitInt(in, out, &rules->innerWgt, 0, 100, "Enter inner weight");
   }
   return resp == 'y';
}

const Class *OthelloDlg::GetClass() const {
   return &mClass;
}
