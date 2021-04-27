#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <set>
#include <map>
#include <iostream>
#include <memory>
#include "Board.h"

class GameModel {
public:
   // Observers or views of GM implement Observer and register with GM.
   // GM calls Refresh on its observers with a hint bitflag indicating
   // what type of change(s) have occured:
   // 
   // kClass -- Class of game being played has changed (perhaps due to a load)
   // kMove  -- Board has just changed by applying one move.
   // kBoard -- Board has changed, by more than just a forward move, e.g.
   //           an undo or a new game start without game class change.
   // kStatus -- General status (e.g. player positions, playability) has changed
   class Observer {
   public:
      constexpr static int kClass = 0x1, kBoard = 0x2, kMove = 0x4, kStatus = 0x10;
      virtual void Refresh(int flags) = 0;        
   };

   // Some observers may also be Players, whose position (0 for white, 1 
   // for black) may be set and retrieved, who may have an identifying
   // name, and who may approve or disapprove actions by other players
   // including swapping places, taking back a move, and replacing the
   // game entirely with a new game.
   class Player : public Observer, public std::enable_shared_from_this<Player> {
   public:
      virtual ~Player() {} 
      virtual void SetPosition(int pos) = 0;
      virtual int  GetPosition() = 0;
      virtual const std::string &GetName() = 0;
      virtual bool IsChangePlaceOK() = 0;
      virtual bool IsTakeBackOK() = 0;
      virtual bool IsGameReplaceOK() = 0;
   };
   
   // Set of observers, std::shared references from multiple points
   typedef std::set<std::shared_ptr<Observer>> ObsList;

   // Set of Players
   typedef std::map<int, std::shared_ptr<Player>> PlyMap;

   GameModel();

   // Start a new game (replacing the current board) using the specified
   // game type.  Notify observers of a Board or Class change, as appropriate.
   virtual void NewGame(const BoardClass *cls);

   // Make a move if move is valid, and notify observers of a Move.  For 
   // invalid move, throw BaseException
   virtual void MakeMove(std::unique_ptr<Board::Move>);
   
   // If all Players agree, retract one full move and notify Observers of a
   // Board change.  Return true iff all Players agreed.
   virtual bool TakeBack(std::shared_ptr<Player> requestor);

   // If all Players agree, swap sides.  Notify observers of a status change.
   virtual bool SwapSides(std::shared_ptr<Player> requestor);

   // Return true iff game is ready for play (sufficient players present)
   virtual bool IsPlayable();
   
   // Return true if game is done.  (When Board returns no moves.)
   virtual bool IsDone() const;

   // If all players agree, load a new game from binary istream, including 
   // changing game type entirely if the game being read in indicates this.
   virtual void Load(std::istream &in);

   // Save game to binary ostream, including the game type, but not information
   // on Observers or Players.
   virtual void Save(std::ostream &out) const;

   // Add an Observer to the list of notifiable Observers.
   virtual void AddObserver(std::shared_ptr<Observer> obs) {
      mObservers.insert(obs);
   }
   
   // Remove an Observer from the list of Observers.
   virtual void DropObserver(std::shared_ptr<Observer> obs) {
      mObservers.erase(obs);
   }
   
   // Add a Player to the list of Players and Observers, at the indicated
   // player position (e.g. 0 for first player).  Notify all observers of
   // a status change.
   virtual void AddPlayer(std::shared_ptr<Player> ply, int pos);

   // Remove a Player from the list of Players and Observers.  Notify all 
   // remaining observers of a status change.
   virtual void DropPlayer(std::shared_ptr<Player> ply);

   // Return current board.
   std::shared_ptr<const Board> GetCurBoard() const  {return mCurBoard;}
   
   // Return immutable views of current observers and players
   const ObsList &GetObservers() const {return mObservers;}
   const PlyMap &GetPlayers() const {return mPlayers;}
   
   // Return Player who currently has the move
   std::shared_ptr<const Player> GetWhoseMove() const;

   // Return true if current GameModel needs saving.
   bool IsChanged() const            {return mChanged;}
   
protected:
   // Member data as needed.
};

#endif
