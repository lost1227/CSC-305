// STL Use Examples
// Copyright 2010 Software Inventions, Inc.

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void MapsAndSearches();
void Compounding();

const int dim = 5, rows = 3, cols = 4;

int main() {
   MapsAndSearches();
   Compounding();
}

typedef map<int, double, less<int> > Map;

void MapsAndSearches() {
   int values[5] = {31, 24, 53, 28, 11};
   vector<int> vec(values, values+5); 
   vector<int>::iterator loc;
   Map mp;
   //Map::iterator mItr;  Just use auto
   int key;
   double value;

   cout << endl << "Maps and Searches" << endl;

   loc = find(vec.begin(), vec.end(), 53);
   if (loc != vec.end())
      cout << "Found at " << loc - vec.begin() << endl;
   else
      cout << "Not found" << endl;

   do {
      pair<Map::iterator, bool> res;
      
      cin >> key >> value;
      if (key > 0) {
         res = mp.insert(Map::value_type(key, value));
         
         // Can also do mp[key] = value;
         Value &operator[](Key key) {return ??? }
         
         if (res.second)
         // or just if (mp.insert(Map::value_type(key, value)).second)
            cout << "OK" << endl;
         else
            res.first->second = value;
            cout << "Oops" << endl;
       }
   } while (key > 0);
   cout << endl;

   for (auto mItr = mp.begin(); mItr != mp.end(); mItr++)
      cout << (*mItr).first << " " << (*mItr).second << endl;
   cout << endl;

   for (cin >> key; key > 0; cin >> key) {
      mItr = mp.find(key);
      if (mItr == mp.end())
         cout << "Not found" << endl;
      else
         cout << (*mItr).first << " has value " << (*mItr).second << endl;
   }
}

typedef map<int, list<int> > MapOfLists;

void Compounding() {
   int row, col, key, val;
   vector<vector<int>> dblVec(rows, vector<int>(cols, 42));
   MapOfLists map;

   cout << endl << "Compounding" << endl;
   for (row = 0; row < rows; row++) {
      for (col = 0; col < cols; col++)
         cout << dblVec[row][col] << " "; 
      cout << endl;
   }

   cout << "Enter key value pairs ending with 0, 0:" << endl;
   do {
      cin >> key >> val;
      if (key > 0)
         map[key].push_back(val);
   } while (key > 0);

   for (auto itr = map.begin(); itr != map.end(); itr++) {
      cout << itr->first << " :";
      for (auto lItr = itr->second.begin(); 
       lItr != itr->second.end(); lItr++)
         cout << " " << *lItr;
      cout << endl;
   }
}

/* Output:

Maps and Searches
Found at 2
1 42.0
OK
8 24.0
OK
5 25.0
OK
5 24.0
Oops
3 12.0
OK
0 0.0

1 42
3 12
5 25
8 24

5
5 has value 25
2
Not found
0

Compounding
42 42 42 42 
42 42 42 42 
42 42 42 42 

Enter key value pairs ending with 0, 0:
1 3   5 3   1 2   5 6   5 7   3 9   3 2   0 0

1 : 3 2
3 : 9 2
5 : 3 6 7

--------------------------------------------
From pair.h in the stl library (slightly edited)

template <class T1, class T2>
struct pair {
    T1 first;
    T2 second;
    pair() : first(T1()), second(T2()) {}
    pair(const T1& a, const T2& b) : first(a), second(b) {}
};

--------------------------------------------
From map.h in the stl library

template <class Key, class T, class Compare, class Alloc = alloc>
class map {
public:
  typedef Key key_type;
  typedef T data_type;
  typedef pair<const Key, T> value_type;

  ...
  pair<iterator,bool> insert(const value_type& x) {
     ...
  }
*/
