#ifndef LIST7_H
#define LIST7_H

#include <iostream>

// Header file for List template
// Copyright 1995 Software Inventions, Inc.
// This is a "professional" version of our List class.  In particular:
// 1. It's a template.
// 2. It passes the Base type by const &, to avoid potential big copies.
// 3. It avoids default-construction of the Base type, and makes minimal(?)
//    assumptions about the Base type in general.
// 4. The Iterator template uses overloaded operations to make it behave like
//    a pointer.  (The STL iterators work this way as well.)

template <class Base> class List;
template <class Base> class ListIterator;
template <class Base> std::istream &operator>>(std::istream &, List<Base> &);
template <class Base> std::ostream &operator<<(std::ostream &, const List<Base> &);

template <class Base>
class List {
   friend class ListIterator<Base>;

   struct DataNode {
      Base data;
      DataNode *next;

      DataNode(const Base &d, DataNode *n) : data(d), next(n) {}
   };
   DataNode *head;
   static DataNode *freeList;

   void Delete(void);
   void Copy(const List<Base> &src);

   static DataNode *NewNode(const Base &d, DataNode *n);
   static void DeleteNode(DataNode *toFree);

public:
   List(void) : head(0)                  {}
   List(std::initializer_list<Base> iVals) : head(0)
    {for (auto &val: iVals) Add(val);}

   List(const List<Base> &src) : head(0) {Copy(src);}
   List(List<Base> &&src) : head{src.head} {src.head = nullptr;}

   ~List(void)                           {Delete();}

   const List<Base> &operator=(const List<Base> &src)
    {if (this != &src) {Delete(); Copy(src);} return *this;}
    
   const List<Base> &operator=(List<Base> &&src) 
    {Delete(); head = src.head; src.head = nullptr; return *this;} 

   void Add(const Base &addVal)          {head = NewNode(addVal, head);}
   int  Find(const Base &testVal) const;
   void Drop(const Base &dropVal);
   int  operator== (const List<Base> &rhs) const;

   friend std::istream &operator>><Base> (std::istream &is, List<Base> &list);
   friend std::ostream &operator<<<Base> (std::ostream &os, const List<Base> &list);
};


template <class Base>
class ListIterator {
   const List<Base> *obj;
   typename List<Base>::DataNode *current;

public:
   ListIterator(const List<Base> *o) : obj(o), current(o->head) {}

   void operator++(int)              {if (current) current = current->next;}
   operator int(void) const          {return current != 0;}
   const Base &operator*(void) const {assert(current); return current->data;}

   bool operator==(const ListIterator<Base> &rhs)
    {return obj == rhs.obj && current == rhs.current;}
};

template <class Base>
typename List<Base>::DataNode *List<Base>::freeList = 0;

template <class Base>
void List<Base>::Delete(void)
{
   DataNode *temp;

   while (head) {
      temp = head;
      head = head->next;
      DeleteNode(temp);
   }
}

template <class Base>
void List<Base>::Copy(const List<Base> &src)
{
   DataNode **priorPtr = &head, *temp;

   for (temp = src.head; temp; temp = temp->next) {
      (*priorPtr) = NewNode(temp->data, 0);
      priorPtr = &(*priorPtr)->next;
   }
}

template <class Base>
typename List<Base>::DataNode *List<Base>::NewNode(const Base &d, DataNode *n)
{
   DataNode *rtn;

   if (freeList) {
      rtn = freeList;
      freeList = freeList->next;
      rtn->data = d;   // Note this places certain restrictions on d
      rtn->next = n;
   }
   else
      rtn = new DataNode(d, n);

   return rtn;
}

template <class Base>
void List<Base>::DeleteNode(DataNode *toFree)
{
   toFree->next = freeList;
   freeList = toFree;
}

template <class Base>
int List<Base>::Find(const Base &testVal) const
{
   DataNode *temp;

   // And even more restrictions on Base
   for (temp = head; temp && !(temp->data == testVal); temp = temp->next)
      ;

   return temp != 0;
}

template <class Base>
void List<Base>::Drop(const Base &dropVal) {
   DataNode **temp, *toDrop;

   // And even more restrictions.  Would List<List<int> > now work?
   for (temp = &head; *temp && (*temp)->data != dropVal;)
      temp = &(*temp)->next;

   if (toDrop = *temp) {
      *temp = toDrop->next;
      DeleteNode(toDrop);
   }
}

template <class Base>
int List<Base>::operator==(const List<Base> &rhs) const {
   DataNode *pt, *pt2;

   for (pt = head, pt2 = rhs.head; pt && pt2; pt = pt->next, pt2 = pt2->next)
      if (!(pt->data == pt2->data))
         return false;

   return pt == 0 && pt2 == 0;
}

template <class Base>
std::istream &operator>>(std::istream &is, List<Base> &list) {
   Base item;
   typename List<Base>::DataNode **end;

   list.Delete();
   end = &list.head;
   do {
      is >> item;
      if (item >= 0) {            // What about List<List<int> > ??
         *end = List<Base>::NewNode(item, 0);
         end = &(*end)->next;
      }
   } while (item >= 0);

   return is;
}

template <class Base>
std::ostream &operator<<(std::ostream &os, const List<Base> &list) {
   typename List<Base>::DataNode *temp;

   for (temp = list.head; temp; temp = temp->next)
      os << temp->data << ' ';

   return os;
}

#endif
