#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <string>
#include <memory>
#include "GameModel.h"
#include "GameView.h"
#include "Steppable.h"
#include "Dialog.h"
#include "View.h"

class HumanPlayer : public GameModel::Player, Steppable {
public:
   typedef std::map<std::string, const BoardClass *> NameMap;

   // Join 'mdl', with name 'name'.
   HumanPlayer(std::shared_ptr<GameModel> mdl, std::string name);
   ~HumanPlayer();

   // Restart human playing after having AI player cover us for some moves.
   void Reactivate()     {mActive = true;}

   // Return number of HumanPlayers
   static int GetCount() {return mCount;}
   
   static void InitMap();
      
   // Configure a brand new game in the specified GameModel
   static void GlobalNewGame(std::shared_ptr<GameModel> mdl,
    std::string gameName, int lvl, std::string *playerNames, int numPlayers);

protected:
   // Handle each of the possible user-commands.
   virtual void DoMove();
   virtual void ReadGame();
   virtual void WriteGame();
   virtual void UndoMove();
   virtual void NewGame();
   virtual void PrintHelp();
   virtual void AutoPlay();
   virtual void SetOptions();
   virtual void SwitchSides();
   virtual void ShowMoves();

   // Implementations of Observer methods.
   virtual void Refresh(int flags) override;

   // Handle all housekeeping for asking about game-saving and saving game if
   // requested.  Return true if OK to clear Game.
   virtual bool ClearGame(bool ask);

   // Player Redefinitions
   void SetPosition(int pos)    override {mPos = pos;}
   int  GetPosition()           override {return mPos;}
   const std::string &GetName() override {return mName;}
   bool IsChangePlaceOK() override;
   bool IsTakeBackOK()    override;
   bool IsGameReplaceOK() override;
   
   // Steppable Redefinition
   void Step() override;

protected:
   // Member data as needed
};

#endif

