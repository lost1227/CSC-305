#ifndef CHECKERSDLG_H
#define CHECKERSDLG_H

#include "Class.h"
#include "Dialog.h"

class CheckersDlg : public Dialog {
public:
   bool Run(std::istream &in, std::ostream &out, void *data);

   const Class *GetClass() const override;
   static Class mClass;

   static Object *Create() { return new CheckersDlg(); }
};

#endif