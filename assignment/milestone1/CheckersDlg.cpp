#include "CheckersDlg.h"
#include "CheckersBoard.h"

using namespace std;

Class CheckersDlg::mClass("CheckersDlg", CheckersDlg::Create);

bool CheckersDlg::Run(istream &in, ostream &out, void *data) {
   // FIXME: implement this stub
   throw BaseException("CheckersDlg::Run is not implemented");
   return false;
}

const Class *CheckersDlg::GetClass() const {
   // FIXME: implement this method stub
   throw BaseException("CheckersDlg::GetClass is not implemented");
   return nullptr;
}
