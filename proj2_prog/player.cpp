#ifdef _WIN32
#include "stdafx.h"
#endif

#include "player.h"
using namespace std;

Player::Player(string playerName)
{
  name = playerName;
  startTime = 0;
  endTime = 0;
  nHints = 0;
}

string Player::getName()
{
  return name;
}

void Player::start()
{
  time(&startTime);
}

void Player::end()
{
  time(&endTime);
}

void Player::gotHint()
{
  nHints++;
}

unsigned int Player::timeToComplete()
{
  return difftime(endTime, startTime);
}
