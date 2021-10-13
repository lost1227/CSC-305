#include "BoardTestAPI.h"
#include "Class.h"
#include "Board.h"
#include "View.h"
#include "Dialog.h"

#include <string>
#include <memory>

using namespace std;

const BoardClass *boardClass;

shared_ptr<Board> board;
unique_ptr<View> brdView;
unique_ptr<Dialog> brdDlg;

int boardtest_init(char *boardType) {
   auto boards = BoardClass::GetAllClasses();
   for (auto &bc : boards) {
      if (bc->GetName() == boardType) {
         boardClass = bc;
         board = shared_ptr<Board>(
          dynamic_cast<Board *>(boardClass->NewInstance()));
         brdView = unique_ptr<View>(
          dynamic_cast<View *>(boardClass->GetViewClass()->NewInstance()));
         brdDlg = unique_ptr<Dialog>(
          dynamic_cast<Dialog *>(boardClass->GetDlgClass()->NewInstance()));
         break;
      }
   }

   if (!board || !brdView || !brdDlg) {
      return -1;
   }
   
   return 0;
}

int boardtest_entermove(char *);
char *boardtest_showmove();
int boardtest_applymove();

int boardtest_getval();

RawData boardtest_saveboard();
RawData boardtest_savemove();

int boardtest_loadboard(RawData);
int boardtest_loadmove(RawData);

int boardtest_comparekeys(RawData);
int boardtest_comparemove(char *);

int boardtest_undoMoves(int moveCount);

char *boardtest_showboard();
