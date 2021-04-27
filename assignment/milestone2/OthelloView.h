#ifndef OTHELLOVIEW_H
#define OTHELLOVIEW_H

#include "View.h"

class OthelloView : public View {
public:
   void Draw(std::ostream &out) override;

   const Class *GetClass() const override;
   static Class mClass;

   virtual ~OthelloView() {}

private:
   static Object *Create() { return new OthelloView(); }
};

#endif
