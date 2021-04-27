#include <iostream>
#include <cstring>

/* Concepts
 * 1. Protected scope
 * 2. Scoped inheritance legacy feature
 * 3. Calling base constructors and methods from subclass code
 * 4. Optional polymorphism
 * 5. Tension between polymorphism and inlining
 * 6. Structure of subclass objects (nested base object)
 * 7. Vtable basics
 * 8. Virtual destructor
*/

using namespace std;

class Average {
protected:
   string description;
   long long count = 1;  // long long ensures 8 bytes
   double total;

public:
   Average(string d, double val) : description(d), total(val) {}
   virtual ~Average() {}

   void Print() const {cout << description << " " << total/count << endl;}

   double GetAvg() const           {return total/count;}
   virtual void AddVal(double val) {total += val; count++;}
};   

class HstAverage : public Average {
   static constexpr int kSizeIncr = 10;
   long long hSize;  
   double *history;
   
public:
   HstAverage(string d, double val) : Average(d, val), hSize(kSizeIncr) {
      history = new double[hSize];
      history[count-1] = val;
   }

   ~HstAverage() override {cout << "Deleting history\n"; delete [] history;}

   void Print() const {        // Not an override
      Average::Print();
      cout << "Just added: " << history[count-1] << endl;
   }

   void AddVal(double val) override {
      if (count == hSize) {  // Make more room if needed
         double *oldHst = history;

         history = new double[hSize += kSizeIncr];
         memcpy(history, oldHst, count*sizeof(double));
         delete [] oldHst;
      }
      history[count] = val;
      Average::AddVal(val);
   }

   void Undo() {
      if (count)
         total -= history[--count];
   }
};

int main() {
   double val;
   
   cin >> val;
   HstAverage *hAvg = new HstAverage("Example", val);
   Average *avg = hAvg;  // Upcast relies on ISA relationship
   // HstAverage *hAvg2 = avg; // This would be a downcast, is unsafe, and must use dynamic_cast

   while (cin >> val) {
      avg->AddVal(val);  // Calls HstAverage version
      avg->Print();      // Calls Average version
      hAvg->Print();     // Calls HstAverage version
      cout << endl;
   }
   cout << "Final average: " << avg->GetAvg() << endl; // Or hAvg->GetAvg()
   hAvg->Undo();                                       // but not avg->Undo()
   cout << "Average minus last value: " << avg->GetAvg() << endl;

   // Analysis of underlying data
   Average *t1 = new Average("", 0), *t2 = new Average("", 0);

   cout << "Sizes: String " << sizeof(string) << " Average " 
    << sizeof(Average) << " HstAverage " << sizeof(HstAverage) << endl;

   cout << "Average vtable ptr: " << (void *)*(long *)t1 << " " << (void *)*(long *)t2 << endl;
   cout << "HstAverage vtable ptr: " << (void *)*(long *)hAvg << endl << endl;

   delete avg;  // Note the destructor call!

   return 0;
}

/*
2 42 3 19       (Input)

Example 22      (Output)
Example 22
Just added: 42

Example 15.6667
Example 15.6667
Just added: 3

Example 16.5
Example 16.5
Just added: 19

Final average: 16.5
Average minus last value: 15.6667
Sizes: String 8 Average 32 HstAverage 48
Average vtable ptr: 4201168 4201168
HstAverage vtable ptr: 4201104

Deleting history
*/
