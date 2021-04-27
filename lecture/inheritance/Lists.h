#ifndef LISTS_H
#define LISTS_H
#include <iostream>
#include <string.h>

/* Concepts
 * 1. Pure virtual functions and abstract base classes or "interfaces"
 * 2. Interaction of templates and inheritance
 * 3. Deleted member functions
 * 4. Simple example of how STL list and vector classes work
 */

template <class T>
class List {
public:
   virtual ~List() {};
   virtual void Add(const T&) = 0;
   virtual void Print() const = 0;
   void operator=(List &) = delete;
};

template <class T>
class LinkedList : public List<T> {
   struct Node {
      T data;
      Node *next;
      Node(T d, Node *n) : data(d), next(n) {}
   };

   Node *head = 0;

public:
   LinkedList() {}
   LinkedList(const LinkedList<> &src) {
      Node **priorNode = &head, *temp;

      for (temp = src.head; temp; temp = temp->next) {
         *priorNode = new Node(temp->data, nullptr);
         priorNode = &((*priorNode)->next);
      }
   }

   ~LinkedList() override {
      Node *temp;

      while (head) {
         temp = head;
         head = head->next;
         delete temp;
      }
   }

   void Add(const T &d) override {head = new Node(d, head);}

   void Print() const override {
      for (Node *temp = head; temp; temp = temp->next)
         std::cout << temp->data << " ";
      std::cout << std::endl;
   }
};

template <class T>
class ArrayList : public List<T> {
   static constexpr int kIncr = 10;
   int size = 0;
   int space;
   T *data;

public:
   ArrayList() : space(kIncr), data(new T[space]) {}
   ArrayList(const ArrayList &src) {
      data = new T[space = src.space];
      size = src.size;
      memcpy(data, src.data, size*sizeof(T));
   }
   ~ArrayList() override {delete [] data;}

   void Add(const T &d) override {
      if (size == space) {
         T *temp = data;
         data = new T[space += kIncr];
         memcpy(data, temp, size);
         delete [] temp;
      }
      data[size++] = d;
   }

   void Print() const override {
      for (int i = 0; i < size; i++)
         std::cout << data[i] << " ";
      std::cout << std::endl;
   }
};

#endif
