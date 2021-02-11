#ifndef C4POP10DLG_H
#define C4POP10DLG_H

#include "Dialog.h"

class C4Pop10Dlg : public Dialog {
public:
    bool Run(std::istream &in, std::ostream &out, void *data) override;

    const Class *GetClass() const override;
    static Class mClass;
};

#endif