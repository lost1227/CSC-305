#include <memory>
#include <string>
#include <iostream>

using namespace std;

class Thing {
   static int count;

   int id;
public:
   Thing() : id(count++) {cout << "Making Thing " << id << endl;}
   ~Thing() {cout << "Destroying Thing " << id << endl;}

   void Mod(int newId)          {id = newId;}
   void Print(string lbl) const {cout << lbl << "Thing " << id << endl;}
};

int Thing::count = 0;

unique_ptr<Thing> MakeThing() {
   // Move semantics: the new unique_ptr is moved when it is returned
   // return move(unique_ptr<Thing>(new Thing()));
   return unique_ptr<Thing>(new Thing()); // Return's unique_ptr owns nothing
}

void TakeThing(unique_ptr<Thing> prm) {
   prm->Print("TakeThing: ");
}

int main() {
   // There are three uniqe_ptrs constructed in this statement
   // 1. The unique_ptr constructed in MakeThing
   // 2. The unique_ptr constructed to hold the return value from MakeThing
   //    We have to copy unique_ptr 1 out of the MakeThing() stackframe into the main() stackframe
   // 3. The unique_ptr t0
   // unique_ptr 1 is constructed with the new thing
   // It is then moved into unique_ptr 2
   // This is then moved into t0
   unique_ptr<Thing> t0 = MakeThing();
   // unique_ptr<Thing> t1 = t0; Doesn't compile! The copy constructor has been deleted
   unique_ptr<Thing> t1 = move(t0);
   shared_ptr<Thing> s1(new Thing()), s2;
   shared_ptr<Thing> s3{MakeThing()}; 
   shared_ptr<const Thing> cs1 = s3; // cs1 is a const reference
   weak_ptr<Thing> wp;

   if (!t0 && t0.get() == nullptr) // the two tests are equivalent
      cout << "t0 owns nothing due to assign into t1" << endl;

   cout << endl << "Pass t1 to TakeThing" << endl;
   TakeThing(move(t1));                  // t1 owns nothing after pass

   cout << endl << "Pass MakeThing() to TakeThing" << endl;
   TakeThing(MakeThing());

   cout << endl << "Make unique_ptr and pass it to TakeThing" << endl;
   TakeThing(unique_ptr<Thing>(new Thing())); // But not TakeThing(new Thing())

   cout << endl << "Set up s1 and s3" << endl;
   s1->Print("S1 points to ");
   s3->Mod(42);
   s3->Print("S3 points to ");

   cout << endl << "Copy s1 to s2, sharing the reference" << endl;
   s2 = s1;
   cout << "Ref count after s2 = s1 " << s1.use_count() << endl;

   cout << endl << "Copy s3 into s1 and s2 replacing their refs" << endl;
   s1 = s3;
   s2 = s3;
   cout << "Ref counts after s3 assigns: " << s1.use_count() << " " 
    << s2.use_count() << " " << s3.use_count() << endl;
   wp = s3;
   cout << "... and after wp assignment: " << s3.use_count() << endl << endl;

   s1 = nullptr;
   s2 = nullptr;
   cout << "Ref count after nulling s1 and s2: " << s3.use_count() << endl << endl;   

   // cs1->Mod(43);  // Won't compile - cs1 is const!
   cs1->Print("Cs1 points to ");
   cs1 = nullptr;
   cout << "Ref count after nulling cs1: " << s3.use_count() << endl << endl;
   
   // wp->Print("Test");     Doesn't compile - you can't reference a weak pointer! You need to get a lock
   if (auto sTemp = wp.lock()) {
      cout << "Ref counts after locking wp: " << s3.use_count() << " "
       << sTemp.use_count() << endl;   
      sTemp->Print("sTemp points to: ");
   }
   cout << "Ref count after sTemp leaves scope: " << s3.use_count() << endl;
   s3 = nullptr;
   cout << ".. and ref count after nulling s3: " << s3.use_count() << endl << endl;
   
   if (wp.use_count() == 0 && wp.expired() && !wp.lock()) // All these tests work / are equivalent
      cout << "Weak Pointer is also gone" << endl;

   return 0;
}

/* Sample run
Making Thing 0
Making Thing 1
Making Thing 2
t0 owns nothing due to assign into t1

Pass t1 to TakeThing
TakeThing: Thing 0
Destroying Thing 0

Pass MakeThing() to TakeThing
Making Thing 3
TakeThing: Thing 3
Destroying Thing 3

Make unique_ptr and pass it to TakeThing
Making Thing 4
TakeThing: Thing 4
Destroying Thing 4

Set up s1 and s3
S1 points to Thing 1
S3 points to Thing 42

Copy s1 to s2, sharing the reference
Ref count after s2 = s1 2

Copy s3 into s1 and s2 replacing their refs
Destroying Thing 1
Ref counts after s3 assigns: 4 4 4
... and after wp assignment: 4

Ref count after nulling s1 and s2: 2

Cs1 points to Thing 42
Ref count after nulling cs1: 1

Ref counts after locking wp: 2 2
sTemp points to: Thing 42
Ref count after sTemp leaves scope: 1
Destroying Thing 42
.. and ref count after nulling s3: 0

Weak Pointer is also gone
*/
