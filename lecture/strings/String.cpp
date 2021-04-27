// String source file.  Copyright Software Inventions, Inc.

#include <ctype.h>
#include "String.h"

using namespace std;

istream &operator>>(istream &is, String &str)
{
   char c;
   String::RefNode *ref;

   str.Solo();
   ref = str.ref;
   ref->len = 0;

   while (isspace(c = is.get()))
      ;
   is.putback(c);

   do {
      if (ref->len == ref->size) {
         ref->data[ref->len] = '\0';
         ref->Resize(String::stdIncr);
      }
   } while (!isspace(ref->data[ref->len++] = is.get()));

   is.putback(ref->data[--ref->len]);
   ref->data[ref->len] = '\0';

   return is;
}
