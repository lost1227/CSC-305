// C Pointers Example
#include <iostream>

using namespace std;

void Double(float *arg)
{
   *arg = *arg + *arg;
}

void FillArray(int *array, int dim)
{
   int ndx;

   for (ndx = 0; ndx < dim; ndx++)
      array[ndx] = ndx*ndx;         // array[ndx] is same as *(array + ndx)
}

int main()
{
   int i1, i2, *iPtr1, *iPtr2, *iPtr3;
   int intArr[5];
   float flt = 10.0;

   iPtr1 = &i1;
   iPtr2 = &i2;
   cout << "iPtr1 contains " << iPtr1 << "   iPtr2 contains " << iPtr2 << endl;

   *iPtr1 = 5;
   i2 = 10;
   cout << "i1 is " << i1 << " and *iPtr2 is " << *iPtr2 << endl;

   iPtr2 = iPtr1;
   cout << "iPtr2 is " << iPtr2 << " and *iPtr2 is " << *iPtr2 << endl;
   i1 = 7;
   cout << "*iPtr1 is " << *iPtr1 << " and *iPtr2 is " << *iPtr2 << endl;

   cout << "Double of " << flt << " is ";
   Double(&flt);
   cout << flt << endl;

   FillArray(intArr, 5);     // Same as FillArray(&intArr[0], 5);
   
   // iPtr1 - intArr is the number of elements that iPtr1 is offset into intArr.
   for (iPtr1 = intArr; iPtr1 - intArr < 5; iPtr1++)
      cout << *iPtr1 << " ";
   cout << endl;

   return 0;

   // Bad lines:
   // *iPtr3 = 10;         // Ptrs have a garbage address when first declared!!
                           // Forgetting this is the most common beginners bug
   // float *fPtr = iPtr1; // Cannot mix pointer types.
   // iPtr1 = &10;         // Must have a location to take address.
}

// Output:
// iPtr1 contains 9936   iPtr2 contains 9940
// i1 is 5 and *iPtr2 is 10
// iPtr2 is 9936 and *iPtr2 is 5
// *iPtr1 is 7 and *iPtr2 is 7
// Double of 10 is 20
// 0 1 4 9 16
