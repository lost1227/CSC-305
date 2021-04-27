#ifndef BESTMOVE_H
#define BESTMOVE_H

#include "Board.h"
#include <memory>

struct BestMove {
   std::shared_ptr<Board::Move> bestMove; // The best move to take
   long value;                            // The board value that will result
   long depth;                            // Minimax level used to get move
   long numBoards;                        // # of boards explored to get move

   BestMove() : bestMove(nullptr), value(0), depth(0), numBoards(0) {}
   BestMove(const std::shared_ptr<Board::Move> &mv, long val, int dpt, long brds)
    : bestMove(mv), value(val), depth(dpt), numBoards(brds) {}
   
   void SetBestMove(std::shared_ptr<Board::Move> &mv) {bestMove = mv;}
   void SetBestMove(std::unique_ptr<Board::Move> &&mv) {bestMove = std::move(mv);}
};

#endif
