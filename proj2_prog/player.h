#pragma once

#include <string>
#include <ctime>
#include <fstream>
using namespace std;

class Player
{
public:

  Player(string playerName);
  string getName() const;
  void start();
  void end();
  void gotHint();
  int timeToComplete() const;
  int getNumHints() const;


private:

  time_t startTime, endTime;
  string name;
  int nHints;

};
