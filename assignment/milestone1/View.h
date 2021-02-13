#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <memory>

#include "Board.h"
#include "Class.h"

class View : public Object {
public:
   virtual void Draw(std::ostream &out) = 0;
   virtual void SetModel(const std::shared_ptr<const Board> &brd) {
      mModel = brd;
   }

protected:
   std::shared_ptr<const Board> mModel;
};

#endif
