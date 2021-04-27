// STL Use Examples
// Copyright 1997 Software Inventions, Inc.

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void ContainersAndIterators();
void ListsAndConstructions();
void Comparisons();

const int dim = 5, rows = 3, cols = 4;

int main() {
   ContainersAndIterators();
   ListsAndConstructions();
   Comparisons();
}

void PrintVector(const vector<int> &vec) {
   vector<int>::const_iterator vItr;

   // Call const version of begin, returning vector<int>::const_iterator
   for (vItr = vec.begin(); vItr != vec.end(); vItr++)
      cout << *vItr << " ";

   // Or in C++11
   // for (auto vItr = vec.begin(); vItr != vec.end(); vItr++)
   //    cout << *vItr << " ";

   // Or even
   // for (auto &iVal : vec)
   //    cout << iVal << " ";

   cout << endl;
}

void ContainersAndIterators() {
   int key, ndx, item;
   vector<int> vec(dim);
   vector<int>::iterator loc;
   int values[5] = {31, 24, 53, 28, 11};

   cout << endl << "Containers and Iterators" << endl;
   cout << "Enter values: ";
   for (ndx = 0; ndx < dim; ndx++)
      cin >> vec[ndx];

   cin >> item;
   vec.push_back(item);  // Adds extra space, too.

   cout << "Original value: ";
   PrintVector(vec);

   vec.insert(vec.begin()+2, 10);
   cout << "After insert: ";
   PrintVector(vec);

   sort(vec.begin(), vec.end());
   cout << "After sort: ";
   PrintVector(vec);

   loc = unique(vec.begin(), vec.end());
   cout << "After unique: ";
   PrintVector(vec);

   vec.erase(loc, vec.end());
   cout << "After erase: ";
   PrintVector(vec);
   // Or, vec.erase(unique(vec.begin(), vec.end()), vec.end());

   sort(values, values + 5);

   for (int i = 0; i < 5; i++)
      cout << values[i] << " ";
   cout << endl;
}

void ListsAndConstructions() {
   int values[5] = {31, 24, 53, 28, 11};
   vector<int> vec(values, values+5);
   // C++11: vector<int> vec{31, 24, 53, 28, 11};
   vector<int> allZeros(10, 0);

   cout << endl << "Lists and Constructions" << endl;
   PrintVector(vec);
   // or just PrintVector(vector<int>(values, values + 5));

   PrintVector(allZeros);

   list<int> lst(vec.begin(), vec.end());

   if (equal(lst.begin(), lst.end(), vec.begin()))
      cout << "Copy worked correctly" << endl;
}


int IsLessMod3(int i1, int i2) {
   return i1 % 3 < i2 % 3;
}

void Comparisons() {
   int values[5] = {31, 24, 53, 28, 11};
   vector<int> vec(values, values+5); 
   greater<int> comparator; 

   cout << endl << "Comparisons" << endl;
   sort(vec.begin(), vec.end(), IsLessMod3);
   cout << "After mod 3 sort: ";
   PrintVector(vec);
   
   if (comparator(3, 2))
      cout << "Yep, 3 is greater than 2" << endl;
      
   sort(vec.begin(), vec.end(), comparator);
   // or, just sort(vec.begin(), vec.end(), greater<int>());
   cout << "After reverse sort: ";
   PrintVector(vec);
}

/* 
Output:

Containers and Iterators
Enter values: 1 2 6 2 4 2
Original value: 1 2 6 2 4 2 
After insert: 1 2 10 6 2 4 2 
After sort: 1 2 2 2 4 6 10 
After unique: 1 2 4 6 10 2 2
After erase: 1 2 4 6 10
11 24 28 31 53 

Lists and Constructions
31 24 53 28 11 
0 0 0 0 0 0 0 0 0 0 
Copy worked correctly

Comparisons
After mod 3 sort: 24 31 28 53 11 
Yep, 3 is greater than 2
After reverse sort: 53 31 28 24 11 

---------------------------------------------
From function.h in the stl library (slightly edited)

template <class T>
struct greater {
    bool operator()(const T& x, const T& y) const { return Y < x; }
};

---------------------------------------------
From algorithm in the stl library

template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value) {
    while (first != last && *first != value) ++first;
    return first;
}

Example of algorithm using a function object (simpler than "sort" algorithm)

template <class ForwardIterator, class BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last,
 BinaryPredicate binary_pred) {
    
    if (first == last) return last;
    
    ForwardIterator next = first;
    while(++next != last) {
       if (binary_pred(*first, *next)) return first;
       first = next;
    }
    return last;
}
*/
