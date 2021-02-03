# General test makefile for multi-target test
# Copyright Clinton Staley 12/1/01

# General definitions
CPP = /usr/local/bin/g++
CPPFLAGS = -std=c++11 -g -w -O3 -DLITTLE_ENDIAN
LINKFLAGS = -static-libstdc++

MANCALAOBJS = MancalaBoard.o MancalaMove.o MancalaView.o MancalaDlg.o
OTHELLOOBJS = OthelloBoard.o OthelloMove.o OthelloView.o OthelloDlg.o
PYLOSOBJS = PylosBoard.o PylosMove.o PylosView.o PylosDlg.o
CHECKERSOBJS = CheckersBoard.o CheckersMove.o CheckersView.o CheckersDlg.o
GAMEOBJS = Board.o Dialog.o Class.o $(OTHELLOOBJS) $(CHECKERSOBJS) $(MANCALAOBJS)
BOARDTESTOBJS = BoardTest.o $(GAMEOBJS)
MYBOARDTESTOBJS = MyBoardTest.o $(GAMEOBJS)
MAKEBOOKOBJS = MakeBook.o Book.o SimpleAIPlayer.o $(GAMEOBJS)
MINIMAXOBJS = MinimaxApp.o Steppable.o AIPlayer.o GameModel.o GameView.o HumanPlayer.o Book.o $(GAMEOBJS)

MinimaxApp : $(MINIMAXOBJS)
	$(CPP) $(LINKFLAGS) $(MINIMAXOBJS) -o MinimaxApp

MakeBook : $(MAKEBOOKOBJS)
	$(CPP) $(LINKFLAGS) $(MAKEBOOKOBJS) -o MakeBook

MyBoardTest : $(MYBOARDTESTOBJS)
	$(CPP) $(LINKFLAGS) $(MYBOARDTESTOBJS) -o MyBoardTest

BoardTest : $(BOARDTESTOBJS)
	$(CPP) $(LINKFLAGS) $(BOARDTESTOBJS) -o BoardTest

BTRelease: BoardTest BoardTest.o
	chmod 755 BoardTest
	chmod 644 BoardTest.o
	mv BoardTest BoardTest.o ../../milestone1

MBRelease: MakeBook
	chmod 755 MakeBook
	mv MakeBook ../../prj2

MMARelease: MinimaxApp
	cp MinimaxApp Pylos.gbk ../../prj3
	chmod 755 ../../prj3/MinimaxApp
	chmod 644 ../../prj3/Pylos.gbk

clean:
	rm BoardTest MyBoardTest *.o

# Header file interdependencies

CheckersDlg.h OthelloDlg.h MancalaDlg.h PylosDlg.h: Dialog.h
	touch MancalaDlg.h PylosDlg.h CheckersDlg.h OthelloDlg.h

MancalaView.h PylosView.h OthelloView.h CheckersView.h : View.h
	touch MancalaView.h PylosView.h OthelloView.h CheckersView.h

MancalaBoard.cpp: Class.h Board.h
	touch MancalaBoard.cpp
MancalaMove.cpp: MancalaBoard.h Class.h Board.h
	touch MancalaMove.cpp
MancalaView.cpp: MancalaBoard.h View.h Class.h Board.h
	touch MancalaView.cpp
MancalaDlg.cpp: MancalaBoard.h Dialog.h Class.h
	touch MancalaDlg.cpp

OthelloBoard.cpp: Class.h Board.h
	touch OthelloBoard.cpp
OthelloMove.cpp: OthelloBoard.h Class.h Board.h
	touch OthelloMove.cpp
OthelloView.cpp: OthelloBoard.h View.h Class.h Board.h
	touch OthelloView.cpp
OthelloDlg.cpp: OthelloBoard.h Dialog.h Class.h
	touch OthelloDlg.cpp

PylosBoard.cpp: Class.h Board.h
	touch PylosBoard.cpp
PylosMove.cpp: PylosView.h PylosBoard.h  Board.h
	touch PylosMove.cpp
PylosView.cpp: PylosBoard.h View.h Class.h  Board.h
	touch PylosView.cpp
PylosDlg.cpp: PylosBoard.h Dialog.h Class.h 
	touch PylosDlg.cpp

CheckersBoard.cpp: Class.h Board.h
	touch CheckersBoard.cpp
CheckersMove.cpp: CheckersView.h CheckersBoard.h  Board.h
	touch CheckersMove.cpp
CheckersView.cpp: CheckersBoard.h View.h Class.h  Board.h
	touch CheckersView.cpp
CheckersDlg.cpp: CheckersBoard.h Dialog.h Class.h 
	touch CheckersDlg.cpp

BoardTest.cpp: Board.h View.h Dialog.h

%.cpp: %.h
	touch $@

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

# DO NOT DELETE
