// Consts Example
// Copyright 1995 Software Inventions, Inc.

#include <iostream>
using namespace std;

constexpr int ANSWER = 42;

void sample1(int *pi, int i) {
   *pi = 0;  // Affects variable in caller
   i = 0;    // Affects only local copy
}

void sample2(const int *pci) {
   *pci = 8;         // Not allowed, even if pci points to a nonconst
   cout << *pci;     // Allowed
}

void main() {
   int i, *pi;
   const int ci = ANSWER;     // Can only assign during init
   const int *pci;
   int *const cpi = &i;       // but = &ci would be forbidden

   ci = 10;
   /* OK stuff -- no direct or indirect const mods possible */

   i = ci;           // Modifiable copies are OK; original stays const.
   pci = &ci;        // Can't modify ci via pci
   pci = &i;         // Can't modify i via pci, but extra restrictions are OK.
   pci = pi;         // pci can't modify pi's referent
   *cpi = 10;        // OK -- cpi doesn't point to a const
   sample1(cpi, ci); // OK, since cpi doesn't point to const and ci is copied
   sample2(&ci);     // OK, since formal parameter is pointer to const.
   sample2(&i);      // OK, extra restrictions are allowed.

   /* Not OK -- can't modify consts directly or indirectly */

   ci = 3;           // Not OK: Cannot alter const int
   cpi = &i;         // Not OK: Cannot make constant pointer point elsewhere.
   *pci = 3;         // Not OK: pci points to const int (possibly).

   /* Not OK -- can't even set up possible indirect mod of possible const*/

   pi = &ci;         // Not OK: Might modify ci via pi.
   pi = pci;         // Not OK: Might modify *pci (possibly a const) via pi.
   sample1(&ci, i);  // Not OK: first formal param could be used to modify ci.
   sample1(pci, i);  // Not OK: first formal param might modify *pci
}
