#ifndef MYLIB_H
#define MYLIB_H

#include <stdarg.h>
#include <stdio.h>

#include <exception>
#include <string>
#include <utility>

// String subclass offering a printf-style constructor
class FString : public std::string {
public:
   FString(const char *fmt, ...) {
      static const int bufLen = 1024;
      static char buf[bufLen];
      va_list args;

      va_start(args, fmt);
      vsnprintf(buf, bufLen, fmt, args);
      va_end(args);

      *(std::string *)this = std::string(buf);
   }
};

// The consts in the parameter lists keep the compiler
// from griping about mismatches between const long and long, for instance.
// Note that Sqr is really no faster than pow(val, 2), just briefer
template<class T>
inline T Sqr(const T val) {
   return val * val;
}

template<class T>
inline int InRange(const T lo, const T x, const T hi) {
   return !(x < lo) && x < hi;
}

/* See also abs, clamp, min and max in algorithms. */

template<class Ptr>
struct LessPtr {
   int operator()(const Ptr &a, const Ptr &b) const { return *a < *b; }
};

typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef const char *CStr;

#ifdef LITTLE_ENDIAN

inline ushort EndianXfer(ushort val) {
   return (val >> 8) | (val << 8);
}
inline short EndianXfer(short val) {
   return (val >> 8) | (val << 8);
}
inline int EndianXfer(int val) {
   return ((val & 0xFF000000) >> 24) | ((val & 0x00FF0000) >> 8)
      | ((val & 0x0000FF00) << 8) | ((val & 0x000000FF) << 24);
}
inline uint EndianXfer(uint val) {
   return ((val & 0xFF000000) >> 24) | ((val & 0x00FF0000) >> 8)
      | ((val & 0x0000FF00) << 8) | ((val & 0x000000FF) << 24);
}

#else

inline ushort EndianXfer(ushort val) {
   return val;
}
inline short EndianXfer(short val) {
   return val;
}
inline int EndianXfer(int val) {
   return val;
}
inline uint EndianXfer(uint val) {
   return val;
}

#endif

class BaseException : public std::exception {
public:
   BaseException(const std::string &err): mErr(err) {}
   ~BaseException() throw(){};
   const char *what() const throw() { return mErr.c_str(); }

protected:
   std::string mErr;
};

struct FreeListDeleter {
   void operator()(void *ptr) {
      if (ptr)
         ::operator delete[](ptr);
   }
};

#endif
