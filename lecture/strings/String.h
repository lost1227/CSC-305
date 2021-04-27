// String header file.  Copyright Software Inventions, Inc.

#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <string.h>

struct String {
   String()                {ref = new RefNode("", 0);}
   String(const char *c)   {ref = new RefNode(c, strlen(c));}
   String(const String &s) {Attach(s);}
   String(String &&s)      {ref = s.ref; s.ref = nullptr;}
   ~String()               {Detach();}

   const char &operator[](int ndx) const     {return ref->data[ndx];}
   char &operator[](int ndx)                 {Solo(); return ref->data[ndx];}

   const String &operator=(const String &s)
    {if (&s != this) {Detach(); Attach(s);} return *this;}

   const String &operator=(String &&s)
    {Detach(); ref = s.ref; s.ref = nullptr; return *this;}

   int operator==(const String &rhs) const
    {return strcmp(ref->data, rhs.ref->data) == 0;}

   int operator!=(const String &rhs) const
    {return strcmp(ref->data, rhs.ref->data) != 0;}

   int operator<=(const String &rhs) const
    {return strcmp(ref->data, rhs.ref->data) <= 0;}

   int operator>=(const String &rhs) const
    {return strcmp(ref->data, rhs.ref->data) >= 0;}

   int operator<(const String &rhs) const
    {return strcmp(ref->data, rhs.ref->data) < 0;}

   int operator>(const String &rhs) const
    {return strcmp(ref->data, rhs.ref->data) > 0;}

   int Length() {return ref->len;}

   friend inline std::ostream &operator<<(std::ostream &os, const String &str)
    {return os << str.ref->data;}

   friend std::istream &operator>>(std::istream &is, String &str);

protected:
   void Attach(const String &s) {ref = s.ref; ref->refs++;}
   void Detach()                {if (--ref->refs == 0) delete ref;}
   void Solo()
    {if (ref->refs > 1) {ref->refs--; ref = new RefNode(ref->data, ref->len);}}

   static constexpr int stdIncr = 20;

   struct RefNode {
      int refs;
      int len;
      int size;
      char *data;

      RefNode(const char *dt, int ln) : refs(1) {Copy(dt, ln, 0);}
      ~RefNode()                                {delete [] data;}

      void Copy(const char *dt, int ln, int sp = 0)
       {len = ln; size = ln+sp; data = new char[size+1]; strcpy(data, dt);}

      void Resize(int i)
       {char *t = data; Copy(t, len, i); delete [] t;};
   };

   RefNode *ref;
};

#endif
