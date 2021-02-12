#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <list>
#include <set>
#include <limits.h>
#include <algorithm>
#include "MyLib.h"
#include "Board.h"
#include "View.h"
#include "Dialog.h"

using namespace std;

void PrintMoves(const list<shared_ptr<const Board::Move>> &lst) {
   int numCols, col, maxLen = 1;
   const int maxCols = 80;
      
   for (auto lstItr = lst.begin(); lstItr != lst.end(); lstItr++)
      maxLen = max(maxLen, (int)((string)(**lstItr)).size());
   
   numCols = maxCols / (maxLen + 1); // Figure number of columns

   // Left justify following output
   cout << setiosflags(ios::left) << resetiosflags(ios::right);
   col = 0;
   for (auto lstItr = lst.begin(); lstItr != lst.end(); lstItr++) {
      if (!col)
        cout << endl;
      else
        cout << " ";
      col = (col + 1) % numCols;
      cout << setw(maxLen) << (string) **lstItr;
   }
   cout << endl;
}

int main(int argc, char **argv) {
   const int argLen = 200, maxCols = 80, minArgs = 2, maxArgs = 3;
   const BoardClass *boardClass;
   shared_ptr<Board> board;
   unique_ptr<View> brdView;
   unique_ptr<Dialog> brdDlg;
   shared_ptr<Board::Move> move, cmpMove;
   string command, arg, commandLine;
   char cArg[argLen];
   int count, seed, ndx, runLimit, commentStart;
   list<unique_ptr<Board::Move>> lst;
   list<shared_ptr<const Board::Move>> cLst;
   bool testRun, controlledTest;

   vector<const BoardClass *> boards = BoardClass::GetAllClasses();

   (void)maxCols;
   (void)cArg;

   if (argc < minArgs || argc > maxArgs) {
      cout << "Usage: BoardTest BoardClass [runLimit]" << endl;
      exit(1);
   }

   for (auto& bc : boards) {
      if (bc->GetName() == argv[1]) {
         boardClass = bc;
         board = shared_ptr<Board>(dynamic_cast<Board *>(boardClass->NewInstance()));
         brdView = unique_ptr<View>(dynamic_cast<View *>(boardClass->GetViewClass()->NewInstance()));
         brdDlg = unique_ptr<Dialog>(dynamic_cast<Dialog *>(boardClass->GetDlgClass()->NewInstance()));
         break;
      }
   }

   if (!board || !brdView || !brdDlg) {
      cout << "Failed to create classes or objects" << endl;
      exit(1);
   }

   controlledTest = argc == maxArgs;
   runLimit = controlledTest ? stoi(argv[2]) : -1;

   brdView->SetModel(board);
   move = board->CreateMove();

   while (cin && !cin.eof()) {
      try {
         getline(cin, commandLine);
         if (cin.eof())
            throw BaseException("Unexpected EOF");
            
         if ((commentStart = commandLine.find_first_of("#"))
          != (int)string::npos)
            commandLine = commandLine.substr(0, commentStart);
            
         if (commandLine.find_first_not_of(" \t") == string::npos)
            continue;

         istringstream cmdIn(commandLine);
         cmdIn >> command; // gets first word!
         // ************************ enterMove ************************
         if (command.compare("enterMove") == 0) {
            getline(cmdIn, arg);
            *move = arg;
         }
         // ************************ showMove ************************
         else if (command.compare("showMove") == 0) {
            cout << (string)*move << endl;
         }
         // ************************ applyMove ************************
         else if (command.compare("applyMove") == 0) {
            lst.clear();
            board->GetAllMoves(&lst);
            for (auto &mv : lst) {
                if (*mv == *move) {
                    board->ApplyMove(std::move(mv));
                    break;
                }
            }
         }
         // ************************ doMove ************************
         else if (command.compare("doMove") == 0) {
            getline(cmdIn, arg);
            *move = arg;
            lst.clear();
            board->GetAllMoves(&lst);
            for (auto &mv : lst) {
                if (*mv == *move) {
                    board->ApplyMove(std::move(mv));
                    break;
                }
            }
         }
         // ************************ showVal ************************
         else if (command.compare("showVal") == 0) {
            cout << "Value: " << board->GetValue() << endl;
         }
         // ************************ saveBoard ************************
         else if (command.compare("saveBoard") == 0) {
            cmdIn >> arg;
            ofstream strm(arg);
            board->Write(strm);
            strm.close();
         }
         // ************************ saveMove ************************
         else if (command.compare("saveMove") == 0) {
            cmdIn >> arg;
            ofstream strm(arg);
            move->Write(strm);
            strm.close();
         }
         // ************************ loadBoard ************************
         else if (command.compare("loadBoard") == 0) {
            cmdIn >> arg;
            ifstream strm(arg);
            board->Read(strm);
            strm.close();
         }
         // ************************ loadMove ************************
         else if (command.compare("loadMove") == 0) {
            cmdIn >> arg;
            ifstream strm(arg);
            move->Read(strm);
            strm.close();
         }
         // ************************ compareKeys ************************
         else if (command.compare("compareKeys") == 0) {
            cmdIn >> arg;
            auto oBoard = board->Clone();
            ifstream strm(arg);
            oBoard->Read(strm);
            strm.close();
            auto key = board->GetKey();
            auto oKey = oBoard->GetKey();
            
            if (*key == *oKey) {
                cout << "Board keys are equal" << endl;
            } else {
                cout << "Board keys are unequal" << endl;
                if (*key < *oKey) {
                    cout << "Current board is less than " << arg << endl;
                } else {
                    cout << "Current board is greater than " << arg << endl;
                }
            }
         }
         // ************************ compareMove ************************
         else if (command.compare("compareMove") == 0) {
            getline(cmdIn, arg);
            if (!cmpMove)
                cmpMove = board->CreateMove();
            *cmpMove = arg;
            if (*move == *cmpMove) {
                cout << "Moves are equal" << endl;
            } else if (*move < *cmpMove) {
                cout << "Current move is less than entered move" << endl;
            } else {
                cout << "Current move is greater than entered move" << endl;
            }
            cmpMove = nullptr;
         }
         // ************************ setOptions ************************
         else if (command.compare("setOptions") == 0) {
            void *rules = nullptr;
            try {
               rules = boardClass->GetOptions();
               if (brdDlg->Run(cin, cout, rules))
                  boardClass->SetOptions(rules);
               cout << endl;
               delete rules;
            } catch(BaseException &e) {
               if (rules)
                  delete rules;
               throw e;
            }
            continue;
         }
         // ************************ undoLastMove ************************
         else if (command.compare("undoLastMove") == 0) {
            if (!(cmdIn >> count) || count < 0) {
               cmdIn.clear();
               throw BaseException("Must have a nonnegative count for undoLastMove");
            }

            if (count > (int)board->GetMoveHist().size())
               count = board->GetMoveHist().size();

            while (count-- > 0)
               board->UndoLastMove();
         }
         // ************************ showMoveHist ************************
         else if (command.compare("showMoveHist") == 0) {
            cLst = board->GetMoveHist();
            cout << endl << "Move History: ";
            PrintMoves(cLst);
         }
         // ************************ showBoard ************************
         else if (command.compare("showBoard") == 0) {
            brdView->Draw(cout);
            lst.clear();
            board->GetAllMoves(&lst);
            cLst.clear();

            // for (auto uptr : lst) {                                      Nope
            for (auto &uptr : lst) {
               // cLst.push_back(uptr);                                     Nope
               // shared_ptr<Board::Move> tPtr = uptr;                      Nope
               // cLst.push_back(shared_ptr<Board::Move>(uptr));            Nope
               // cLst.push_back(shared_ptr<Board::Move>(move(uptr))); *&$! Nope
               // cLst.push_back(shared_ptr<Board::Move>(std::move(uptr))); YEP!
               cLst.push_back(std::move(uptr));                          // Best
            }

            cout << endl << "All Moves: ";
            PrintMoves(cLst);
         }

         // ************************ testPlay ************************
         // ************************ testRun  ************************
         else if (command.compare("testPlay") == 0
          || command.compare("testRun") == 0) {
            if (!(cmdIn >> seed >> count) || count < 0)
               throw BaseException("Bad arguments for testPlay/testRun");
               
            srand(seed);
            testRun = command.compare("testRun") == 0;
            runLimit -= count;
            
            if (controlledTest && runLimit < 0)
               throw BaseException("Run limit exceeded.");
            
            while (count-- > 0) {
               lst.erase(lst.begin(), lst.end());
               board->GetAllMoves(&lst);
               if (lst.size() == 0)
                  if (testRun) {
                     ndx = 1 + rand() % board->GetMoveHist().size();
                     while (ndx--)
                        board->UndoLastMove();
                  }
                  else
                     break;
               else {
                  ndx = rand() % lst.size();

                  auto itr = lst.begin();
                  while (ndx--)
                     itr++;
                  board->ApplyMove(std::move(*itr));
               }
            }
         }
         // ************************ keyMoveCount ************************
         else if (command.compare("keyMoveCount") == 0) {
            lst.clear();
            cLst.clear();
            cout << "Moves/Keys: " << Board::Move::GetOutstanding() << "/"
             << Board::Key::GetOutstanding() << endl;
         }
         // ************************ quit ************************
         else if (command.compare("quit") == 0)
            break;
         else
            cout << "Unknown command: " << command << endl;
      } 
      catch (BaseException &err) {
         cout << "Error: " << err.what() << endl;
      }
      cout << endl;
   }

   return 0;
}
