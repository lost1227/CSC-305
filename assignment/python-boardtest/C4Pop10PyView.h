#pragma once

#include "View.h"

class C4Pop10PyView : public View {
public:
   void Draw(std::ostream &out) override;

   const Class *GetClass() const override;
   static const Class mClass;

private:
   static Object *Create() { return new C4Pop10PyView(); }
};