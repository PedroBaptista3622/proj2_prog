#pragma once

#include <string>
#include <ctime>
#include <fstream>
using namespace std;

/**
 * Represents a player, handling their nickname, the time they take to complete
 * a task, and how many times they were helped.
 * 
 * @author	João N. Matos
 * @author	José Pedro Baptista
 */
class Player
{
public:

	/**
	 * Constructs a player from their nickname
	 * 
	 * @param	playerName	The name of the player
	 */
	Player(string playerName);

	/**
	 * Returns the player's name
	 * 
	 * @return	Name of the player
	 */
	string getName() const;

	/**
	 * Records start time
	 */
	void start();

	/**
	 * Records end time
	 */
	void end();

	/**
	 * Increments number of hints
	 */
	void gotHint();

	/**
	 * Returns the time it took to complete the task
	 * 
	 * @return	Time starting and ending task, in seconds
	 */
	int timeToComplete() const;

	/**
	 * Returns the number of hints the player has gotten.
	 * 
	 * @return	Number of hints received
	 */
	int getNumHints() const;


private:

	time_t startTime, endTime;
	string name;
	int nHints;

};
