// Code for Casting Example 1
// Copyright 1995 Software Inventions, Inc.

/*
Casting1.cpp is an example program that traces calls to constructors (including
a copy constructor), the destructor, and the operator= member function.  Note
in particular that a copy constructor is called on all value parameter passes
and value returns.

Be sure to trace every line of output for casting1.cpp and its companion
example casting2.cpp.  Be sure you understand why each line appears.
*/

#include <stdio.h>
#include <string.h>

#define STRLEN 50

class Sample {
   char *data;
public:
   Sample(int);
   Sample(const Sample &);
   Sample(Sample &&);
   ~Sample();
   void operator=(const Sample &);
   void Print() const;
};

Sample::Sample(int i) {
   data = new char[STRLEN];
   sprintf(data, "Sample object %d", i);
   printf("Constructing %s\n", data);
}

Sample::Sample(const Sample &s) {
   data = new char[STRLEN];
   strcpy(data, s.data);
   printf("Constructing %s via X(X&)\n", data);
}

Sample::Sample(Sample &&s) {
   data = s.data;
   s.data = nullptr;
   printf("Constructing %s via X(X&&)\n", data);
}

Sample::~Sample() {
   printf( "Deleting %s\n", data);
   if (data)
      strncpy(data, "junked", 6);
//   delete [] data;  Don't actually delete, so we can watch what happens.
}

void Sample::operator=(const Sample &source) {
   printf("Operator= -- deleting %s and copying %s\n", data, source.data);
   if (this != &source) {
      strncpy(data, "junked", 6);
      //delete [] data;
      data = new char[STRLEN];
      strcpy(data, source.data);
   }
}

void Sample::Print() const {
   printf( "Printing %s\n", data);
}

void f1(Sample s) {  // Pass in by value
   printf( "Performing f1\n");
   s.Print();
}

void f2(const Sample &s) { // Pass in by reference
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

Sample f5(Sample &s) {  // Pass in by reference; return by value
   printf( "Performing f5\n");
   return s;          // Copy constructor called
}

Sample f6(Sample s) {   // Pass by value; return by value -- 2 constructor calls
   printf( "Performing f6\n");
   return s;            // Move constructor called
}

int main() {
   Sample s1(1), s2(2), s3(3);  // Old-fashioned constructor call

   printf( "Passing Samples to f1 and f2\n");
   f1(s1);       // Copy constructor called
   f2(s1);

   printf( "\nPassing integers to f1 and f2\n");
   f1(4);        // Int constructor called
   f2(4);

   printf("\nDirect use of return by value -- f3\n");
   f3(6).Print();
   printf("\nAssignment of return by value -- f3\n");
   s1 = f3(5);   // Operator= assign.
   s1.Print();

   /* Compiler warns against this
   printf("\nUse of reference-returned local -- f4\n");
   f4(6).Print();  // Blows up the app (fortunately)
   */

   printf("\nIn by reference, out by value\n");
   s1 = f5(s2);  // Copy construtor return and operator= assign
   s1.Print();
   s2.Print();

   printf("\nIn and out by value\n");
   s2 = f6(s3);  // Copy constructor pass and return; Operator= assign.
   s2.Print();
   s3.Print();

   printf("\nPassing f6 result straight to f1 (with RVO)\n");
   f1(f6(s3));

   printf("\nDone with main\n");
   return 0;
}

/* Output:
Constructing Sample object 1
Constructing Sample object 2
Constructing Sample object 3
Passing Samples to f1 and f2
Constructing Sample object 1 via X(X&)
Performing f1
Printing Sample object 1
Deleting Sample object 1
Performing f2
Printing Sample object 1

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
Operator= -- deleting Sample object 1 and copying Sample object 5
Deleting Sample object 5
Printing Sample object 5

In by reference, out by value
Performing f5
Constructing Sample object 2 via X(X&)
Operator= -- deleting Sample object 5 and copying Sample object 2
Deleting Sample object 2
Printing Sample object 2
Printing Sample object 2

In and out by value
Constructing Sample object 3 via X(X&)
Performing f6
Constructing Sample object 3 via X(X&&)
Operator= -- deleting Sample object 2 and copying Sample object 3
Deleting Sample object 3
Deleting (null)
Printing Sample object 3
Printing Sample object 3

Passing f6 result straight to f1
Constructing Sample object 3 via X(X&)
Performing f6
Constructing Sample object 3 via X(X&&)
Performing f1
Printing Sample object 3
Deleting Sample object 3
Deleting (null)

Done with main
Deleting Sample object 3
Deleting Sample object 3
Deleting Sample object 2
*/
