#include <iostream>
#include <string>
#include <memory>

#include "string.h"

#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"

using namespace std;


int main() {
    shared_ptr<OthelloBoard> board(new OthelloBoard());
    shared_ptr<OthelloView> view(new OthelloView());

    unique_ptr<Board::Move> currMove = board->CreateMove();

    view->SetModel(board);

    // showBoard, enterMove, showMove, doMove and quit
    string line;
    while(true) {
        getline(cin, line);
        size_t idx;
        if((idx = line.find("showBoard")) != string::npos) {
            view->Draw(cout);
        } else if((idx = line.find("enterMove")) != string::npos) {
            *currMove = line.substr(idx + strlen("enterMove"));
            //*currMove = line;
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
        } else if((idx = line.find("quit")) != string::npos) {
            exit(0);
        } else {
            cout << "Invalid command!" << endl;
        }
    }
}