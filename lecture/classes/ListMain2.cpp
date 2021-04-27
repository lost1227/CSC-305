// Main program for List 2
// Copyright 1995 Software Inventions, Inc.

#include <assert.h>
#include "List2.h"

using namespace std;

// Major concepts:
// 1. Use of copy constructor for value (NOT reference) parameters.
// 2. Use of move assignment for value (NOT reference) returns
// 2. Chaining of iostream operators
// 3. Statement scope construction

void PrintAll(const char *label, List list) {  // Normally PrintAll(const List &list)
   cout << label;
   for (ListIterator itr(&list); itr; itr++)
      cout << " " <<  *itr;

   cout << endl;
}

List Clear42s(const List &list) {
   List rtn{list};     // Make a copy to return

   while (rtn.Find(42))
      rtn.Drop(42);

   cout << "Returning from Clear42s" << endl;

   return move(rtn);   // But just return rtn is better due to RVO
}

int main() {
   List list1, list2, list3;

   cout << "Enter items to add for two lists, each terminated by -1: " << endl;
   cin >> list1 >> list2;
   cout << "You entered: " << list1 << " followed by " << list2 << endl;

   if (list1 == list2)
      cout << "Lists are the same" << endl;
   else {
      cout << "Lists are different" << endl;
      list1 = list2;
      assert(list1 == list2);
   }

   if (List().Find(10))
      cout << "Empty List has no 10s" << endl;
      
   if (!(list1 == List()))
      cout << "List 1 is nonempty" << endl;

   cout << "Testing move semantics" << endl;
   list3 = Clear42s(list1);  
   PrintAll("List 3", list3);

   return 0;
}

/* Sample run
Enter items to add for two lists, each terminated by -1:
2 8 41 -1
2 8 41 42 -1
You entered: 2 8 41  followed by 2 8 41 42
Lists are different
Copy assign
List 1 is nonempty
Testing move semantics
X(X&)
Returning from Clear42s
X(X&&)
Move assign
X(X&)
List 3 2 8 41

W/O move(rtn) 
Enter items to add for two lists, each terminated by -1:
2 8 41 -1
2 8 41 42 -1
You entered: 2 8 41  followed by 2 8 41 42
Lists are different
Copy assign
List 1 is nonempty
Testing move semantics
X(X&)
Returning from Clear42s
Move assign
X(X&)
List 3 2 8 41
*/
