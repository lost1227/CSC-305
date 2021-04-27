// Main for List class
// Copyright 1995 Software Inventions, Inc.

// Major concepts:
//
// 1. Include files
// 2. Namespaces
// 3. Statement scope construction
// 4. constexpr functions

#include <iostream>
#include <cassert>
#include "List1.h"

using namespace std;

constexpr int ANSWER = 42;
constexpr int sqr(int x) {return x*x;}
constexpr int SQUARE_ANSWER = sqr(ANSWER);  // Evaluates at compile time

int main() {
   List list1, list2;
   int temp;

   cout << "Enter ints to add for list 1 terminated by -1: ";
   do {
      cin >> temp;
      if (temp >= 0)
         list1.Add(temp);
   } while (temp >= 0);

   cout << "Enter ints to add for list 2 terminated by -1: ";
   do {
      cin >> temp;
      if (temp >= 0)
         list2.Add(temp);
   } while (temp >= 0);

   cout << "Squares of all ints in list 1: " << endl;
   for (ListIterator itr{&list1}; itr.Ok(); itr.Next())
      cout << itr.Current()*itr.Current() << " ";
   cout << endl;

   if (list1.Find(SQUARE_ANSWER))
      list1.Drop(SQUARE_ANSWER);

   if (list1 == list2)
      cout << "Lists are the same\n";
   else {
      list1 = list2;
      cout << "Squares of all ints in list 1: " << endl;
      for (ListIterator itr{&list1}; itr.Ok(); itr.Next())
         cout << sqr(itr.Current()) << " ";                // Runs at runtime
      cout << endl;
   }

   return 0;
}

/*
Enter ints to add for list 1 terminated by -1: 42 1 3 2 -1
Enter ints to add for list 2 terminated by -1: 1 3 2 -1
Squares of all ints in list 1:
4 9 1 1764
Lists are the same

Enter ints to add for list 1 terminated by -1: 1 2 3 4 -1
Enter ints to add for list 2 terminated by -1: 5 6 7 8 -1
Squares of all ints in list 1:
16 9 4 1
Squares of all ints in list 1:
64 49 36 25
*/ 
