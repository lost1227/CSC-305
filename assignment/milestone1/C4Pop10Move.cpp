#include "C4Pop10Move.h"

using namespace std;

vector<unique_ptr<C4Pop10Move, FreeListDeleter>> C4Pop10Move::mFreeList;

C4Pop10Move::C4Pop10Move(MoveType mvType, int srcRow, int dstRow)
    : mType(mvType)
    , mSrcRow(srcRow)
    , mDstRow(dstRow)
{}

C4Pop10Move::~C4Pop10Move() {}

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
    unique_ptr<C4Pop10Move, FreeListDeleter> ptr((C4Pop10Move *)p, FreeListDeleter());
    mFreeList.push_back(move(ptr));

    mOutstanding--;
}

void *C4Pop10Move::operator new(size_t sz) {
    void *tmp;

    if(mFreeList.size()) {
        tmp = (void *) mFreeList.back().release();
        mFreeList.pop_back();
    }
    else {
        tmp = ::new char[sz];
    }

    mOutstanding++;
    return tmp;
}

istream &C4Pop10Move::Read(istream &in) {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

ostream &C4Pop10Move::Write(ostream &out) const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}
