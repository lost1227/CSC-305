// Code for Initialization Example 1 -- Standard owner class
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

Sample::Sample() {
   data = new char[StrLen];
   sprintf(data, "Sample object default");
   cout << "Default constructing " << data << endl;
}

Sample::Sample(int i) {
   data = new char[StrLen];
   sprintf(data, "Sample object tagged by %d", i);
   cout << "Constructing " << data << endl;
}

Sample::Sample(const Sample &s) {
   data = new char[StrLen];
   strcpy(data, s.data);
   cout << "Copy constructing " << data << endl;
}

Sample::~Sample() {
   cout << "Deleting " << data << endl;
   delete [] data;
}

const Sample &Sample::operator=(const Sample &src) {
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

Name::Name() {
   data = new char[StrLen];
   sprintf(data, "Name object default");
   cout << "Default constructing " << data << endl;
}

Name::Name(int i) {
   data = new char[StrLen];
   sprintf(data, "Name object tagged by %d", i);
   cout << "Constructing " << data << endl;
}

Name::Name(const Name &s) {
   data = new char[StrLen];
   strcpy(data, s.data);
   cout << "Copy constructing " << data << endl;
}

Name::~Name() {
   cout << "Deleting " << data << endl;
   delete [] data;
}

const Name &Name::operator=(const Name &src) {
   cout << "Copying " << src.data << endl;
   if (this != &src) {
      delete [] data;
      data = new char[StrLen];
      strcpy(data, src.data);
   }
   return *this;
}


class NamedSample : public Sample {
protected:
   Name name;
public:
   NamedSample(int);
   NamedSample(const NamedSample &);
   ~NamedSample();
   const NamedSample &operator=(const NamedSample &);
};

NamedSample::NamedSample(int tag) : name(0), Sample(tag) {
   cout << "NamedSample integer constructor" << endl;
}

NamedSample::NamedSample(const NamedSample &ns) : name(ns.name), Sample(ns) {
   cout << "NamedSample copy constructor" << endl;
}

NamedSample::~NamedSample() {
   cout << "NamedSample destructor" << endl;
}

const NamedSample &NamedSample::operator=(const NamedSample &s) {
   cout << "Doing NamedSample assign" << endl;
   Sample::operator=(s);
   name = s.name;
   return *this;
}

int main() {
   NamedSample ns1(20);
   cout << endl << "Break1" << endl << endl;
   NamedSample ns2(ns1);
   cout << endl << "Break2" << endl << endl;
   ns1 = ns2;
   cout << endl << "Break3" << endl << endl;
   return 0;
}

/*
Constructing Sample object tagged by 20
Constructing Name object tagged by 0
NamedSample integer constructor

Break1

Copy constructing Sample object tagged by 20
Copy constructing Name object tagged by 0
NamedSample copy constructor

Break2

Doing NamedSample assign
Copying Sample object tagged by 20
Copying Name object tagged by 0

Break3

NamedSample destructor
Deleting Name object tagged by 0
Deleting Sample object tagged by 20
NamedSample destructor
Deleting Name object tagged by 0
Deleting Sample object tagged by 20
*/