#include "BoardTestAPI.h"
#include "Class.h"
#include "Board.h"
#include "View.h"
#include "Dialog.h"

#include <string>
#include <memory>
#include <sstream>
#include <cassert>
#include <string_view>

using namespace std;

const BoardClass *boardClass;

shared_ptr<Board> board;
unique_ptr<View> brdView;
unique_ptr<View> brdPyView;
unique_ptr<Dialog> brdDlg;

shared_ptr<Board::Move> currMove;

RawData makeRawData(string src) {
   if (src.size() == 0)
      return RawData {
         .data = nullptr,
         .size = 0
      };
   else {
      RawData data {
         .data = malloc(src.size()),
         .size = src.size()
      };
      src.copy((char*)data.data, data.size);
      return data;
   }
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
   string currMoveStr = *currMove;
   return makeRawData(move(currMoveStr));
}

void boardtest_applymove() {
   list<unique_ptr<Board::Move>> allowedMoves;

   board->GetAllMoves(&allowedMoves);

   for(auto &move : allowedMoves) {
      if(*move == *currMove) {
         board->ApplyMove(std::move(move));
         break;
      }
   }
}

RawData boardtest_saveboard() {
   ostringstream strm;
   assert(!strm.fail());
   board->Write(strm);
   string strdata = strm.str();
   return makeRawData(move(strdata));
}
RawData boardtest_savemove() {
   ostringstream strm;
   assert(!strm.fail());
   currMove->Write(strm);
   string strdata = strm.str();
   return makeRawData(move(strdata));
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
   ostringstream strm;
   assert(!strm.fail());
   brdView->Draw(strm);
   string strdata = strm.str();
   return makeRawData(move(strdata));
}

RawData boardtest_getBinaryBoard() {
   ostringstream strm;
   brdPyView->Draw(strm);
   string strdata = strm.str();
   return makeRawData(move(strdata));
}

RawData boardtest_getValidMoves() {
   ostringstream strm;
   assert(!strm.fail());
   list<unique_ptr<Board::Move>> allowedMoves;
   board->GetAllMoves(&allowedMoves);
   for(auto& move : allowedMoves) {
      strm << (string)*move << '\0';
   }
   string strdata = strm.str();
   return makeRawData(move(strdata));
}

RawData boardtest_getMoveHist() {
   ostringstream strm;
   assert(!strm.fail());
   auto moves = board->GetMoveHist();
   for(auto& move : moves) {
      strm << (string)*move << '\0';
   }
   // string_view strdata = strm.view();
   string strdata = strm.str();
   return makeRawData(move(strdata));
}

int boardtest_getBoardVal() {
   return board->GetValue();
}

void boardtest_free_rawdata(RawData data) {
   if(data.size > 0 && data.data != nullptr)
      free(data.data);
}
