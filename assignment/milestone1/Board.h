#ifndef BOARD_H
#define BOARD_H

#include <list>
#include <string>
#include <map>
#include <memory>
#include <limits.h>
#include "Class.h"

#pragma warning(disable:4786)

class Board : public Object {
public:
   static constexpr int kWinVal = INT_MAX/4;

   class Move {
   public:
      virtual ~Move() {};
      virtual std::unique_ptr<Move> Clone() const = 0;
      virtual bool operator==(const Move &) const = 0;
      virtual bool operator<(const Move &) const = 0;
      virtual operator std::string() const = 0;
      virtual void operator=(const std::string &src) = 0;

      virtual std::istream &Read(std::istream &) = 0;
      virtual std::ostream &Write(std::ostream &) const = 0;

      static long GetOutstanding() {return mOutstanding;}

   protected:
      static long mOutstanding;
   };

   // Base class for keys returned by getKey and used in the transposition
   // table.  A class may return null from getKey, indicating that it 
   // should not be used with a transposition table.  Key-derived classes
   // must not have any dynamically allocated data, since they are 
   // written and read to and from binary files as a single block of bytes.
   class Key : public Object {
   public:
      virtual ~Key() {};

      // Compare two keys for equality or less-than.
      virtual bool operator==(const Key &) const = 0;
      virtual bool operator<(const Key &) const = 0;

      virtual std::istream &Read(std::istream &) = 0;
      virtual std::ostream &Write(std::ostream &) const = 0;

      static long GetOutstanding() {return mOutstanding;}

   protected:

      static long mOutstanding;
   };
      
   virtual ~Board() {}

   // Return current estimated value of board.
   virtual int GetValue() const = 0;

   // Apply the specified move to the board.  
   virtual void ApplyMove(std::unique_ptr<Move>) = 0;

   // Undo the last move.  May be called repeatedly.
   virtual void UndoLastMove() = 0;

   // Return via out parameter a list of all possible moves from this board.
   // Caller owns the moves.  Moves are returned in sorted order, as determined
   // by the operator< for the move class in question.  Returns an empty move
   // list iff the game is over.
   virtual void GetAllMoves(std::list<std::unique_ptr<Move>> *fillIn) const = 0;

   // Create a default-constructed move of the appropriate type for this board.
   virtual std::unique_ptr<Move> CreateMove() const = 0;

   // Get whose move it is, numbering from 0 as first player.
   virtual int GetWhoseMove() const = 0;

   // Return a move history list.  Board retains ownership of moves.
   virtual const std::list<std::shared_ptr<const Move>> &GetMoveHist() const = 0;

   // Duplicate current board.
   virtual std::unique_ptr<Board> Clone() const = 0;

   // Return a Key object for use with transposition table.  Caller owns the
   // key.
   virtual std::unique_ptr<const Key> GetKey() const = 0;

   // Binary Read/Write   
   virtual std::istream &Read(std::istream &) = 0;
   virtual std::ostream &Write(std::ostream &) const = 0;
};

#endif
