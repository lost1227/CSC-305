#pragma once

#include "View.h"

class CheckersPyView : public View {
public:
   void Draw(std::ostream &out);

   const Class *GetClass() const override;
   static Class mClass;

private:
   static Object *Create() { return new CheckersPyView(); }
};
