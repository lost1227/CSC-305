#ifndef MYLIB_H
#define MYLIB_H

#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <exception>
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
template <class T>
inline T Sqr(const T val) {return val*val;}

template <class T>
inline int InRange(const T lo, const T x, const T hi)
 {return !(x < lo) && x < hi;}

/* See also abs, clamp, min and max in algorithms. */

template <class Ptr>
struct LessPtr {
   int operator()(const Ptr &a, const Ptr &b) const {return *a < *b;} 
};

typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef const char *CStr;

#ifdef LITTLE_ENDIAN

inline ushort EndianXfer(ushort val) {
   // FIXME: implement this stub
   throw std::exception();
   return 0;
}// Fill in
inline short  EndianXfer(short val)  {
   // FIXME: implement this stub
   throw std::exception();
   return 0;
}// Fill in
inline int    EndianXfer(int val)    {
   // FIXME: implement this stub
   throw std::exception();
   return 0;
}// Fill in
inline uint   EndianXfer(uint val)   {
   // FIXME: implement this stub
   throw std::exception();
   return 0;
}// Fill in

#else

inline ushort EndianXfer(ushort val) {return val;}
inline short  EndianXfer(short val)  {return val;}
inline int    EndianXfer(int val)    {return val;}
inline uint   EndianXfer(uint val)   {return val;}

#endif

class BaseException : public std::exception {
public:
   BaseException(const std::string &err) : mErr(err) {}
   ~BaseException() throw() {};
   const char *what() const throw() {return mErr.c_str();}

protected:
   std::string mErr;
};

#endif

