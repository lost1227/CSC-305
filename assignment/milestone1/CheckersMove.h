#ifndef CHECKERSMOVE_H
#define CHECKERSMOVE_H

#include <memory>
#include <string>
#include <vector>

#include "CheckersBoard.h"
#include "MyLib.h"

class CheckersMove : public Board::Move {
public:
   friend class CheckersBoard;

   CheckersMove(const std::vector<CheckersBoard::Loc> &seq);

   ~CheckersMove(){};

   bool operator==(const Board::Move &rhs) const override;
   bool operator<(const Board::Move &rhs) const override;
   operator std::string() const override;
   void operator=(const std::string &src) override;
   std::unique_ptr<Board::Move> Clone() const override;

   void operator delete(void *p);
   void *operator new(size_t sz);
   void *operator new(size_t sz, void *vp) { return vp; }

protected:
   std::istream &Read(std::istream &is);
   std::ostream &Write(std::ostream &) const;

   std::vector<CheckersBoard::Loc> mSeq;
   bool mWasKinged;
   std::vector<bool> mWereKings;

   static std::vector<std::unique_ptr<CheckersMove, FreeListDeleter>> mFreeList;
};

#endif
