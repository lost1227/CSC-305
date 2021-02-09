#ifndef OTHELLOBOARD_H
#define OTHELLOBOARD_H

#include <iostream>
#include <set>
#include "MyLib.h"
#include "Board.h"

class OthelloMove;

class OthelloBoard : public Board {
public:
   friend class OthelloMove;

   static constexpr int dim = 8;
   enum {mWPiece = -1, mBPiece = 1}; // Old style classless enum example

   // Direction represents the row/col changes needed to move in a direction.
   // Public in order to satisfy defective Visual C++ compiler.
   struct Direction {
      short rDelta;  // Change in row for the direction (-1, 0, or 1)
      short cDelta;  // Change in col for the direction
   };

   struct Rules {
      int cornerWgt;
      int sideWgt;
      int nearSideWgt;
      int innerWgt;
   };

   OthelloBoard();
   ~OthelloBoard();

   int GetValue() const override;
   void ApplyMove(std::unique_ptr<Move>) override;
   void UndoLastMove() override;

   void GetAllMoves(std::list<std::unique_ptr<Move>> *) const override;
   std::unique_ptr<Move> CreateMove() const override;

   int GetWhoseMove() const override {return mNextMove == mWPiece;}
   const std::list<std::shared_ptr<const Move>> &GetMoveHist() const override 
    {return *(std::list<std::shared_ptr<const Move>> *)&mMoveHist;}

   std::unique_ptr<Board> Clone() const override;
   std::unique_ptr<const Key> GetKey() const override;

   std::istream &Read(std::istream &) override;
   std::ostream &Write(std::ostream &) const override; 
   
   static Object *CreateBoard();

   // Option accessor/mutator.  GetOptions returns dynamically allocated
   // object representing options. SetOptions takes similar object.  Caller
   // owns object in both cases.
   static void *GetOptions();
   static void SetOptions(const void *opts);      

   char GetSquare(int row, int col) const {return mBoard[row][col];}

   const Class *GetClass() const override;
   static BoardClass mClass;
protected:
   static constexpr int numDirs = 8;
   static constexpr int squareCount = 64;
   static constexpr int sqrShift = 2; 
   static constexpr int sqrMask = 0x3;

   void RecalcWeight();  // Recalculate current weight of this OthelloBoard.

   static std::set<OthelloBoard *> mRoster; // Naked to preclude storage leak
   static Direction mDirs[numDirs];
   static short mWeights[dim][dim];

   static bool InBounds(int row, int col)
    {return InRange<short>(0, row, dim) && InRange<short>(0, col, dim);}

   char mBoard[dim][dim];       // Current state of board: -1 white, 0 none, 1 black
   char mNextMove;              // Whose move is next (mWPiece or mBPiece)
   char mPassCount;             // How many pass moves have just been made
   short mWeight;               // Current board value.
   std::list<std::shared_ptr<Move>> mMoveHist; // History of moves thus far.
};

#endif
