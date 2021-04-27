// Implementation for list 2
// Copyright 1995 Software Inventions, Inc.

#include "List2.h"

using namespace std;

// Major concepts: 
// 1. Static data definition  
// 2. Double pointers  
// 3. Freelist 
// 4. Move semantics

List::DataNode *List::freeList = nullptr;

void List::Delete() {
   DataNode *temp;

   while (head) {
      temp = head;
      head = head->next;
      delete temp;       // or DeleteNode(temp)
   }
}

void List::Copy(const List &src) {
   DataNode **priorNode = &head, *temp;

   for (temp = src.head; temp; temp = temp->next) {
      *priorNode = new DataNode(temp->data, nullptr);  // or NewNode(temp->data, nullptr)
      priorNode = &((*priorNode)->next);
   }
}

const List &List::operator=(const List &src) {
   std::cout << "Copy assign" << endl;
   if (this != &src) {
      Delete();
      Copy(src);
   }
   return *this;
}

const List &List::operator=(List &&src) {
   std::cout << "Move assign" << endl;
   Delete();
   head = src.head;
   src.head = nullptr;
   
   return *this; 
}

List::DataNode *List::NewNode(int d, DataNode *n) {
   DataNode *rtn;

   if (freeList) {
      rtn = freeList;
      freeList = freeList->next;
      rtn->data = d;
      rtn->next = n;
   }
   else
      rtn = new DataNode(d, n);

   return rtn;
}

void List::DeleteNode(DataNode *toFree) {
   toFree->next = freeList;
   freeList = toFree;
}


int List::Find(int testVal) const {
   DataNode *temp;

   for (temp = head; temp && temp->data != testVal; temp = temp->next)
      ;
   return temp != nullptr;
}

void List::Drop(int dropVal) {
   DataNode **temp, *toDrop;

   for (temp = &head; *temp && (*temp)->data != dropVal;)
      temp = &(*temp)->next;

   if (toDrop = *temp) {
      *temp = toDrop->next;
      delete toDrop;               // or DeleteNode(toDrop)
   }
}

int List::operator== (const List &rhs) const {
   DataNode *pt, *pt2;

   for (pt = head, pt2 = rhs.head; pt && pt2; pt = pt->next, pt2 = pt2->next)
      if (pt->data != pt2->data)
         return false;

   return pt == nullptr && pt2 == nullptr;
}

istream &operator>>(istream &is, List &list) {
   int item;
   List::DataNode **end;

   list.Delete();
   end = &list.head;
   do {
      is >> item;
      if (item >= 0) {
         *end = new List::DataNode(item, nullptr);  
         // or end = List::NewNode(item, nullptr)
         end = &(*end)->next;
      }
   } while (item >= 0);

   return is;
}

ostream &operator<<(ostream &os, const List &list) {
   List::DataNode *temp;

   for (temp = list.head; temp; temp = temp->next)
      os << temp->data << ' ';

   return os;
}
