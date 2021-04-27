#ifndef MINIMAXAPP_H
#define MINIMAXAPP_H

#include <string>
#include <map>
#include <memory>
#include "Class.h"
#include "Steppable.h"
#include "GameModel.h"

class GameView;

class MinimaxApp {
public:
   MinimaxApp();

   // NO smart pointer here!!
   static MinimaxApp *GetApp() {return &mApp;}
   
   void Run();
   
protected:
// Other member data may be needed.
   std::shared_ptr<GameModel> mModel;
   std::shared_ptr<GameView> mView;
};

#endif
