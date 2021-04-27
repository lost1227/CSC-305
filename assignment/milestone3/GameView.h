#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <iostream>
#include <memory>
#include "View.h"
#include "GameModel.h"

class View;
class Dialog;

class GameView : public GameModel::Observer {
public:
   GameView(std::shared_ptr<GameModel> mdl, std::ostream &out);

protected:
   // Implementation of Observer method.
   virtual void Refresh(int flags) override;
   virtual void PrintWin();

   std::shared_ptr<GameModel> mModel;
   std::unique_ptr<View> mBrdView;
   std::ostream &mOut;
};

#endif

