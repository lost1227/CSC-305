// Reference Example
// Copyright 1995 Software Inventions, Inc.
#include <iostream>

using namespace std;

// A reference parameter refers to the original, without the need for explicit
// pointers.  Interestingly, this is rarely used.
void bump(int &i) {
   i++;
}

// By far the most common use for references is as const ref parameters.
int max(const int &i, const int &j) {
   return i > j ? i : j;
}

// Reference return is also often by const, though in certain cases nonconst refs
// are returned.  These may be used as lvalues!
int &rmax(int &refToi, int &refToj) {
   if (refToi > refToj)
      return refToi;
   else
      return refToj;
}

int &&returnLocal() {
   return 42;
}

int main()
{
   int i, j, k = 10;
   int &refToi = i, &refToj = j;
   int *pi;
   const int ci = 6;

   i = 2;
   refToi = 3;               // Set i to 3
   refToj = refToi + 1;      // Set j to 4
   refToi = j;               // Copy j into i.
   // refToi = &j;           // This won't compile.  Can't change refToi's target

   pi = &refToi;             // Point pi to i  (not to refToi)
   *pi = 5;                  // Set i to 5

   bump(j);                  // Adds 1 directly to j
   bump(refToj);             // Reference is "passed along"
   // bump(42);              // This won't compile.
   // bump(ci);              // Nor will this.  No backdoors via refs.

   i = max(j, 8);            // Set i to 8 (creates temp for 8)
   rmax(i, j) = 10;          // Set larger of i or j to 10
   rmax(i, rmax(j, k)) = 20; // Set larger of i, j or k to 20

   // C++ 11 Rvalue references
   // int &refTo6 = 6;       // Won't compile.  lref would have to be const
   int &&rvRefTo6 = 6;       // ... but this does
   int &&rvRefToExpr = (i + 1) * rvRefTo6;  // ... and even this
   // int &&rvRefToi = i;     // Can't do this.  Rv refs only to temps/dead

   cout << rvRefTo6 << " " << rvRefToExpr << " " << endl;

   rvRefTo6++;               // Implied private copy
   rvRefToExpr = rvRefToExpr + 2;
   cout << rvRefTo6 << " " << rvRefToExpr << " " << endl;

   cout << returnLocal()+1 << endl;

   return 0;
}

/*
Sample output:
6 66
7 68 43
*/
