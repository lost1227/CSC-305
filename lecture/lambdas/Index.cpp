#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <functional>

using namespace std;

// Extended string type has split method like a modern language
struct string_ex : public string {
   string_ex() {}
   string_ex(const string &s) : string(s) {}
   string_ex(const char *cstr) : string(cstr) {}

   vector<string> split(set<char> seps = set<char>{' ', '\t'}) const {
      vector<string> rtn;

      auto itr = begin();
      auto itr2 = itr;

      do {
         while (itr2 != end() && seps.find(*itr2) == seps.end())
            itr2++;
      
         rtn.push_back(string(itr, itr2));
         
         while (itr2 != end() && seps.find(*itr2) != seps.end())
            itr2++;
         itr = itr2;
      } while (itr != end());

      return move(rtn);
   }
};

// New using keyword instead of typedef
using IndexType = map<string, map<int, set<int>>,
 function<bool(const string &, const string &)>>;

void addWords(IndexType *index, vector<string> words, int line,
 const function<bool(const string &)> &filter) {
   int offset = 0;

   for (string &word: words) {
      if (!filter(word))
         (*index)[word][line].insert(offset);
      offset++;
   }
}

int main() {
   IndexType index{[](const string &s1, const string &s2) 
    {return s1.size() < s2.size() || s1.size() == s2.size() && s1 < s2;}};

   set<string> dropWords{"a", "an", "and", "the"};
   string_ex line;
   int lineNum = 1;

   while (getline(cin, line)) {
      addWords(&index, line.split(), lineNum++, 
       [&dropWords](const string &s){return dropWords.find(s) != dropWords.end();});
   }

   for (auto &entry: index) {
      cout << entry.first << ":";
      for (auto &lineSpec: entry.second) {
         cout << " (" << lineSpec.first << ":";
         for (auto col: lineSpec.second)
            cout << " " << col;
         cout << ")";
      }
      cout << endl;
   }

   return 0;
}

/* Example of function returning lambda
function<bool(string)> filter(const set<string> &matchStrs) {
   return [&matchStrs](string s)->bool{return matchStrs.find(s) != matchStrs.end();};
}

function<bool(string)> f = filter(mStrs);
*/

/*
This is a test of the indexing system         (input)
the indexing system
the indexing system indexing system

is: (1: 1)                                    (output)
of: (1: 4)
This: (1: 0)
test: (1: 3)
system: (1: 7) (2: 2) (3: 2 4)
indexing: (1: 6) (2: 1) (3: 1 3)
*/
