#ifndef BOARD_TEST_API_H
#define BOARD_TEST_API_H

#include <stddef.h>

const BoardClass *boardClass;

extern "C" {

typedef struct RawData {
   size_t size;
   void *data;
} RawData;

int boardtest_init(char *boardType);

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
}

#endif
