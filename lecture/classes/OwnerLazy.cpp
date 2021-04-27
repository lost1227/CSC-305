// Code for Initialization Example 1 -- Lazy owner class
// Copyright 1997, Software Inventions, Inc.

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int StrLen = 50;

class Sample {
protected:
   char *data;
public:
   Sample();
   Sample(int);
   Sample(const Sample &);
   ~Sample();
   const Sample &operator=(const Sample &);
};

Sample::Sample()
{
   data = new char[StrLen];
   sprintf(data, "Sample object default");
   cout << "Default constructing " << data << endl;
}

Sample::Sample(int i)
{
   data = new char[StrLen];
   sprintf(data, "Sample object tagged by %d", i);
   cout << "Constructing " << data << endl;
}

Sample::Sample(const Sample &s)
{
   data = new char[StrLen];
   strcpy(data, s.data);
   cout << "Copy constructing " << data << endl;
}

Sample::~Sample()
{
   cout << "Deleting " << data << endl;
   delete [] data;
}

const Sample &Sample::operator=(const Sample &src)
{
   cout << "Copying " << src.data << endl;
   if (this != &src) {
      delete [] data;
      data = new char[StrLen];
      strcpy(data, src.data);
   }
   return *this;
}

class Name {
protected:
   char *data;
public:
   Name();
   Name(int);
   Name(const Name &);
   ~Name();
   const Name &operator=(const Name &);
};

Name::Name()
{
   data = new char[StrLen];
   sprintf(data, "Name object default");
   cout << "Default constructing " << data << endl;
}

Name::Name(int i)
{
   data = new char[StrLen];
   sprintf(data, "Name object tagged by %d", i);
   cout << "Constructing " << data << endl;
}

Name::Name(const Name &s)
{
   data = new char[StrLen];
   strcpy(data, s.data);
   cout << "Copy constructing " << data << endl;
}

Name::~Name()
{
   cout << "Deleting " << data << endl;
   delete [] data;
}

const Name &Name::operator=(const Name &src)
{
   cout << "Copying " << src.data << endl;
   if (this != &src) {
      delete [] data;
      data = new char[StrLen];
      strcpy(data, src.data);
   }
   return *this;
}

// The "Lazy Owner" class provides no copy constructor, operator=, nor
// destructor.  The corresponding methods of its component objects (the
// base object and/or member objects) are automatically called instead.
// This is a viable, and in fact preferred, design when your owner class
// has no bare allocated data (like the char * member of Sample and Name)
// needing maintenance.  If your class comprises only objects that are 
// already intelligent, rely on their intelligence and save your breath.

class NamedSample : public Sample {
protected:
   Name name;
};

void main()
{
   NamedSample ns1;
   cout << endl << "Break1" << endl << endl;
   
   NamedSample ns2(ns1);
   cout << endl << "Break2" << endl << endl;
   
   ns1 = ns2;
   cout << endl << "Break3" << endl << endl;
}

/* Output:
Default constructing Sample object default
Default constructing Name object default

Break1

Copy constructing Sample object default
Copy constructing Name object default

Break2

Copying Sample object default
Copying Name object default

Break3

Deleting Name object default
Deleting Sample object default
Deleting Name object default
Deleting Sample object default
*/