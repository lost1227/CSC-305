#include "CheckersPyView.h"

#include <cstdint>

#include "CheckersBoard.h"

using namespace std;

Class CheckersPyView::mClass("CheckersPyView", CheckersPyView::Create);

void CheckersPyView::Draw(ostream &out) {
   auto board = dynamic_pointer_cast<const CheckersBoard>(mModel);
   CheckersBoard::Loc loc;
   uint8_t dim = CheckersBoard::DIM;
   uint8_t piece;
   uint8_t move;

   out.write((char*)&dim, sizeof(uint8_t));

   for(loc.row = CheckersBoard::DIM - 1; loc.row >= 0; loc.row--) {
      for(loc.col = 0; loc.col < CheckersBoard::DIM; loc.col++) {
         piece = board->getPiece(loc);
         out.write((char*)&piece, sizeof(uint8_t));
      }
   }

   move = board->GetWhoseMove();
   out.write((char*)&move, sizeof(uint8_t));
}

const Class *CheckersPyView::GetClass() const {
   return &mClass;
}
