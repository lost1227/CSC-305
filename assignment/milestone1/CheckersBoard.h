#ifndef CHECKERS_H
#define CHECKERS_H

#include <iostream>
#include <set>
#include <vector>
#include <memory>
#include <assert.h>
#include "MyLib.h"
#include "Board.h"

class CheckersMove;

class CheckersBoard : public Board {
public:
   friend class CheckersMove;

   static constexpr int KEY_LEN = 4;

   // Bitflags used in board cells to indicate color and type of piece
   static constexpr int NONE = 0, PIECE = 0x1, WHITE = 0x2, KING = 0x4;

   static constexpr int DIM = 8;
   static constexpr int PIECEWGT = 100;
   static constexpr int PC_MOVES = 2;
   static constexpr int KING_MOVES = 4;
   static constexpr int BITS_PER_PIECE = 3;

   struct Rules {
      int kingWgt; // Weight given to a king
      int backWgt; // Additional weight given to a back-row piece
      int moveWgt;

      Rules() : kingWgt(300), backWgt(100), moveWgt(20) {}

      void EndSwap();
   };

   struct Loc {
      short row;
      short col;

      Loc(short r = -1, short c = -1) : row(r), col(c) {}

      bool operator==(const Loc &rhs) const
       {return rhs.row == row && rhs.col == col;}

      bool operator<(const Loc &rhs) const
       {return row < rhs.row || (row == rhs.row && col < rhs.col);}

       void EndSwap() {row = EndianXfer(row); col = EndianXfer(col);}
   };

   CheckersBoard();
   ~CheckersBoard();

   int GetValue() const override;
   void ApplyMove(std::unique_ptr<Move>) override;
   void UndoLastMove() override;

   void GetAllMoves(std::list<std::unique_ptr<Move>> *) const override;
   std::unique_ptr<Move> CreateMove() const override;

   int GetWhoseMove() const override {return mMoveFlg == WHITE;}
   const std::list<std::shared_ptr<const Move>> &GetMoveHist() const override
    {return *(std::list<std::shared_ptr<const Move>> *)&mMoveHist;}

   std::unique_ptr<Board> Clone() const override;

   std::unique_ptr<const Key> GetKey() const override;

   static int InRange(Loc pos)
    {return pos.row >= 0 && pos.row < DIM && pos.col >= 0 && pos.col < DIM;}
   
   char getPiece(Loc loc) const {return mBoard[loc.row][loc.col];}

   std::istream &Read(std::istream &);
   std::ostream &Write(std::ostream &) const;

   static Object *CreateBoard();
   static void *GetOptions();
   static void SetOptions(const void *opts);      

   const Class *GetClass() const override;

protected:
   // Direction represents the row/col changes needed to move in a direction.
   struct Direction {
      short rDelta;  // Change in row for the direction (-1, 0, or 1)
      short cDelta;  // Change in col for the direction
   };


   void NewOptions();    // Recalculate for new options/rules.
   void CalcMoves() const;
   void FindNormalMoves() const;
   bool IsBackRow(char pc, const Loc &loc) {
      return ((pc & WHITE) && loc.row == 0) || (!(pc & WHITE) && loc.row == CheckersBoard::DIM-1);
   }

   static Rules mRules;

   // Move directions.  First two are normal; third and fourth are king-only
   static Direction mDirs[KING_MOVES];
   static std::set<CheckersBoard *> mRoster;

   long mValue;
   char mBoard[DIM][DIM];
   char mMoveFlg;
   mutable bool mMovesValid;
   
   // Precompute and adjust the list of possible moves, to save time
   mutable std::set<CheckersMove> mMoves;
   std::list<std::shared_ptr<Move>> mMoveHist;
};

#endif
