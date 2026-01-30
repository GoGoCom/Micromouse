/*
 * Simulation.h
 *
 *  Created on: 17 May 2021
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Mack / mackorone
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

class Simulation {
public:
	Simulation();
	virtual ~Simulation();

	// API
	void log(char *message);
	int mazeWidth();
	int mazeHeight() ;

	bool FrontWallFront(int halfStepsAway) ;
	bool FrontWallRight(int halfStepsAway) ;
	bool FrontWallLeft(int halfStepsAway)  ;

	bool BackWallBack(int halfStepsAway)  ;
	bool BackWallRight(int halfStepsAway) ;
	bool BackWallLeft(int halfStepsAway)  ;

	bool wallFront();
	bool wallRight();
	bool wallLeft() ;

	bool moveFullForward(short distance);
	bool moveHalfForward(short numHalfSteps);
	bool moveEdgeForward(short numHalfSteps);

	void runRight();
	void runLeft();

	void turnRight90();
	void turnLeft90();
	void turnRight45();
	void turnLeft45();
	void turnBack();

	void completeRun();

	void setWall(int x, int y, char direction);
	void clearWall(int x, int y, char direction);
	void setColor(int x, int y, char color);
	void clearColor(int x, int y);
	void clearAllColor() ;
	void setText(int x, int y, char * text);
	void clearText(int x, int y);
	void clearAllText();
	bool wasReset();
	void ackReset();
	// ----- Helpers -----
	char *readline() ;
	char *communicate(char * command);
	bool getAck(char * command);
	bool getBoolean(char * command);
	int  getInteger(char * command);
};

#endif /* SIMULATION_H_ */
