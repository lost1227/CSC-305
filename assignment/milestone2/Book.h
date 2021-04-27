#ifndef BOOK_H
#define BOOK_H

#include <map>
#include <memory>
#include <iostream>
#include "BestMove.h"
#include "MyLib.h"

class Book : public [FILL IN MAP BASE CLASS]  {
public:
   Book() : mLevel(0) {}

   int GetLevel()          {return mLevel;}
   void SetLevel(int val)  {mLevel = val;}

   // Read/write book to and from a file in binary format.  In Read,
   // assume the Keys and Moves in the file are those for brdCls.
   std::istream &Read(std::istream &is, const Class *brdCls);
   std::ostream &Write(std::ostream &os);

protected:
   uchar mLevel;
};

#endif
