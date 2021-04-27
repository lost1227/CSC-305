#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <memory>
#include "Steppable.h"
#include "GameModel.h"
#include "HumanPlayer.h"
#include "BestMove.h"
#include "Book.h"
#include "Board.h"
#include "limits.h"

class AIPlayer : public GameModel::Player, Steppable {
public:
   // Deepest allowed minimax level
   constexpr static int MAX_LEVEL = 15;
   constexpr static int SAVE_LEVEL = 1;

   AIPlayer(std::shared_ptr<GameModel>, std::string name,
    int lim = INT_MAX, std::shared_ptr<HumanPlayer> prx = nullptr);
   
   const std::string &GetName() override {return mName;}
   void Refresh(int flags)   override;
   void SetPosition(int pos) override {mPosition = pos;}
   int  GetPosition()        override {return mPosition;}
   bool IsChangePlaceOK()    override;    
   bool IsTakeBackOK()       override {return true;}
   bool IsGameReplaceOK()    override {return true;}
   
   // Make one move if it's your turn.  Quit the game if you finish it and
   // quitAtEnd was true.  Kill yourself if you didn't quit the game, but
   // you've hit your "limit".
   void Step() override;
   
    // Preconditions: res points to a BestMove object, which may have 0 for
   // its current bestMove.  Any value V such that V <= min or V >= max is
   // "uninteresting" to the caller.  Level is always >= 1 and indicates how
   // deeply to probe. (Note that this means you should evaluate leaf
   // boards directly as they are generated, rather than making a FindBestMove
   // call with level of 0 for each leaf board.  This is important for efficient
   // running.)  If tt is not null, it points to a book of previously computed
   // BestMoves.
   //
   // Postconditions: res->value indicates the result of the minimax search.
   // If res->value <= min or res->value >= max then no "interesting" move could
   // be found, and res->bestMove will indicate the first move where this fact
   // was uncovered.  If brd is an endgame board, then  res->value will
   // be winVal, 0 or -winVal, and res->bestMove will be 0 since there is no move
   // from an endgame position.  Otherwise, res->bestMove will provide the best
   // move.  Res->numBoards gives the number of boards examined during the
   // minimax computation, including the root board. *brd is left in the same
   // state as it was when the call commenced.  Res->value gives the
   // minimax computed value for *brd. *tt contains new entries for any board 
   // configurations that were computed during the call, with depth greater
   // than or equal to SAVE_LEVEL (currently 1), and will have updated any 
   // entries for which deeper results were computed during the call.
   static void Minimax(Board *brd, int lvl, long min, long max, BestMove *res,
    TTable *tt, int debugLvl = 0);

   // Set or get the play level shared by all AIPlayer instances.
   static int GetLevel() {return mLevel;}
   static void SetLevel(int val);
   
protected:
   // Use Book if possible, otherwise do Minimax calc.
   virtual BestMove FigureMove() const;
   // Member data as needed
};

#endif
