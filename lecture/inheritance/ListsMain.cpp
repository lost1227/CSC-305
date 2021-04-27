#include <iostream>
#include "Lists.h"

using namespace std;

void ReadList(List<int> *list) {
   int val;

   do {
      cin >> val;
      if (val > 0)
         list->Add(val);
   } while (val > 0);
}

int main() {
   // List<int> *list = new List<int>();  // Won't compile
   List<int> *list1 = new ArrayList<int>();
   List<int> *list2 = new LinkedList<int>();

   ReadList(list1);
   ReadList(list2);

   list1->Print();
   list2->Print();
}

/*
2 3 42 9 -1  (Input)
3 10 -1

2 3 42 9  (Output)
10 3
*/
