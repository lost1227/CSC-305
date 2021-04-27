#include "String.h"

using namespace std;

void Printem(String s1, String s2)  // Copy construction, but no data copied
{
   cout << "String 1: " << s1 << endl << "String 2: " << s2 << endl;
}

void main()
{
   String string1, string2;

   cout << "Enter two strings: ";
   cin >> string1 >> string2;  // Length doesn't matter.

   if (string1 != string2)
      string1 = string2;       // Shared data.  No copy.
   Printem(string1, string2);

   string2[0] = 'X';           // Now an independent copy.
   Printem(string1, string2);
                               // Dynamically allocated storage released here.
}

/*
Enter two strings:
Test Supercalifragilisticexpialidocious
String 1: Supercalifragilisticexpialidocious
String 2: Supercalifragilisticexpialidocious
String 1: Supercalifragilisticexpialidocious
String 2: Xupercalifragilisticexpialidocious
*/