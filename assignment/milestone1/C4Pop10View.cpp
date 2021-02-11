#include "C4Pop10View.h"

#include "MyLib.h"

using namespace std;

const Class C4Pop10View::mClass("C4Pop10View", C4Pop10View::Create);

void C4Pop10View::Draw(ostream &out) {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

const Class *C4Pop10View::GetClass() const {
    return &mClass;
}