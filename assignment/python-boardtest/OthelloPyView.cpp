#include "OthelloPyView.h"

#include "OthelloBoard.h"

#include <cstdint>

using namespace std;

Class OthelloPyView::mClass("OthelloPyView", OthelloPyView::Create);

void OthelloPyView::Draw(ostream &out) {
  shared_ptr<const OthelloBoard> board = dynamic_pointer_cast<const OthelloBoard>(mModel);

   int row, col;
   uint8_t dim = OthelloBoard::dim;
   int8_t square;
   int8_t move;

   out.write((char*)&dim, sizeof(uint8_t));

   for(row = 0; row < OthelloBoard::dim; row++) {
      for(col = 0; col < OthelloBoard::dim; col++) {
         square = board->GetSquare(row, col);
         out.write((char*)&square, sizeof(int8_t));
      }
   }

   move = board->GetWhoseMove();
   out.write((char*)&move, sizeof(uint8_t));
}

const Class *OthelloPyView::GetClass() const {
   return &mClass;
}
