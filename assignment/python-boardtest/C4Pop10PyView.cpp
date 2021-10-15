#include "C4Pop10PyView.h"

#include <cstdint>

#include <cassert>

#include "C4Pop10Board.h"
#include "MyLib.h"

using namespace std;

const Class C4Pop10PyView::mClass("C4Pop10PyView", C4Pop10PyView::Create);

void C4Pop10PyView::Draw(ostream &out) {
   auto board = dynamic_pointer_cast<const C4Pop10Board>(mModel);
   int row, col;
   char piece;

   assert(board != nullptr);

   uint8_t width, height;
   uint8_t move;

   width = C4Pop10Board::DIM_W;
   height = C4Pop10Board::DIM_H;

   out.write((char *)&width, sizeof(uint8_t));
   out.write((char *)&height, sizeof(uint8_t));

   for (row = C4Pop10Board::DIM_H - 1; row >= 0; row--) {
      for (col = 0; col < C4Pop10Board::DIM_W; col++) {
         piece = board->GetLoc(row, col);
         out.write(&piece, sizeof(char));
      }
   }

   move = board->GetWhoseMove();
   out.write((char *)&move, sizeof(uint8_t));
}

const Class *C4Pop10PyView::GetClass() const {
   return &mClass;
}