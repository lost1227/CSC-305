// C string class example
// Copyright 2004 Software Inventions, Inc.

#include <iostream>
#include <string>
#include <map>
#include <ctype.h>

using namespace std;

class CICharTraits : public char_traits<char> {
public:
   static bool eq(const char_type &c1, const char_type &c2) 
    {return toupper(c1) == toupper(c2);}
   
   static bool lt(const char_type &c1, const char_type &c2)
    {return toupper(c1) < toupper(c2);}
    
   static int compare(const char_type *c1, const char_type *c2, size_t n) {
      for (; n && eq(*c1, *c2); n--, c1++, c2++)
         ;
      return n == 0 ? 0 : lt(*c1, *c2) ? -1 : 1;
   }
};

typedef basic_string<char> string;
typedef basic_string<char, CICharTraits> Word;
typedef map<Word, int> WordMap;

void main()
{
   string line;
   int wordEnd;
   Word word;      // This works exactly like string, except for collation.
   WordMap wCount;
   WordMap::iterator itr;
   
   while (getline(cin, line)) {
      line += " "; // Guaranteed a final whitespace.
      do {
         line.erase(0, line.find_first_not_of(" \t"));
         
         if ((wordEnd = line.find_first_of(" \t")) != string::npos) {
            word = line.substr(0, wordEnd).c_str();
            wCount[word]++;
            line.erase(0, wordEnd);
         }
      } while (wordEnd != string::npos);
   }
   
   for (itr = wCount.begin(); itr != wCount.end(); itr++)
      cout << itr->first.c_str() << " appears " << itr->second
       << " times." << endl;
}

/*
Input:
This is a test of this   wordcounting program
a WOrd iS a woRd in This Test

Output:
a appears 3 times.
in appears 1 times.
is appears 2 times.
of appears 1 times.
program appears 1 times.
test appears 2 times.
This appears 3 times.
WOrd appears 2 times.
wordcounting appears 1 times.
*/
