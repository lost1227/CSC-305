#ifndef C4POP10MOVE_H
#define C4POP10MOVE_H

#include <string>

#include "Board.h"
#include "MyLib.h"

class C4Pop10Move : public Board::Move {
public:
   enum class MoveType : char { PASS = 0, PLACE = 1, KEEP = 2, TAKE_PLACE = 3 };

   C4Pop10Move(
    MoveType mvType = MoveType::PASS, int srcRow = -1, int dstRow = -1);
   ~C4Pop10Move();

   std::unique_ptr<Move> Clone() const override;
   bool operator==(const Move &) const override;
   bool operator<(const Move &) const override;
   operator std::string() const override;
   void operator=(const std::string &src) override;

   void operator delete(void *p);
   void *operator new(size_t sz);
   void *operator new(size_t sz, void *vp) { return vp; }

   std::istream &Read(std::istream &) override;
   std::ostream &Write(std::ostream &) const override;

   const MoveType GetType() const { return mType; }
   int GetSrcCol() const { return mSrcCol; }
   int GetDstCol() const { return mDstCol; }

   void SetDidFillCol(bool didFillCol) { mDidFillCol = didFillCol; }
   bool GetDidFillCol() const { return mDidFillCol; }

protected:
   MoveType mType;

   char mSrcCol;
   char mDstCol;

   bool mDidFillCol;

   static std::vector<std::unique_ptr<C4Pop10Move, FreeListDeleter>> mFreeList;

   char colToChar(const int col) const;
   int colStrToInt(const std::string &str) const;
};

#endif