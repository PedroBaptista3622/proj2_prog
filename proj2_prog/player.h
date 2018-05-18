#pragma once

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
  int timeToComplete();


private:

  time_t startTime, endTime;
  string name;
  int nHints;

};
