#include <iostream>
#include <string.h>

using namespace std;

// The real method is called strcmp
int StrCmp(const char *s1, const char *s2)
{
   for (; *s1 != '\0' && *s2 != '\0' && *s1 == *s2; s1++, s2++)
      ;
   
   return *s1 - *s2;
}

// The real method is called strcpy
void StrCpy(char *target, const char *source)
{
   while (*target++ = *source++)
      ;
}

int main()
{
   char string1[10], string2[10], *string3;

   cout << "Enter two strings: ";
   cin >> string1 >> string2;

   if (StrCmp(string1, string2) != 0)
      StrCpy(string1, string2);
   string3 = string2;
   cout << string1 << " " << string3 << endl;

   if (StrCmp("quoted string", string1) > 0)
      StrCpy(string1, "new data");
   cout << string1 << endl;
   
   StrCpy(string1+4, "stuff");
   strcat(string2, "X");
   cout << string1 << " " << string3 << " " << strlen(string2) << endl;
   cout << string1+4 << " " << "Test String"+5 << " " << "NESW"[3] << endl;

   return 0;
}

// Output:
//
// Enter two string: professor project
// project project
// new data
// new stuff projectX 8
// stuff String W

// Exercises:
// 1. Try writing strcat
// 2. Write line to shorten a string str by 4 chars