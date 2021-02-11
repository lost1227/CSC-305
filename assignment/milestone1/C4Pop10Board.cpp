#include "C4Pop10Board.h"
#include "C4Pop10Dlg.h"
#include "C4Pop10View.h"

using namespace std;

const BoardClass C4Pop10Board::mClass(
    "C4Pop10Board",
    C4Pop10Board::CreateBoard,
    "C4Pop10",
    &C4Pop10View::mClass,
    &C4Pop10Dlg::mClass,
    C4Pop10Board::SetOptions,
    C4Pop10Board::GetOptions
);

C4Pop10Board::C4Pop10Board() {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

C4Pop10Board::~C4Pop10Board() {
    // throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
    cerr << FString("%s:%d not implemented", __FILE__, __LINE__) << endl;
}

int C4Pop10Board::GetValue() const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

void C4Pop10Board::ApplyMove(unique_ptr<Move> move) {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

void C4Pop10Board::UndoLastMove() {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

void C4Pop10Board::GetAllMoves(list<unique_ptr<Move>> *moves) const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

unique_ptr<Board::Move> C4Pop10Board::CreateMove() const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

int C4Pop10Board::GetWhoseMove() const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

const list<shared_ptr<const Board::Move>> &C4Pop10Board::GetMoveHist() const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

unique_ptr<Board> C4Pop10Board::Clone() const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

unique_ptr<const Board::Key> C4Pop10Board::GetKey() const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

istream &C4Pop10Board::Read(istream &in) {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

ostream &C4Pop10Board::Write(ostream &out) const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

Object *C4Pop10Board::CreateBoard() {
    return new C4Pop10Board;
}

void *C4Pop10Board::GetOptions() {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

void C4Pop10Board::SetOptions(const void *opts) {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

const Class *C4Pop10Board::GetClass() const {
    return &mClass;
}