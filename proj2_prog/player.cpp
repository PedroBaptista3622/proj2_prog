#include "player.h"

using namespace std;

/**
 * Constructs a player from their nickname
 * 
 * @param	playerName	The name of the player
 */
Player::Player(string playerName)
{
  name = playerName;
  startTime = 0;
  endTime = 0;
  nHints = 0;
}

/**
 * Returns the player's name
 * 
 * @return	Name of the player
 */
string Player::getName() const
{
  return name;
}

/**
 * Records start time
 */
void Player::start()
{
  time(&startTime);
}

/**
 * Records end time
 */
void Player::end()
{
  time(&endTime);
}

/**
 * Increments number of hints
 */
void Player::gotHint()
{
  nHints++;
}

/**
 * Returns the time it took to complete the task
 * 
 * @return	Time starting and ending task, in seconds
 */
int Player::timeToComplete() const
{
  return difftime(endTime, startTime);
}

/**
 * Returns the number of hints the player has gotten.
 * 
 * @return	Number of hints received
 */
int Player::getNumHints() const
{
	return nHints;
}
