#ifndef CHECKERSDLG_H
#define CHECKERSDLG_H

#include "Class.h"
#include "Dialog.h"

class CheckersDlg : public Dialog {
public:
   bool Run(std::istream &in, std::ostream &out, void *data);

   const Class *GetClass() const override;
   static Class mClass;

   static Object *Create() {return new CheckersDlg();}

private:
   static constexpr int KING_MIN = 0;
   static constexpr int KING_MAX = 1000;
   static constexpr int BACK_MIN = 0;
   static constexpr int BACK_MAX = 1000;
   static constexpr int MOVE_MIN = 0;
   static constexpr int MOVE_MAX = 100;
};

#endif