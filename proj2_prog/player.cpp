#include "player.h"

using namespace std;

Player::Player(string playerName)
{
  name = playerName;
  startTime = 0;
  endTime = 0;
  nHints = 0;
}

string Player::getName() const
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

int Player::timeToComplete() const
{
  return difftime(endTime, startTime);
}

int Player::getNumHints() const
{
	return nHints;
}
