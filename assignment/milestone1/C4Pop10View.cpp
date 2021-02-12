#include "C4Pop10View.h"
#include "C4Pop10Board.h"

#include "MyLib.h"

using namespace std;

const Class C4Pop10View::mClass("C4Pop10View", C4Pop10View::Create);

/*

. . . . . . .
. . . . . . .
. . . . . . .
. . . . . . .
. . . . . . .
. . . . . . .
-------------
A B C D E F G
Y

*/
void C4Pop10View::Draw(ostream &out) {
    auto board = dynamic_pointer_cast<const C4Pop10Board>(mModel);
    int row, col;
    char piece;

    for(row = C4Pop10Board::DIM_H-1; row >= 0 ; row--) {
        for(col = 0; col < C4Pop10Board::DIM_W; col++) {
            piece = board->GetLoc(row, col);
            if(piece & C4Pop10Board::PIECE){
                out << ((piece & C4Pop10Board::RED) ? "R" : "Y");
            } else {
                out << ".";
            }
            if(col < C4Pop10Board::DIM_W-1)
                out << " ";
        }
        out << endl;
    }
    out << "-------------" << endl;
    out << "A B C D E F G" << endl;
    out << (board->GetWhoseMove() ? "R" : "Y") << endl;
}

const Class *C4Pop10View::GetClass() const {
    return &mClass;
}