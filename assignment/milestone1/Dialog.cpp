#include "Dialog.h"

#include <iostream>
#include <sstream>
#include <string>

#include "MyLib.h"

using namespace std;

void Dialog::ReadLimitInt(
 istream &is, ostream &os, int *val, int lo, int hi, string prompt) {
   string inStr, ostr;
   istringstream inStrStm;
   bool valid = false;

   while (!valid) {
      os << prompt << " [" << lo << ", " << hi << "]: ";
      if (getline(is, inStr).eof())
         throw BaseException("Unexpected EOF");
      inStrStm = istringstream(inStr);

      if ((inStrStm >> *val).fail())
         os << "Badly formatted input" << endl;
      else {
         ostr.clear();
         getline(inStrStm, ostr);
         if (ostr.find_first_not_of(" \t") != string::npos)
            os << "Unexpected garbage after value." << endl;
         else if (*val < lo || *val > hi)
            os << "Please enter a value between " << lo << " and " << hi
               << endl;
         else
            valid = true;
      }
   }
}