// Code for Casting Example 2
// Copyright 1995 Software Inventions, Inc.

/*
Casting2.cpp is a variation of casting1.cpp, with the copy constructor and
operator= member function missing from Sample.  In all other respects it is
identical to casting1.cpp.  Note in particular the lines for which a "bitwise
copy" warning appears.  This warning is notifying you that a direct memory
copy is being made, rather than a copy via the operator= or copy constructor.
This is a problem if you have a class that must copy dynamically allocated
data along with the actual object itself.  In particular:

1. A sample object can have junked data in it without having been explicitly
   deleted if a memberwise copy of it has been deleted.

2. C++ does memberwise copies when an object is passed or returned by value
   without any type conversion, and when an object is assigned without an
   operator=
*/

#include <stdio.h>
#include <string.h>

#define STRLEN 50

class Sample {
   char *data;
public:
   Sample(int);
   ~Sample();
   void Print() const;
};

Sample::Sample(int i) {
   data = new char[STRLEN];
   sprintf(data, "Sample object %d", i);
   printf( "Constructing %s\n", data);
}

Sample::~Sample() {
   printf( "Deleting %s\n", data);
   strncpy(data, "junked", 6);
//   delete [] data;  Don't actually delete, so we can watch what happens.
}

void Sample::Print() const {
   printf( "Printing %s\n", data);
}

void f1(Sample s) {  // Pass in by value
   printf( "Performing f1\n");
   s.Print();
}

void f2(const Sample &s) {  // Pass in by reference
   printf( "Performing f2\n");
   s.Print();
}

Sample f3(int i) { // Return by value
   printf( "Performing f3\n");
   return i;
}

const Sample &f4(int i) { // Return temporary by const ref
   printf( "Performing f4\n");
   return i;
}

Sample f5(Sample &s) { // Pass in by reference; return by value
   printf( "Performing f5\n");
   return s;          // Memberwise copy
}

Sample f6(Sample s) {   // Pass by value; return by value
   printf( "Performing f6\n");
   return s;          // Memberwise copy
}

int main() {
   Sample s1(1), s2(2), s3(3);

   printf( "Passing Samples to f1 and f2\n");
   f1(s1);       // Memberwise copy
   f2(s1);

   printf( "\nPassing integers to f1 and f2\n");
   f1(4);
   f2(4);

   printf("\nDirect use of return by value -- f3\n");
   f3(6).Print();
   printf("\nAssignment of return by value -- f3\n");
   s1 = f3(5);   // Memberwise assign.
   s1.Print();

   //printf("\nUse of reference-returned local -- f4\n");
   //f4(6).Print();  // Blows up the app

   printf("\nIn by reference, out by value\n");
   s1 = f5(s2);  // Memberwise copies on both return and assign.
   s1.Print();
   s2.Print();

   printf("\nIn and out by value\n");
   s2 = f6(s3);  // Memberwise copies on both return and assign.
   s2.Print();
   s3.Print();

   printf("\nPassing f6 result straight to f1 (with RVO)\n");
   f1(f6(s3));   // Memberwise, memberwise, memberwise....

   printf("\nDone with main\n");

   return 0;
}

/* Output:
Constructing Sample object 1
Constructing Sample object 2
Constructing Sample object 3
Passing Samples to f1 and f2
Performing f1
Printing Sample object 1
Deleting Sample object 1
Performing f2
Printing junked object 1

Passing integers to f1 and f2
Constructing Sample object 4
Performing f1
Printing Sample object 4
Deleting Sample object 4
Constructing Sample object 4
Performing f2
Printing Sample object 4
Deleting Sample object 4

Direct use of return by value -- f3
Performing f3
Constructing Sample object 6
Printing Sample object 6
Deleting Sample object 6

Assignment of return by value -- f3
Performing f3
Constructing Sample object 5
Deleting Sample object 5
Printing junked object 5

In by reference, out by value
Performing f5
Deleting Sample object 2
Printing junked object 2
Printing junked object 2

In and out by value
Performing f6
Deleting Sample object 3
Deleting junked object 3
Printing junked object 3
Printing junked object 3

Passing f6 result straight to f1 (with RVO)
Performing f6
Performing f1
Printing junked object 3
Deleting junked object 3
Deleting junked object 3

Done with main
Deleting junked object 3
Deleting junked object 3
Deleting junked object 2
*/
