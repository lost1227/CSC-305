#ifndef OTHELLOMOVE_H
#define OTHELLOMOVE_H

#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include "OthelloBoard.h"

class OthelloMove : public Board::Move {
public:
   // Flipset represents a "run" of flips in a given direction.
   struct FlipSet {
      char count = 0;                         // Number of flipped cells 
      const OthelloBoard::Direction *dir = nullptr; // Direction of run.

      FlipSet() {}
      FlipSet(int c, OthelloBoard::Direction *d) : count(c), dir(d) {}
   };

   friend class OthelloBoard;
   typedef std::list<FlipSet> FlipList;
   
   OthelloMove(char row = 0, char col = 0) : mRow(row), mCol(row) {}
   virtual ~OthelloMove() {}

   void AddFlipSet(const FlipSet &fs) 
    {mFlipSets.push_back(fs);}

   void ClearFlipSets()                {mFlipSets.clear();}
   const FlipList &GetFlipSets() const {return mFlipSets;}

   bool operator==(const Board::Move &rhs) const; 
   bool operator<(const Board::Move &rhs) const;
   operator std::string() const;
   void operator=(const std::string &src);
   std::unique_ptr<Board::Move> Clone() const;

   bool IsPass() const {return mRow == -1 && mCol == -1;}

   short GetRow() const {return mRow;}
   short GetCol() const {return mCol;}

   void operator delete(void *p);
   void *operator new(size_t sz);

protected:
   std::istream &Read(std::istream &is);
   std::ostream &Write(std::ostream &) const;

   static constexpr int bitShift = 4;
   static constexpr int bitMask = 0xF;

   char mRow;
   char mCol;
   FlipList mFlipSets;

   static std::vector<OthelloMove *> mFreeList;
};

#endif
