// Implementation for List class
// Copyright 1995 Software Inventions, Inc.

// Eight major concepts: 
// 1. method definition vs declaration
// 2. scope
// 3. inline initializer
// 4. new/delete
// 5. comma operator
// 6. proper design of linked list copy
// 7. proper design of operator=
// 8. use of assertions
// 9. nullptr (C++11)

#include <cassert>
#include <iostream>
#include "List1.h"

List::List() : head(nullptr) {}

List::List(const List &src) {
   Copy(src);
}

// Note that ~List is the name, not an expression.
List::~List() {
   Delete();
}

void List::Delete() {
   DataNode *temp;

   while (head) {
      temp = head;        // Wny not: delete head; head = head->next ?
      head = head->next;
      delete temp;  // Delete temp's target.  Delete *temp
   }
}

// One deliberate bug inserted here.  Find it.
void List::Copy(const List &src) {
   DataNode *priorNode = nullptr, *temp;

   // Bug: if src is empty, head is never initialzed
   for (temp = src.head; temp; temp = temp->next) {
      if (priorNode == nullptr)
         priorNode = head = new DataNode;  // new does *not* initialize
      else {
         priorNode->next = new DataNode;
         priorNode = priorNode->next;
      }
      priorNode->data = temp->data;
      priorNode->next = nullptr;
   }
}

void List::Add(int addVal) {
   DataNode *temp;

   temp = new DataNode;
   temp->data = addVal;
   temp->next = head;
   head = temp;
}

int List::Find(int testVal) const {
   DataNode *temp;

   for (temp = head; temp && temp->data != testVal; temp = temp->next)
      ; // Standard style for bodiless for-loops
   
   assert(temp == nullptr || temp->data == testVal);
   return temp != nullptr;
}

// One intentional bug here.  Find it
void List::Drop(int dropVal) {
   DataNode *temp, *prev;

   for (temp = head; temp && temp->data != dropVal; temp = temp->next)
      prev = temp;

   if (temp) {
      if (prev)
         prev->next = prev->next->next;
      else
         head = head->next;
      // Bug: temp is not freed
      delete temp;
   }

   
}

int List::operator== (const List &rhs) const {
   DataNode *pt, *pt2;

   for (pt = head, pt2 = rhs.head; pt && pt2; pt = pt->next, pt2 = pt2->next)
      if (pt->data != pt2->data)
         return false;

   return pt == nullptr && pt2 == nullptr;
}

// This is a classic, general design for operator=
const List &List::operator=(const List &src) {
   // Check for self-assignment (list1 = list1;)
   if (this != &src) {
      Delete();
      Copy(src);
   }
   return *this;  // Why not return this ?
}
