#include "C4Pop10Dlg.h"

#include <limits>

#include "C4Pop10Board.h"

using namespace std;

const Class C4Pop10Dlg::mClass("C4Pop10Dlg", C4Pop10Dlg::Create);

static constexpr int SAFE_MIN = 1, SAFE_MAX = 500, KEPT_MIN = 1,
                     KEPT_MAX = 1000, THREAT_MIN = 1, THREAT_MAX = 200,
                     MOVE_MIN = 1, MOVE_MAX = 200;

bool C4Pop10Dlg::Run(istream &in, ostream &out, void *data) {
   C4Pop10Board::Rules *rules = reinterpret_cast<C4Pop10Board::Rules *>(data);
   char resp;
   out << "Safe disc weight: " << rules->safeWgt << endl
       << "Kept disc weight: " << rules->keptWgt << endl
       << "Threat weight: " << rules->threatWgt << endl
       << "Move weight: " << rules->moveWght << endl;

   out << endl << "Modify? [y/n] ";
   if ((in >> resp).eof())
      throw BaseException("Unexpected EOF");

   in.ignore(numeric_limits<streamsize>::max(), '\n');

   if (resp == 'y') {
      out << endl;
      ReadLimitInt(in, out, &rules->safeWgt, SAFE_MIN, SAFE_MAX,
         "Enter safe disc weight");
      ReadLimitInt(in, out, &rules->keptWgt, KEPT_MIN, KEPT_MAX,
         "Enter kept disc weight");
      ReadLimitInt(in, out, &rules->threatWgt, THREAT_MIN, THREAT_MAX,
         "Enter threat weight");
      ReadLimitInt(
         in, out, &rules->moveWght, MOVE_MIN, MOVE_MAX, "Enter move weight");
   }

   return resp == 'y';
}

const Class *C4Pop10Dlg::GetClass() const {
   return &mClass;
}