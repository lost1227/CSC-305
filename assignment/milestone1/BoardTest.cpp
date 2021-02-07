#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <memory>
#include <algorithm>

#include <cstdlib>

#include "assert.h"

#include "Board.h"
#include "View.h"
#include "Dialog.h"

//FIXME: Use reflection instead of manual instantiation
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloDlg.h"

using namespace std;

class BoardTestCmd;
template<class T>
void printMoveList(T, T);

class BoardTest {
public:
    BoardTest(shared_ptr<Board> &&, shared_ptr<View> &&, shared_ptr<Dialog> &&);
    void RegisterCmd(BoardTestCmd *cmd) {
        mCmds.push_back(unique_ptr<BoardTestCmd>(cmd));
    }
    void ExecCmd(string &);
    void Run();

    
    shared_ptr<Board> mBoard;
    shared_ptr<View> mView;
    shared_ptr<Dialog> mDlg;
    shared_ptr<Board::Move> mCurrMove;

    bool shouldRun { true };
private:
    vector<unique_ptr<BoardTestCmd>> mCmds;
};

class BoardTestCmd {
public:
    virtual ~BoardTestCmd() {};
    virtual bool Accept(const string& str) { return regex_match(str, mMatches, mMatcher); }
    virtual void Apply(BoardTest&) = 0;
protected:
    BoardTestCmd(regex&& expr) : mMatcher(expr) {}
    smatch mMatches;
    regex mMatcher;
};

class ShowBoardCmd : public BoardTestCmd {
public:
    ShowBoardCmd() : BoardTestCmd(regex(R"(^\s*showBoard)")) {}
    void Apply(BoardTest &board) override {
        list<unique_ptr<Board::Move>> moveOpts;
        board.mView->Draw(cout);
        cout << endl;
        cout << "All Moves: " << endl;
        board.mBoard->GetAllMoves(&moveOpts);
        printMoveList(moveOpts.begin(), moveOpts.end());
    }
};

class EnterMoveCmd : public BoardTestCmd {
public:
    EnterMoveCmd() : BoardTestCmd(regex(R"(^\s*enterMove(.*)$)")) {}
    void Apply(BoardTest &board) override {
        auto tmpMove = board.mBoard->CreateMove();
        (*tmpMove) = mMatches[1];
        board.mCurrMove = move(tmpMove);
    };
};

class ShowMoveCmd : public BoardTestCmd {
public:
    ShowMoveCmd() : BoardTestCmd(regex(R"(^\s*showMove)")) {}
    void Apply(BoardTest &board) override {
        assert(board.mCurrMove);
        cout << (string)(*board.mCurrMove) << endl;
    }
};

class ApplyMoveCmd : public BoardTestCmd {
public:
    ApplyMoveCmd() : BoardTestCmd(regex(R"(^\s*applyMove)")) {}
    void Apply(BoardTest &board) override {
        assert(board.mCurrMove);
        list<unique_ptr<Board::Move>> moveOpts;
        board.mBoard->GetAllMoves(&moveOpts);
        for(auto& uniqMovePtr : moveOpts) {
            if(*uniqMovePtr == *board.mCurrMove) {
                board.mBoard->ApplyMove(move(uniqMovePtr));
                return;
            }
        }
        cout << "Invalid move!" << endl;
    }
};

class ShowMoveHistCmd : public BoardTestCmd {
public:
    ShowMoveHistCmd() : BoardTestCmd(regex(R"(^\s*showMoveHist)")) {}
    void Apply(BoardTest &board) override {
        const list<shared_ptr<const Board::Move>> &moveHist = board.mBoard->GetMoveHist();
        cout << endl << "Move History: " << endl;
        printMoveList(moveHist.begin(), moveHist.end());
    }
};

class DoMoveCmd : public BoardTestCmd {
public:
    DoMoveCmd() : BoardTestCmd(regex(R"(^\s*doMove(.*)$)")) {}
    void Apply(BoardTest &board) override {
        auto tmpMove = board.mBoard->CreateMove();
        (*tmpMove) = mMatches[1];
        board.mCurrMove = move(tmpMove);

        list<unique_ptr<Board::Move>> moveOpts;
        board.mBoard->GetAllMoves(&moveOpts);
        for(auto& uniqMovePtr : moveOpts) {
            if(*uniqMovePtr == *board.mCurrMove) {
                board.mBoard->ApplyMove(move(uniqMovePtr));
                return;
            }
        }
        cout << "Invalid move!" << endl;
    }
};

class UndoLastMoveCmd : public BoardTestCmd {
public:
    UndoLastMoveCmd() : BoardTestCmd(regex(R"(^\s*undoLastMove\s+(\d+))")) {}
    void Apply(BoardTest &board) override {
        int count = stoi(mMatches[1]);
        auto moveHist = board.mBoard->GetMoveHist();
        count = min(count, (int)moveHist.size());
        for(int i = 0; i < count; i++)
            board.mBoard->UndoLastMove();
    }
};

