#ifndef STEPPABLE_H
#define STEPPABLE_H

#include <memory>
#include <set>

// Steppable permits a mock-thread action via a mixin design pattern.  
// To use this class, derive from from Steppable and implement a Step method.
// Nothing more is needed.
//
// A main driver may then call StepAll to cause the Step methods of all 
// Steppables to be called once.  Repeated calls of StepAll will mimic
// multithreaded action.  
//
// SteppablesExist indicates whether any Steppables exist.

class Steppable {
public:
   Steppable();
   virtual ~Steppable();
   
   virtual void Step() = 0;
   
   // Call Step on all current Steppables.  Note that each Step call may
   // alter the current Steppables list by addition or deletion.
   static void StepAll();
   static bool SteppablesExist();

private:
   // Members as needed
};

#endif
