#include "Dialog.h"

#include <cassert>
#include <iostream>
#include <limits>
#include <string>

#include "MyLib.h"

using namespace std;

enum class ReadLimitIntState {
   READ_INITIAL,
   FINISH_LINE_UNCONDITIONAL,
   FINISH_LINE_CONDITIONAL,
   CHECK_VALUE,
   DONE
};

void Dialog::ReadLimitInt(
   istream &is, ostream &os, int *val, int lo, int hi, std::string prompt) {
   ReadLimitIntState state = ReadLimitIntState::READ_INITIAL;
   char next;
   while (state != ReadLimitIntState::DONE) {
      switch (state) {
         case ReadLimitIntState::READ_INITIAL:
            assert(is.good());
            os << prompt << " [" << lo << ", " << hi << "]: ";
            is >> *val;

            if (is.fail()) {
               if (is.eof()) {
                  throw BaseException("Unexpected EOF");
               }
               is.clear();
               os << "Badly formatted input" << endl;
               state = ReadLimitIntState::FINISH_LINE_UNCONDITIONAL;
               break;
            }
            state = ReadLimitIntState::FINISH_LINE_CONDITIONAL;
            break;
         case ReadLimitIntState::FINISH_LINE_UNCONDITIONAL:
            is.ignore(numeric_limits<streamsize>::max(), '\n');
            state = ReadLimitIntState::READ_INITIAL;
            break;
         case ReadLimitIntState::FINISH_LINE_CONDITIONAL:
            assert(is.good());
            next = is.get();
            if (is.eof()) {
               throw BaseException("Unexpected EOF");
            }
            if (next == '\n') {
               state = ReadLimitIntState::CHECK_VALUE;
               break;
            }
            if (next != ' ') {
               os << "Unexpected garbage after value." << endl;
               state = ReadLimitIntState::FINISH_LINE_UNCONDITIONAL;
               break;
            }
            break;
         case ReadLimitIntState::CHECK_VALUE:
            if (*val < lo || *val > hi) {
               os << "Please enter a value between " << lo << " and " << hi
                  << endl;
               state = ReadLimitIntState::READ_INITIAL;
               break;
            }
            state = ReadLimitIntState::DONE;
            break;
         default:
            assert(false);
      }
   }
}