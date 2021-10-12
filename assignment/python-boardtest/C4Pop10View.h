#ifndef C4POP10VIEW_H
#define C4POP10VIEW_H

#include "View.h"

class C4Pop10View : public View {
public:
   void Draw(std::ostream &out) override;

   const Class *GetClass() const override;
   static const Class mClass;

private:
   static Object *Create() { return new C4Pop10View(); }
};

#endif