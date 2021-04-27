// Header file for List2
// Copyright 1995 Software Inventions, Inc.

#ifndef LIST2_H
#define LIST2_H

#include <iostream>
#include <assert.h>

// Major concepts: 
// 1. compound include files  i
// 2. inline methods  
// 3. static data/methods  
// 4. friend functions for stream operators
// 5. Move semantics

class List {
   friend class ListIterator;

   struct DataNode {
      int data;
      DataNode *next;
      
      DataNode(int d, DataNode *n) : data{d}, next{n} {}
   };
   
   DataNode *head = nullptr;
   static DataNode *freeList;  // List of recyclable nodes

   void Delete();
   void Copy(const List &src);

   static DataNode *NewNode(int d, DataNode *n);
   static void DeleteNode(DataNode *toFree);

public:
   List() : head{nullptr}            {}
   ~List()                           {Delete();}

   List(const List &src) : head{nullptr}  {std::cout << "X(X&)\n"; Copy(src);}
   List(List &&src) : head{src.head} {std::cout << "X(X&&)\n"; src.head = nullptr;}

   const List &operator=(const List &src);
   const List &operator=(List &&src);

   void Add(int addVal)              {head = new DataNode(addVal, head);}
                                            // or NewNode(addVal, head)
   int  Find(int testVal) const;
   void Drop(int dropVal);
   int  operator== (const List &rhs) const;

   // These are not member functions
   friend std::istream &operator>> (std::istream &is, List &list);
   friend std::ostream &operator<< (std::ostream &os, const List &list);
};

class ListIterator {
   const List *obj;
   const List::DataNode *current;

public:
   ListIterator(const List *o) : obj{o}, current{o->head} {}

   void operator++(int)          {if (current) current = current->next;}
   operator int() const          {return current != nullptr;}
   const int &operator*() const {assert(current); return current->data;}
   void Reset()                  {current = obj->head;}
   
   bool operator==(const ListIterator &rhs) const
    {return obj == rhs.obj && current == rhs.current;}
};
#endif
