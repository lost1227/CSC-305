#ifndef C4POP10_H
#define C4POP10_H

#include "Board.h"
#include "C4Pop10Move.h"

class C4Pop10Board : public Board {
public:
    friend class C4Pop10Move;

    struct Rules {
        int safeWgt;
        int threatWgt;
        int keptWgt;
        int moveWght;

        Rules() : safeWgt(100), threatWgt(50), keptWgt(120), moveWght(50) {}

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

    const Class *GetClass() const override;
    static Class mClass;
};

#endif