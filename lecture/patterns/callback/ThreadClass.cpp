#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <algorithm>

using namespace std;

class Thread {
   pthread_t id;                 // ID of created thread

   // Callback pattern
   static void *ThreadMain(void *vThread) {
      return ((Thread *)vThread)->Run();
   }

public:
   Thread() {pthread_create(&id, NULL, ThreadMain, this);}

   virtual void *Run() {return nullptr;}
   void Join() {pthread_join(id, NULL);}
};

// Specific derived thread class doing a sample job
class SortThread : public Thread {
   vector<int> *toSort;

public:
   SortThread(vector<int> *tS) : toSort(tS) {}

   void *Run() override {
      sort(toSort->begin(), toSort->end());
      return nullptr;
   }
};

int main() {
   Thread *thread;
   int val;
   vector<int> vals;

   while (cin >> val)
      vals.push_back(val);

   thread = new SortThread(&vals);
   thread->Join();

   for (auto i: vals)
      cout << i << " ";
   cout << endl;

   return 0;
}
