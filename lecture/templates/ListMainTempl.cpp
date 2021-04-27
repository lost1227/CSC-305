#include <iostream>
#include <cassert>
#include "ListTempl.h"

// Main program for ListTempl

using namespace std;

template <class Base>
void PrintSquares(const List<Base> &list)
{
   cout << "Squares of all values in list: " << endl;

   for (ListIterator<Base> itr(&list); itr; itr++)
      cout << *itr * *itr << " ";
   cout << endl;
}

int main()
{
   List<int> iList1, iList2;
   List<float> fList;
   List<List<int>> listList1, listList2;
   List<int> initList = {2, 3, 5, 7, 11, 13};

   iList1.Add(2);
   fList.Add(1.5);

   cout << "Enter items to add for two lists, each terminated by -1: " << endl;
   cin >> iList1 >> iList2;

   if (iList1 == iList2)
      cout << "Integer Lists are the same\n";
   else
      cout << "Integer Lists are different\n";

   listList1.Add(iList1);
   listList1.Add(iList2);
   listList2 = listList1;
   assert(listList2 == listList1);

   PrintSquares(iList1);
   PrintSquares(fList);

   if (listList2.Find(iList1))
      cout << "iList1 is in listList2" << endl;
      
   cout << "Output of listList2:" << endl << listList2 << endl;

   cout << "List-initialized list: " << initList << endl;

   // These won't compile:
   //
   // listList1.Add(fList);
   // if (fList == iList1);
   // PrintSquares(listList1);
   // listList1.Drop(iList1);

   return 0;
}

/*
Enter items to add for two lists, each terminated by -1:
2 3 7 -1
3 2 7 -1
Integer Lists are different
Squares of all values in list:
4 9 49
Squares of all values in list:
2.25
iList1 is in listList2
Output of listList2:
3 2 7  2 3 7
*/
