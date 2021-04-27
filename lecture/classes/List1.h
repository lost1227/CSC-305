// Header file for List class
// Copyright 1995 Software Inventions, Inc.

// Ten major concepts:
// 1. nested class
// 2. default constructor
// 3. copy constructor,
// 4. destructor
// 5. operator overload method,
// 6. concept of operator=
// 7. public/private scope
// 8. friend classes
// 9. iterators
// 10. const methods

class List {
   friend class ListIterator;

   struct DataNode {
      int data;
      DataNode *next;
   };
   DataNode *head;

   void Delete();
   void Copy(const List &src);

public:
   List();       
   List(const List &src);
   ~List(); 
   void Add(int addVal);
   int  Find(int testVal) const;
   void Drop(int dropVal);
   int  operator== (const List &rhs) const;
   const List &operator=(const List &src);
};

class ListIterator {
   const List *obj;               // The list we're traversing
   const List::DataNode *current; // The node we're on

public:
   ListIterator(const List *o) : obj(o), current(o->head) {};

   void Next()          {if (current) current = current->next;}
   int  Ok() const      {return current != nullptr;}
   int  Current() const {assert(current); return current->data;}
   void Reset()         {current = obj->head;}
};
