#include "C4Pop10Board.h"
#include "C4Pop10Dlg.h"
#include "C4Pop10View.h"

#include <cassert>
#include <cstring>

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

C4Pop10Board::C4Pop10Board()
    : mMoveFlg{0}
    , freeCols{DIM_W}
{
    memset(mBoard, 0, sizeof(mBoard));
}

C4Pop10Board::~C4Pop10Board() {}

int C4Pop10Board::GetValue() const {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

void C4Pop10Board::ApplyMove(unique_ptr<Move> move) {
    shared_ptr<Move> ourMove{::move(move)};
    shared_ptr<C4Pop10Move> uMove = dynamic_pointer_cast<C4Pop10Move>(ourMove);

    char piece;
    int row, col;

    switch(uMove->GetType()) {
        case C4Pop10Move::MoveType::PASS:
            throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
        break;
        case C4Pop10Move::MoveType::PLACE:
            piece = PIECE | mMoveFlg;
            col = uMove->GetSrcCol();
            assert(col < DIM_W);
            assert(!mBoard[DIM_H-1][col]);
            for(row = DIM_H-1; row > 0 && !mBoard[row-1][col]; row--)
                ;
            if(row == DIM_H-1)
                freeCols--;
            mBoard[row][col] = piece;
        break;
        case C4Pop10Move::MoveType::KEEP:
            throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
        break;
        case C4Pop10Move::MoveType::TAKE_PLACE:
            throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
        break;
        default:
        assert(false);
    }

    mMoveFlg = (mMoveFlg == RED) ? 0 : RED;
}

void C4Pop10Board::UndoLastMove() {
    throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
}

void C4Pop10Board::GetAllMoves(list<unique_ptr<Move>> *moves) const {
    int col;
    assert(moves->size() == 0);

    if(freeCols > 0) {
        for(col = 0; col < DIM_W; col++) {
            if(!(mBoard[DIM_H-1][col] & PIECE))
                moves->push_back(unique_ptr<Move>(new C4Pop10Move(C4Pop10Move::MoveType::PLACE, col)));
        }
    } else {
        throw BaseException(FString("%s:%d not implemented", __FILE__, __LINE__));
    }
}

unique_ptr<Board::Move> C4Pop10Board::CreateMove() const {
    return unique_ptr<Board::Move>(new C4Pop10Move());
}

int C4Pop10Board::GetWhoseMove() const {
    return (mMoveFlg & RED) ? 1 : 0;
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

const char C4Pop10Board::GetLoc(int row, int col) const {
    return mBoard[row][col];
}