#ifndef OTHELLODLG_H
#define OTHELLODLG_H

#include "Class.h"
#include "Dialog.h"

class OthelloDlg : public Dialog {
public:
   bool Run(std::istream &in, std::ostream &out, void *data) override;

   const Class *GetClass() const override;
   static Class mClass;

   static Object *Create() { return new OthelloDlg(); }
};

#endif
