#pragma once

#ifdef _WIN32
#include "stdafx.h"
#endif

#include <string>
#include <ctime>
#include <fstream>
using namespace std;

class Player
{
public:

  Player(string playerName);
  string getName();
  void start();
  void end();
  void gotHint();
  unsigned int timeToComplete();


private:

  time_t startTime, endTime;
  string name;
  unsigned int nHints;

};
