
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <limits.h>

using namespace std;

// Simple functional class example
class Functor {
   int &xRef;

public:
   Functor(int &x) : xRef(x) {}
   void operator()(int &v) {v += xRef; xRef = v;}
};

// Function and function to return it
void SimpleFunction(int &x) {
   x += 1;
}

function<void (int &)> RtnFunc() {
   return SimpleFunction;
}

// Attempting to return a lambda

// Nope. Wrong return type
// void (*RtnAdder(int amt))(int &) {
//    return &[=amt](int &x){x += amt;};
// }

// Use std::function template, which can be constructed with any
// argument/return - compatible entity.
function<void (int &)> RtnAdder(int amt) {
   return [amt](int &x){x += amt;};
}

// Vector printing utility
void Print(const vector<int> &vals) {
   for_each(vals.begin(), vals.end(), [](const int &x){cout << x << " ";});
   cout << "\n";
}

// 4
function<void(int)> GetGtCounter(int &counter, int limit) {
   return [&counter, limit](int x){counter += (x > limit) ? 1 : 0;};
}

int main() {
   vector<int> vals{42, 131, 0, 20, 7};
   int total = 0;
   int bigVal = INT_MIN;
     
   // Basic uses of lambdas with for_each
   for_each(vals.begin(), vals.end(), Functor(total));
   Print(vals);
   cout << total << endl;

   for_each(vals.begin(), vals.end(), [&total](int &x){x += total; total = x;});
   Print(vals);

   for_each(vals.begin(), vals.end(), [&](int x){bigVal = max(x, bigVal);});
   cout << "bigVal " << bigVal << endl;

   // What types are lambdas??
   cout << typeid(Functor(total)).name() << endl;
   cout << typeid([](){}).name() << endl;
   cout << typeid([](){}).name() << endl;
   cout << typeid([](){return 0;}).name() << endl;
   cout << typeid([](int){return 0;}).name() << endl;
   cout << typeid([&total](int){return 0;}).name() << endl;

   // Uses of function/lambda returning functions
   for_each(vals.begin(), vals.end(), RtnFunc());
   Print(vals);

   total = 0;
   for_each(vals.begin(), vals.end(), RtnAdder(10));
   Print(vals);
   
   // Exercises ...............
   cout << "Start of exercises" << endl;
   vals = vector<int>{54, 89, 10, 200, 7};
   int limit = 42;
   int count = 0;
   int temp = 0;

   // 3
   for_each(vals.begin(), vals.end(), [&count,limit](int x){count += (x > limit) ? 1 : 0;});
   cout << count << endl;

   //5
   for_each(vals.begin(), vals.end(), [&temp](int &x){
      int swp = x;
      x = temp;
      temp = swp;
   });
   Print(vals);
   // 1. Rewrite RtnFunc to use function return type
   // 2. Rewrite Print to use lambda and for_each
   // 3. Write a for_each call to count in "count" the number of items larger
   //    than "limit" use &-notation only when needed
   // 4. Now write a function that is passed a limit and counter and returns 
   //    a functor to use in a similar for_each call.
   // 5. Write a for_each call in main to move each item up one, putting 0 at start,
   //    dropping the last value.
}

