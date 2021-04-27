#include <fstream>
#include "MinimaxApp.h"
#include "GameView.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "MyLib.h"

using namespace std;

MinimaxApp MinimaxApp::mApp;

MinimaxApp::MinimaxApp() : mView(0), mModel(0) {
   mModel = make_shared<GameModel>();
   mView = make_shared<GameView>(mModel, cout);
}

void MinimaxApp::Run() {
   int level;
   string players[2], type;
   
   // Do some setup, and prompt for and set up first game   

   while (Steppable::SteppablesExist())
      Steppable::StepAll();
}

int main(int argc, char **argv) 
{
   try {
      MinimaxApp::GetApp()->Run();
   } catch (BaseException &err) {
      cerr << "Error: " << err.what() << endl;
   }

   return 0;
}
