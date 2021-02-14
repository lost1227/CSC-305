#ifndef C4POP10_H
#define C4POP10_H

#include "Board.h"
#include "C4Pop10Move.h"
#include "Class.h"

class C4Pop10Board : public Board {
public:
   friend class C4Pop10Move;

   static constexpr int DIM_W = 7, DIM_H = 6;
   static constexpr char NONE = 0, PIECE = 1, RED = 2;
   static constexpr int WIN_DISC_COUNT = 10;

   struct Rules {
      int safeWgt;
      int threatWgt;
      int keptWgt;
      int moveWght;

      Rules(): safeWgt(100), threatWgt(50), keptWgt(120), moveWght(50) {}

      void EndSwap();
   };

   C4Pop10Board();
   ~C4Pop10Board();

   int GetValue() const override;
   void ApplyMove(std::unique_ptr<Move>) override;
   void UndoLastMove() override;

   void GetAllMoves(std::list<std::unique_ptr<Move>> *) const override;
   std::unique_ptr<Move> CreateMove() const override;

   int GetWhoseMove() const override;
   const std::list<std::shared_ptr<const Move>> &GetMoveHist() const override;

   std::unique_ptr<Board> Clone() const override;

   std::unique_ptr<const Key> GetKey() const override;

   std::istream &Read(std::istream &) override;
   std::ostream &Write(std::ostream &) const override;

   static Object *CreateBoard();
   static void *GetOptions();
   static void SetOptions(const void *opts);

   const Class *GetClass() const override;
   static const BoardClass mClass;

   const char GetLoc(int row, int col) const;

   struct PlayerScore {
      int safeDisks, threatDisks, keptDisks;
      PlayerScore(): safeDisks{0}, threatDisks{0}, keptDisks{0} {}
   };

   mutable PlayerScore mRedScore, mYellowScore;

private:
   char mBoard[DIM_H][DIM_W];
   char mMoveFlg;

   int mFreeCols;

   std::list<std::shared_ptr<const C4Pop10Move>> mMoveHist;

   bool IsPartOf4(int col) const;
   int CountCol(int col) const;

   enum class PieceVal : char {
      UNKNOWN = 0,
      NONE = 1,
      SAFE_ROW = 2,
      SAFE_COL = 3,
      THREAT = 4
   };

   struct Dir {
      int dRow, dCol;
   };

   void RecalculateScores() const;
   mutable bool mValidScores;

   mutable PieceVal mBottomRowVal[DIM_W];

   static Rules mRules;
   static constexpr int DIAG_DIRS = 2, ALL_DIRS = 4;
   static const Dir mDirs[ALL_DIRS];
};

#endif