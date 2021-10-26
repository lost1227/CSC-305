#include "BoardTestAPI.h"
#include "Class.h"
#include "Board.h"
#include "View.h"
#include "Dialog.h"

#include <string>
#include <memory>
#include <sstream>
#include <cassert>

using namespace std;

const BoardClass *boardClass;

shared_ptr<Board> board;
unique_ptr<View> brdView;
unique_ptr<View> brdPyView;
unique_ptr<Dialog> brdDlg;

shared_ptr<Board::Move> currMove;


list<unique_ptr<Board::Move>> allowedMoves;
ostringstream myoutstrm;
string currstr;

RawData getCurrStrData() {
   return RawData {
      .data = (void *) currstr.c_str(),
      .size = currstr.size()
   };
}

int boardtest_init(char *boardType) {
   auto boards = BoardClass::GetAllClasses();
   for (auto &bc : boards) {
      if (bc->GetName() == boardType) {
         boardClass = bc;
         board = shared_ptr<Board>(
          dynamic_cast<Board *>(boardClass->NewInstance()));
         brdView = unique_ptr<View>(
          dynamic_cast<View *>(boardClass->GetViewClass()->NewInstance()));
         brdPyView = unique_ptr<View>(
            dynamic_cast<View *>(boardClass->GetPyViewClass()->NewInstance()));
         brdDlg = unique_ptr<Dialog>(
          dynamic_cast<Dialog *>(boardClass->GetDlgClass()->NewInstance()));
         break;
      }
   }

   if (!board || !brdView || !brdDlg) {
      return -1;
   }

   brdView->SetModel(board);
   brdPyView->SetModel(board);

   currMove = board->CreateMove();
   
   return 0;
}

void boardtest_entermove(char *moveStr) {
   *currMove = moveStr;
}

RawData boardtest_showmove() {
   currstr = *currMove;
   return getCurrStrData();
}

void boardtest_applymove() {
   allowedMoves.clear();

   board->GetAllMoves(&allowedMoves);

   for(auto &move : allowedMoves) {
      if(*move == *currMove) {
         board->ApplyMove(std::move(move));
         break;
      }
   }
}

RawData boardtest_saveboard() {
   myoutstrm.str("");
   board->Write(myoutstrm);
   currstr = move(myoutstrm.str());
   return getCurrStrData();
}
RawData boardtest_savemove() {
   myoutstrm.str("");
   currMove->Write(myoutstrm);
   currstr = move(myoutstrm.str());
   return getCurrStrData();
}

RawData boardtest_getBoardKey() {
   myoutstrm.str("");
   board->GetKey()->Write(myoutstrm);
   currstr = move(myoutstrm.str());
   return getCurrStrData();
}

void boardtest_loadboard(RawData data) {
   istringstream strm(string((char*)data.data, data.size));
   assert(!strm.fail());
   board->Read(strm);
}
void boardtest_loadmove(RawData data) {
   istringstream strm(string((char*)data.data, data.size));
   assert(!strm.fail());
   currMove->Read(strm);
}

void boardtest_undoMoves(int moveCount) {
   assert(moveCount >= 0);
   if(moveCount > (int)board->GetMoveHist().size())
      moveCount = board->GetMoveHist().size();
   while(moveCount-- > 0)
      board->UndoLastMove();
}

RawData boardtest_showboard() {
   myoutstrm.str("");
   brdView->Draw(myoutstrm);
   currstr = move(myoutstrm.str());
   return getCurrStrData();
}

RawData boardtest_getBinaryBoard() {
   myoutstrm.str("");
   brdPyView->Draw(myoutstrm);
   currstr = move(myoutstrm.str());
   return getCurrStrData();
}

RawData boardtest_getValidMoves() {
   myoutstrm.str("");
   allowedMoves.clear();
   board->GetAllMoves(&allowedMoves);
   for(auto& move : allowedMoves) {
      myoutstrm << (string)*move << '\0';
   }
   currstr = move(myoutstrm.str());
   return getCurrStrData();
}

RawData boardtest_getMoveHist() {
   myoutstrm.str("");
   auto moves = board->GetMoveHist();
   for(auto& move : moves) {
      myoutstrm << (string)*move << '\0';
   }
   currstr = move(myoutstrm.str());
   return getCurrStrData();
}

int boardtest_getBoardVal() {
   return board->GetValue();
}

void boardtest_free_rawdata(RawData data) {
   currstr = string();
}
