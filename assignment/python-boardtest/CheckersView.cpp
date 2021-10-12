#include "CheckersView.h"

#include <ctype.h>

#include "CheckersBoard.h"

using namespace std;

Class CheckersView::mClass("CheckersView", CheckersView::Create);

void CheckersView::Draw(ostream &out) {
   int piece;
   CheckersBoard::Loc loc;
   char symbol;
   auto ob = dynamic_pointer_cast<const CheckersBoard>(mModel);

   out << "           White" << endl << endl;
   for (loc.row = CheckersBoard::DIM - 1; loc.row >= 0; loc.row--) {
      cout << (char)('A' + loc.row) << "  ";
      for (loc.col = 0; loc.col < CheckersBoard::DIM; loc.col++) {
         piece = ob->getPiece(loc);
         symbol = piece ? (piece & CheckersBoard::WHITE) ? 'w' : 'b' : '.';
         out << (char)((piece & CheckersBoard::KING) ? toupper(symbol) : symbol)
          << "  ";
      }
      out << endl;
   }
   out << "   1  2  3  4  5  6  7  8" << endl;
   out << endl << "           Black" << endl;

   out << endl
    << (ob->GetWhoseMove() ? "White's move" : "Black's move") << endl;
}

const Class *CheckersView::GetClass() const {
   return &mClass;
}
