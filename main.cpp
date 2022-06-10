#include "Game.hpp"

#include <iostream>

using namespace std;

/*
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

*/

int main()
{
  Game game("Horse Racing");
  game.Run();
  return 0;
}
