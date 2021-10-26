#ifndef BOARD_TEST_API_H
#define BOARD_TEST_API_H

#include <stddef.h>

#ifdef _WIN32
#define BOARDTESTAPI __declspec(dllexport)
#else
#define BOARDTESTAPI
#endif

extern "C" {

BOARDTESTAPI typedef struct RawData {
   void *data;
   size_t size;
} RawData;

BOARDTESTAPI int boardtest_init(char *boardType);

BOARDTESTAPI int boardtest_entermove(char *);
BOARDTESTAPI RawData boardtest_showmove();
BOARDTESTAPI void boardtest_applymove();

BOARDTESTAPI RawData boardtest_saveboard();
BOARDTESTAPI RawData boardtest_savemove();

BOARDTESTAPI RawData boardtest_getBoardKey();

BOARDTESTAPI void boardtest_loadboard(RawData);
BOARDTESTAPI void boardtest_loadmove(RawData);

BOARDTESTAPI void boardtest_undoMoves(int moveCount);

BOARDTESTAPI RawData boardtest_showboard();
BOARDTESTAPI RawData boardtest_getBinaryBoard();

BOARDTESTAPI RawData boardtest_getValidMoves();

BOARDTESTAPI RawData boardtest_getMoveHist();

BOARDTESTAPI int boardtest_getBoardVal();

BOARDTESTAPI void boardtest_free_rawdata(RawData);
}

#endif
