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
   uint8_t piece;

   assert(board != nullptr);

   uint8_t width, height;
   uint8_t move;

   uint8_t safeDisks, threatDisks, keptDisks;

   const C4Pop10Board::PlayerScore& redScore = board->GetRedScore();
   const C4Pop10Board::PlayerScore& yellowScore = board->GetYellowScore();

   width = C4Pop10Board::DIM_W;
   height = C4Pop10Board::DIM_H;

   out.write((char *)&width, sizeof(uint8_t));
   out.write((char *)&height, sizeof(uint8_t));

   for (row = C4Pop10Board::DIM_H - 1; row >= 0; row--) {
      for (col = 0; col < C4Pop10Board::DIM_W; col++) {
         piece = board->GetLoc(row, col);
         out.write((char*)&piece, sizeof(uint8_t));
      }
   }

   move = board->GetWhoseMove();
   out.write((char *)&move, sizeof(uint8_t));

   safeDisks = redScore.safeDisks;
   threatDisks = redScore.threatDisks;
   keptDisks = redScore.keptDisks;

   out.write((char*)&safeDisks, sizeof(uint8_t));
   out.write((char*)&threatDisks, sizeof(uint8_t));
   out.write((char*)&keptDisks, sizeof(uint8_t));

   safeDisks = yellowScore.safeDisks;
   threatDisks = yellowScore.threatDisks;
   keptDisks = yellowScore.keptDisks;

   out.write((char*)&safeDisks, sizeof(uint8_t));
   out.write((char*)&threatDisks, sizeof(uint8_t));
   out.write((char*)&keptDisks, sizeof(uint8_t));
}

const Class *C4Pop10PyView::GetClass() const {
   return &mClass;
}