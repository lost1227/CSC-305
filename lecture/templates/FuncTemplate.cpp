#include <iostream>
using namespace std;
#include "List2.h"

// Major concepts:
// 1. General idea of template, instantiation, code emission
// 2. Implicit instantiation.
// 3. Explicit instantiation.
// 4. A template is not a method!
// 5. Template code implies restrictions on instantiating type.

template <class T>
T Max(T value1, T value2) {
   return value1 > value2 ? value1 : value2;
}

template <class T1, class T2>
T1 Min(T1 value1, T2 value2) {
   if (value1 < value2)
      return value1;
   else
      return value2;
}

void main()
{
   int i = 100, j = 2000;
   float a = 3.0, b = 4.5;
   char c = 100;
   List lst1, lst2;

   // a = Max<float>(a, b);
   // i = Max<int>(i, j);
   
   cout << Max(i, j) << endl;          // or Max<int>(i, j)
   cout << Max(a, b) << endl;          // or Max<float>(a, b)
   cout << Max(a, (float)j) << endl;
   cout << Max<double>(i, j) << endl;

   cout << Min(j, c) << endl;
   cout << Min(c, j) << endl;
   cout << Min<int, int>(c, j) << endl;   
   cout << Min<List, List>(lst1, lst2);  // Gives weird template err
}

/* Output:
2000
4.5
2000
2000

100
d
100
*/