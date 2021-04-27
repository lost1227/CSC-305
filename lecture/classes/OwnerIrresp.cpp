// Code for Initialization Example 1 -- Irresponsible owner class
// Copyright 1995, Software Inventions, Inc.

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

// The "Irresponsible Owner" class provides a copy constructor and operator=,  
// but fails to properly implement them.  Providing these methods
// automatically turns off the default "lazy owner" behavior, and you must
// completely implement the methods for each member datum or base object.

class NamedSample : public Sample {
protected:
   Name name;
public:
   NamedSample(int);
   NamedSample(const NamedSample &);
   ~NamedSample();
   const NamedSample &operator=(const NamedSample &);
};

// Neglects to construct name.  Default construction results.
NamedSample::NamedSample(int size) : Sample(size)
{
   cout << "NamedSample integer constructor" << endl;
}

// Neglects to copy construct subcomponents.  Default construction, not
// copy construction, results.  Assignment takes care of "name", but results
// in extra work since the default construction is overwritten.
NamedSample::NamedSample(const NamedSample &ns)
{
   cout << "NamedSample copy constructor" << endl;
   name = ns.name;
}

// Destructor is safe either way.  Subobjects automatically destruct.
NamedSample::~NamedSample()
{
   cout << "NamedSample destructor" << endl;
}

// This is a disaster.  It turns off automatic behavior but does nothing else.
const NamedSample &NamedSample::operator=(const NamedSample &s)
{
   cout << "Doing NamedSample assign" << endl;
   return *this;
}

void main()
{
   NamedSample ns1(20);
   cout << endl << "Break1" << endl << endl;
   
   NamedSample ns2(ns1);
   cout << endl << "Break2" << endl << endl;
   
   ns1 = ns2;
   cout << endl << "Break3" << endl << endl;
}





/* Output:
Constructing Sample object tagged by 20
Default constructing Name object default
NamedSample integer constructor

Break1

Default constructing Sample object default
Default constructing Name object default
NamedSample copy constructor
Copying Name object default

Break2

Doing NamedSample assign

Break3

NamedSample destructor
Deleting Name object default
Deleting Sample object default
NamedSample destructor
Deleting Name object default
Deleting Sample object tagged by 20
*/
