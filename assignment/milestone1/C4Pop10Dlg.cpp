#include "C4Pop10Dlg.h"

#include "MyLib.h"

using namespace std;

const Class C4Pop10Dlg::mClass("C4Pop10Dlg", C4Pop10Dlg::Create);

bool C4Pop10Dlg::Run(istream &in, ostream &out, void *data) {
   throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

const Class *C4Pop10Dlg::GetClass() const {
   return &mClass;
}