class ShowValCmd : public BoardTestCmd {
public:
    ShowValCmd() : BoardTestCmd(regex(R"(^\s*showVal)")) {}
    void Apply(BoardTest &board) override {
        cout << "Value: " << board.mBoard->GetValue() << endl;
    }
};

class SaveBoardCmd : public BoardTestCmd {
public:
    SaveBoardCmd() : BoardTestCmd(regex(R"(^\s*saveBoard\s+([^\s]*))")) {}
    void Apply(BoardTest &board) override {
        ofstream strm(mMatches[1]);
        board.mBoard->Write(strm);
        strm.close();
    }
};

class LoadBoardCmd : public BoardTestCmd {
public:
    LoadBoardCmd() : BoardTestCmd(regex(R"(^\s*loadBoard\s+([^\s]*))")) {}
    void Apply(BoardTest &board) override {
        ifstream strm(mMatches[1]);
        board.mBoard->Read(strm);
        strm.close();
    }
};

class SaveMoveCmd : public BoardTestCmd {
public:
    SaveMoveCmd() : BoardTestCmd(regex(R"(^\s*saveMove\s+([^\s]*))")) {}
    void Apply(BoardTest &board) override {
        ofstream strm(mMatches[1]);
        board.mCurrMove->Write(strm);
        strm.close();
    }
};

class LoadMoveCmd : public BoardTestCmd {
public:
    LoadMoveCmd() : BoardTestCmd(regex(R"(^\s*loadMove\s+([^\s]*))")) {}
    void Apply(BoardTest &board) override {
        ifstream strm(mMatches[1]);
        board.mCurrMove->Read(strm);
        strm.close();
    }
};

class CompareKeysCmd : public BoardTestCmd {
public:
    CompareKeysCmd() : BoardTestCmd(regex(R"(^\s*compareKeys\s+([^\s]*))")) {}
    void Apply(BoardTest &board) override {
        auto oBoard = board.mBoard->Clone();
        assert(oBoard);
        ifstream strm(mMatches[1]);
        oBoard->Read(strm);
        strm.close();
        auto key = board.mBoard->GetKey();
        auto oKey = oBoard->GetKey();
        
        if(*key == *oKey) {
            cout << "Board keys are equal" << endl;
            return;
        }
        cout << "Board keys are unequal" << endl;
        if(*key < *oKey) {
            cout << "Current board is less than " << mMatches[1] << endl;
        } else {
            cout << "Current board is greater than " << mMatches[1] << endl;
        }
    }
};

class CompareMoveCmd : public BoardTestCmd {
public:
    CompareMoveCmd() : BoardTestCmd(regex(R"(^\s*compareMove\s+(.*)$)")) {}
    void Apply(BoardTest &board) override {
        auto currMove = board.mCurrMove;
        auto oMove = board.mBoard->CreateMove();
        *oMove = mMatches[1];
        assert(oMove);
        
        if(*currMove == *oMove) {
            cout << "Moves are equal" << endl;
        }else if(*currMove < *oMove) {
            cout << "Current move is less than entered move" << endl;
        } else {
            cout << "Current move is greater than entered move" << endl;
        }
    }
};

class SetOptionsCmd : public BoardTestCmd {
public:
    SetOptionsCmd() : BoardTestCmd(regex(R"(^\s*setOptions)")) {}
    void Apply(BoardTest &board) override {
        // FIXME: Use the BoardClass to get/set options
        OthelloBoard::Rules *rules = reinterpret_cast<OthelloBoard::Rules *>(OthelloBoard::GetOptions());
        board.mDlg->Run(cin, cout, rules);
        OthelloBoard::SetOptions(rules);
        delete rules;
    }
};

class TestPlayCmd : public BoardTestCmd {
public:
    TestPlayCmd() : BoardTestCmd(regex(R"(^\s*testPlay\s+(\d+)\s+(\d+))")) {}
    void Apply(BoardTest &board) override {
        int seed = stoi(mMatches[1]);
        int moveCount = stoi(mMatches[2]);
        int idx;
        list<unique_ptr<Board::Move>> moveOpts;

        srand(seed);

        for(int i = 0; i < moveCount; i++) {
            moveOpts.clear();
            board.mBoard->GetAllMoves(&moveOpts);
            if(moveOpts.size() == 0)
                break;
            auto iterator = moveOpts.begin();
            idx = rand() % moveOpts.size();
            advance(iterator, idx);
            
            *board.mCurrMove = **iterator;
            board.mBoard->ApplyMove(move(*iterator));
        }
    }
};

