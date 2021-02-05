#include <iostream>
#include <string>
#include <memory>

#include <string.h>
#include <assert.h>

#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"

using namespace std;

const int outWidth = 80;

template<class T>
void printMoveList(T begin, T end) {
    if(begin == end){
        cout << endl;
        return;
    }
    list<string> moveStrs;
    string curr;
    int longestMoveLength = 0;
    for(; !(begin == end); begin++) {
        curr = **begin;
        longestMoveLength = max(longestMoveLength, (int) curr.length());
        moveStrs.push_back(move(curr));
    }

    curr = "";
    for(auto& mov : moveStrs) {
        if(curr.length() + mov.length() > outWidth) {
            cout << curr << endl;
            curr = "";
        } else if(curr.length() != 0) {
            curr += " ";
        }
        curr += mov;
        for(int i = mov.length(); i < longestMoveLength; i++)
            curr += " ";
    }
    if(curr.length() > 0)
        cout << curr;
    cout << endl;
}

int main() {
    shared_ptr<OthelloBoard> board(new OthelloBoard());
    shared_ptr<OthelloView> view(new OthelloView());

    unique_ptr<Board::Move> currMove = board->CreateMove();

    list<unique_ptr<Board::Move>> moves;

    view->SetModel(board);

    // showBoard, enterMove, showMove, doMove and quit
    string line;
    while(true) {
        getline(cin, line);
        size_t idx;
        if((idx = line.find("showBoard")) != string::npos) {
            view->Draw(cout);
            moves.clear();
            board->GetAllMoves(&moves);
            printMoveList(moves.begin(), moves.end());
        } else if((idx = line.find("enterMove")) != string::npos) {
            *currMove = line.substr(idx + strlen("enterMove"));
            //*currMove = line;
        } else if((idx = line.find("showMoveHist")) != string::npos) { 
            const list<shared_ptr<const Board::Move>> &moveHist = board->GetMoveHist();
            printMoveList(moveHist.begin(), moveHist.end());
        } else if((idx = line.find("showMove")) != string::npos) {
            cout << (string) *currMove << endl;
        } else if((idx = line.find("applyMove")) != string::npos) {
            board->ApplyMove(currMove->Clone());
        } else if((idx = line.find("doMove")) != string::npos) {
            currMove = board->CreateMove();
            *currMove = line.substr(idx + strlen("doMove"));
            board->ApplyMove(currMove->Clone());
        } else if((idx = line.find("undoLastMove")) != string::npos) {
            board->UndoLastMove();
        } else if((idx = line.find("showVal")) != string::npos) {
            cout << "Value: " << board->GetValue() << endl;
        } else if((idx = line.find("quit")) != string::npos) {
            exit(0);
        } else {
            cout << "Invalid command!" << endl;
        }
        cout << endl;
    }
}