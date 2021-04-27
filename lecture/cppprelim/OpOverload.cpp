// Operator overload example
// (Also struct initialization and printf.)
// Copyright 1995 Software Inventions, Inc.

#include <stdio.h>

struct Complex {
   double real;
   double img;

   bool operator<(const Complex &c1) const;
};

Complex operator+(const Complex &c1, const Complex &c2)
{
   Complex sum;

   sum.real = c1.real + c2.real;
   sum.img = c1.img + c2.img;

   return sum;
}

Complex operator-(const Complex &c1, const Complex &c2)
{
   Complex diff;

   diff.real = c1.real - c2.real;
   diff.img = c1.img - c2.img;

   return diff;
}

// Left hand operand is |*this|, the context object.  Right hand operatand is explicitly
// declared.  Left hand operand's member data are accessed by direct name.
// Right hand operand's member data require "rhs."
bool Complex::operator<(const Complex &rhs) const
{
   return real*real + img*img < rhs.real*rhs.real + rhs.img*rhs.img;
}

int main()
{
   Complex val1 = {1.0, 2.0}, val2 = {3.0, 4.0};
   Complex result;

   result = val1 + val2;
   result = result + val1 - val2;

   if (val1 < val2)   // equivalent to:  if (val1.operator<(val2))
      printf("%0.1f %0.1f\n", result.real, result.img);


   return 0;
}

// Output:
// 2.0 4.0