class TestRunCmd : public BoardTestCmd {
public:
    TestRunCmd() : BoardTestCmd(regex(R"(^\s*testRun\s+(\d+)\s+(\d+))")) {}
    void Apply(BoardTest &board) override {
        int seed = stoi(mMatches[1]);
        int moveCount = stoi(mMatches[2]);
        int idx;
        list<unique_ptr<Board::Move>> moveOpts;

        srand(seed);

        for(int i = 0; i < moveCount; i++) {
            moveOpts.clear();
            board.mBoard->GetAllMoves(&moveOpts);
            if(moveOpts.size() == 0) {
                auto &moveHist = board.mBoard->GetMoveHist();
                assert(moveHist.size() > 0);
                size_t undoCount = (rand() % (moveHist.size() - 1)) + 1;
                assert(undoCount > 0);
                assert(undoCount < moveHist.size());
                for(size_t i = 0; i < undoCount; i++)
                    board.mBoard->UndoLastMove();
                if(moveHist.size() == 0)
                    *board.mCurrMove = *board.mBoard->CreateMove();
                else
                    *board.mCurrMove = *moveHist.back();
                board.mBoard->GetAllMoves(&moveOpts);
                assert(moveOpts.size() > 0);
            }
            auto iterator = moveOpts.begin();
            idx = rand() % moveOpts.size();
            advance(iterator, idx);
            
            *board.mCurrMove = **iterator;
            board.mBoard->ApplyMove(move(*iterator));
        }
    }
};

class KeyMoveCountCmd : public BoardTestCmd {
public:
    KeyMoveCountCmd() : BoardTestCmd(regex(R"(^\s*keyMoveCount)")) {}
    void Apply(BoardTest &) override {
        cout << "Moves/Keys: "
             << Board::Move::GetOutstanding()
             << "/" << Board::Key::GetOutstanding()
            << endl;
    }
};

class EmptyLineCmd : public BoardTestCmd {
public:
    EmptyLineCmd() : BoardTestCmd(regex(R"(^\s*$)")){}
    void Apply(BoardTest &) override {};
};

class QuitCmd : public BoardTestCmd {
public:
    QuitCmd() : BoardTestCmd(regex(R"(^\s*quit)")) {}
    void Apply(BoardTest &board) override {
        board.shouldRun = false;
    }
};

BoardTest::BoardTest(shared_ptr<Board> &&board, shared_ptr<View> &&view, shared_ptr<Dialog> &&dlg)
    : mBoard(board)
    , mView(view)
    , mDlg(dlg)
    , mCurrMove(board->CreateMove())
{
    mView->SetModel(mBoard);

    // FIXME: Since these are all singletons, could this be done better with static members?
    // That is, could we make each BoardTestCmd hold a static instance of itself, then have
    // the BoardTestCmd somehow register itself with BoardTest?
    RegisterCmd(new EmptyLineCmd());
    RegisterCmd(new ShowBoardCmd());
    RegisterCmd(new EnterMoveCmd());
    RegisterCmd(new ShowMoveCmd());
    RegisterCmd(new ApplyMoveCmd());
    RegisterCmd(new ShowMoveHistCmd());
    RegisterCmd(new DoMoveCmd());
    RegisterCmd(new UndoLastMoveCmd());
    RegisterCmd(new ShowValCmd());
    RegisterCmd(new SaveBoardCmd());
    RegisterCmd(new LoadBoardCmd());
    RegisterCmd(new SaveMoveCmd());
    RegisterCmd(new LoadMoveCmd());
    RegisterCmd(new CompareKeysCmd());
    RegisterCmd(new CompareMoveCmd());
    RegisterCmd(new SetOptionsCmd());
    RegisterCmd(new TestPlayCmd());
    RegisterCmd(new TestRunCmd());
    RegisterCmd(new KeyMoveCountCmd());
    RegisterCmd(new QuitCmd());
}

void BoardTest::ExecCmd(string &cmdStr) {
    for(auto& cmd : mCmds) {
        if(cmd->Accept(cmdStr)) {
            cmd->Apply(*this);
            return;
        }
    }
    cout << "Unknown command!" << endl;
}

void BoardTest::Run() {
    string cmd;
    while(shouldRun) {
        getline(cin, cmd);
        if(cin.eof()) {
            cout << "Error: Unexpected EOF" << endl << endl;
            break;
        }
        try {
        ExecCmd(cmd);
        } catch(BaseException &e) {
            cout << "Error: " << e.what() << endl;
        }
        cout << endl;
    }
}

const int outWidth = 80;

template<class T>
void printMoveList(T begin, T end) {
    if(begin == end){
        return;
    }
    static list<string> moveStrs;
    int longestMoveLength = 0;
    static string curr;
    assert(moveStrs.size() == 0);
    for(; !(begin == end); begin++) {
        curr = **begin;
        longestMoveLength = max(longestMoveLength, (int) curr.length());
        moveStrs.push_back(move(curr));
    }

    int currLineLen = 0;
    for(auto& mov : moveStrs) {
        if(currLineLen + mov.length() > outWidth) {
            cout << endl;
            currLineLen = 0;
        } else if(currLineLen != 0) {
            cout << " ";
            ++currLineLen;
        }
        cout << mov;
        currLineLen += mov.length();
        for(int i = mov.length(); i < longestMoveLength; i++, currLineLen++)
            cout << " ";
    }
    cout << endl;

    moveStrs.clear();
}

int main(int argc, char *argv[]) {
    //FIXME: Use reflection instead of manual instantiation
    BoardTest boardTest(
        shared_ptr<Board>(new OthelloBoard()),
        shared_ptr<View>(new OthelloView()),
        shared_ptr<Dialog>(new OthelloDlg()));
    
    boardTest.Run();
    
}