#ifndef BOARD_TEST_API_H
#define BOARD_TEST_API_H

#include <stddef.h>

extern "C" {

typedef struct RawData {
   void *data;
   size_t size;
} RawData;

int boardtest_init(char *boardType);

void boardtest_entermove(char *);
RawData boardtest_showmove();
void boardtest_applymove();

RawData boardtest_saveboard();
RawData boardtest_savemove();

void boardtest_loadboard(RawData);
void boardtest_loadmove(RawData);

void boardtest_undoMoves(int moveCount);

RawData boardtest_showboard();

RawData boardtest_getValidMoves();

RawData boardtest_getMoveHist();

void boardtest_free_rawdata(RawData);
}

#endif
