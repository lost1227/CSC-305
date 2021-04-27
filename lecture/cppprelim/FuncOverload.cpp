// Example of function overloading and default parameters
// Copyright 1995 Software Inventions, Inc.

// Also illustration of printf.  Format specifiers:
// %s -- string
// %d or %i -- integer
// %x -- integer in hexadecimal
// %f -- float/double
// %c -- print int as character
// %##d -- print using a MINIMUM field of ## chars.  0 is default.
// %##.$$f -- print using min field of ## chars and precision of $$ digits
//
// Printf is variadic -- no checking of parameters past the format string.
// See docs for more detail on printf and its format specifiers.

#include <stdio.h>

void PrintCost(int cost) {
   printf("Total cost is $%d\n", cost);
}

void PrintCost(double cost) {
   printf("Total cost is $%0.2f\n", cost);
}

void PrintName(const char *last, const char *first = "", int salary = 0) {
   printf("%10s, %10s   $%d\n", last, first, salary);
}

int main() {
   PrintCost(10);
   PrintCost(11.234);
   PrintName("Jones", "Robert", 10000);
   PrintName("Jones", "Robert");
   PrintName("Jones");
   // PrintName("Jones", 10000);         // Results in compiler error

   return 0;
}

/*
Total cost is $10
Total cost is $11.23
     Jones,     Robert   $10000
     Jones,     Robert   $0
     Jones,              $0
*/
