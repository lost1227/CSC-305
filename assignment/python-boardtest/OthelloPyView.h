#pragma once

#include "View.h"

class OthelloPyView : public View {
public:
   void Draw(std::ostream &out) override;

   const Class *GetClass() const override;
   static Class mClass;

   virtual ~OthelloPyView() {}

private:
   static Object *Create() { return new OthelloPyView(); }
};
