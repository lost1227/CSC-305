#include <iostream>
using namespace std;

const int DIM = 16;

// Dumb/simple function
int AddOne(int val) {
   return val + 1;
}
   
void ReadArray(int (*array)[DIM]) {   // or int array[][DIM]
   int row, col;                      // ... but not int *array[DIM]

   for (row = 0; row < DIM; row++)
      for (col = 0; col < DIM; col++)
         cin >> array[row][col];      // or (*(array+row))[col]
}

int **Answer1(void (*)(int (*)[DIM])) {
   return 0;
}

void (*Answer2())(int (*)[DIM]) {
   return ReadArray;
}

int main() {
   int i1, i2, i3, *p1, *p2, *p3, image[DIM][DIM];
   // A pointer to an array of DIM integers
   int (*ptr2Arr)[DIM] = image;
   // An array of DIM pointers to integers
   int *arrOfPtr[3] = {&i1, &i2, &i3};
   int (**dblPtr2Arr)[DIM] = &ptr2Arr;
   int *(*ptr2arrOfPtr)[3] = &arrOfPtr;
   int (*fPtr)(int) = AddOne;
   void (*fPtr2)(int (*)[DIM]) = ReadArray;
   
   ReadArray(image);
   (*fPtr2)(image);      // or fn(image)
   
   // Some other interesting declarations.  Describe each, and initialize each
   // using prior variables.  For arrays, you may use the same item repeatedly 
   // to initialize.
   int **v0[2];
   int (*v1)[DIM][DIM];
   int **v2[2][3];
   int *(*v3[3])[3];
   
   // Initializing this one will take an earlier bit of code.
   int **(*v4)(void (*)(int (*)[DIM]));
   // v4 is a function pointer that takes
   //    a function pointer that takes
   //       a pointer to an integer array of DIM items
   //       and returns void
   //    and returns an int**

   // Ditto
   void (*(*v5)())(int (*)[DIM]);
   // v5 is a function pointer that takes no arguments
   // and returns a function pointer that
   //    takes a pointer to an array of DIM items
   //    and returns an int

   
   return 0;
}

// Declare (for each, a variable x, plus typedef t and an allocation):
// 1. 10-element array of double pointers to 5 element arrays of ints

// int (**a[10])[5];

// 2. 5-element array of double pointers to functions taking two ints and
//    returning a pointer to an array of 10 integers
// int (*(**arr[5])(int, int))[10]

// 3. double ponter to a function that accepts a pointer to a function that
//    takes two floats and returns an int, and which returns a pointer to a
//    function that takes two floats and returns an int
//
// 4. What type is f, assuming this compiles:
//    f = (int **(*(*A)[10])(int (*p)(int), int)) ptr;
