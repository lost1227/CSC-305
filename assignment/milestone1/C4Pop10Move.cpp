#include "C4Pop10Move.h"

// TODO: remove temporary import
#include <iostream>

using namespace std;

vector<unique_ptr<C4Pop10Move, FreeListDeleter>> C4Pop10Move::mFreeList;

C4Pop10Move::C4Pop10Move() {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

C4Pop10Move::~C4Pop10Move() {
    cerr << FString("%s:%d not implemented", __FILE__, __LINE__) << endl;
}

unique_ptr<Board::Move> C4Pop10Move::Clone() const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

bool C4Pop10Move::operator==(const Board::Move &oth) const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

bool C4Pop10Move::operator<(const Board::Move &oth) const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

C4Pop10Move::operator string() const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

void C4Pop10Move::operator=(const string &src) {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

void C4Pop10Move::operator delete(void *p) {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

void *C4Pop10Move::operator new(size_t sz) {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

istream &C4Pop10Move::Read(istream &in) {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

ostream &C4Pop10Move::Write(ostream &out) const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}
