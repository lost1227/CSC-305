// Example function design
//
// Edited from reply by David Rodriquez at SO

#include <list>
#include <memory>
#include <algorithm>
#include <iostream>

// Base interface for any void(int &) callable thing
struct GeneralCallable {
   virtual void operator()(int &) = 0;
   virtual ~GeneralCallable() {}
};

// Template to allow a specific void(int &) callable
template <typename F>
struct SpecificCallable : public GeneralCallable {
   F functor;
   SpecificCallable(F functor) : functor(functor) {}
   virtual void operator()(int &x) {return functor(x);}
};

// Function class that wraps a SpecificCallable, via
// GeneralCallable interface
class Function {
   std::shared_ptr<GeneralCallable> callable;
public:
   // Constructor takes *any* int(double) type
   template <typename F>
   Function(F f) : callable(new SpecificCallable<F>(f)) {}

   // Operator() passed the call to referenced callable
   void operator()(int &x) {return (*callable)(x);}
};

using namespace std;

int main() {
   list<int> vals{42, 30, 12};
   int total = 0;

   Function f([&total](int &x){total += x;});

   for_each(vals.begin(), vals.end(), f);
   cout << total << endl;
}

