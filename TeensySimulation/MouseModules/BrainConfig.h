/*
 *
 *  Created on: 19 May 2021
 *      Author: David(Yong eel) Lee
*/

#ifndef BRAINCONFIG_H_
#define BRAINCONFIG_H_

#include <Simulation.h>

#define SIMULATION  1

/*
#define SIZE 6	// Size of one dimention of Map

#define GoalRight  5  // training
#define GoalUpper  3
*/


//#define SIZE 16	// Size of one dimention of Map

//#define GoalRight  SIZE/2  // classic
//#define GoalUpper  SIZE/2

#define SIZE 32		// Size of one dimension of Map

//#define GoalRight   25  // 2010 J
//#define GoalUpper   23
//#define GoalRight   26  // 2011 J
//#define GoalUpper   28
//#define GoalRight   23  // 2012 J
//#define GoalUpper   26
//#define GoalRight   7  // 2013 J
//#define GoalUpper   6
//#define GoalRight   26  // 2014 J
//#define GoalUpper   6
//#define GoalRight   7  // 2015 J
//#define GoalUpper   25
//#define GoalRight   3  // 2016 J
//#define GoalUpper   4

//#define GoalRight   20  // 2017 J
//#define GoalUpper   21

//#define GoalRight   13  // 2018 J
//#define GoalUpper   13

//#define GoalRight   18  // 2019 J
//#define GoalUpper   14

 // No match : 2020 - Covid

//#define GoalRight   17    // 2021 J
//#define GoalUpper   18

 // No match : 2022 - Covid

//#define GoalRight   9    // 2023 J
//#define GoalUpper   9

#define GoalRight   20  // 2024 J
#define GoalUpper   9

//#define SIZE 21		// Size of one dimension of Map

//#define GoalRight   6  // 2014 T
//#define GoalUpper   8

//#define GoalRight   14  // 2015 T
//#define GoalUpper   6

//#define GoalRight   18  // 2016 T
//#define GoalUpper   10

//#define GoalRight   2   // 2017 T
//#define GoalUpper   1

//#define GoalRight   15   // 2018 T
//#define GoalUpper   3




#define GoalLeft    GoalRight - 1
#define GoalLower   GoalUpper - 1

#define START_X 0       // coordinate (x, y) origin
#define START_Y 0
#define LARGEVAL 255


//***************************************************************************//

// This is the size fo each cell in the maze. Normally 180mm for a classic maze
const float FULL_CELL = 180.0f;
const float HALF_CELL = FULL_CELL / 2.0;
const float DIAG_CELL = sqrt(HALF_CELL*HALF_CELL+HALF_CELL*HALF_CELL);

//***** PERFORMANCE CONSTANTS************************************************//
// search and run speeds in mm/s and mm - 300, 400, 800, 2000
const float DEFAULT_TURN_SPEED     = 300;
const float DEFAULT_EXPLORE_SPEED  = 400;
const float DEFAULT_SMOOTH_SPEED   = DEFAULT_TURN_SPEED * 0.8f;
const float DEFAULT_TURN_ACCEL     = 1000;
const float DEFAULT_EXPLORE_ACCEL  = 2000;
const float DEFAULT_SMOOTH_ACCEL   = DEFAULT_TURN_ACCEL * 2.0f;
//***************************************************************************//
const float SPEED_RATE               = 1.0f;
const float SPEEDMAX_EXPLORE         = DEFAULT_EXPLORE_SPEED  * SPEED_RATE;
const float SPEEDMAX_SPIN_TURN       = DEFAULT_TURN_SPEED     * SPEED_RATE;
const float SPEEDMAX_SMOOTH_TURN     = DEFAULT_SMOOTH_SPEED   * SPEED_RATE;
const float EXPLORE_ACCELERATION     = DEFAULT_EXPLORE_ACCEL  * SPEED_RATE;
const float SPIN_TURN_ACCELERATION   = DEFAULT_TURN_ACCEL     * SPEED_RATE;
const float SMOOTH_TURN_ACCELERATION = DEFAULT_SMOOTH_ACCEL   * SPEED_RATE;
//#define SPEEDMAX_STRAIGHT          = 800 * SPEED_RATE;

// Directions
enum {
	NORTH,
	EAST,
	SOUTH,
	WEST,
	NORTHEAST,
	NORTHWEST,
	SOUTHEAST,
	SOUTHWEST,
	EASTNORTH,
	EASTSOUTH,
	WESTNORTH,
	WESTSOUTH,
};

// Moving Action type

enum {

	  A_turnLeft45,
	  A_turnRight45,

	  A_turnLeft90,
	  A_turnRight90,

	  A_turnBack,

	  A_moveEdgeForward,
	  A_moveHalfForward,
	  A_moveFullForward,

	  A_smoothLeft90,
	  A_smoothRight90,
	  A_smoothTurnBack,
	  A_smoothFullForward,

};

// New Type for maze
typedef struct Direction {
	uint8_t left45;
	uint8_t left90;
	uint8_t right45;
	uint8_t right90;
	uint8_t opposite;
	short angle;
	uint8_t type;
} Direction ;

const Direction dir_info[12] = {
		{ NORTHWEST , WEST,  NORTHEAST, EAST, SOUTH, 90, DIR4 },  // NORTH
		{ EASTNORTH , NORTH, EASTSOUTH, SOUTH,WEST,   0, DIR4 },  // EAST
		{ SOUTHEAST , EAST,  SOUTHWEST, WEST, NORTH,270, DIR4 },  // SOUTH
		{ WESTSOUTH , SOUTH, WESTNORTH, NORTH,EAST, 180, DIR4 },  // WEST

	    { NORTH , NORTHWEST, EAST,  EASTSOUTH,EASTNORTH, 45, DIR8 },  // NORTHEAST
		{ WEST  , WESTSOUTH, NORTH, NORTHEAST,WESTNORTH,135, DIR8 },  // NORTHWEST
		{ EAST  , EASTNORTH, SOUTH, SOUTHWEST,EASTSOUTH,315, DIR8 },  // SOUTHEAST
		{ SOUTH , SOUTHEAST, WEST,  WESTNORTH,WESTSOUTH,225, DIR8 },  // SOUTHWEST

		{ NORTH , NORTHWEST, EAST,  EASTSOUTH,NORTHEAST, 45, DIR8 },  // EASTNORTH
		{ EAST  , EASTNORTH, SOUTH, SOUTHWEST,SOUTHEAST,315, DIR8 },  // EASTSOUTH
		{ WEST  , WESTSOUTH, NORTH, NORTHEAST,NORTHWEST,135, DIR8 },  // WESTNORTH
		{ SOUTH , SOUTHEAST, WEST,  WESTNORTH,SOUTHWEST,225, DIR8 },  // WESTSOUTH
};

typedef struct
{
	float angle; // deg     ; rotation distance
	float omega; // deg/s   : rotation speed
	float alpha; // deg/s/s : rotation acceleration
	float distance;
	float top_speed;
	float final_speed;
	float acceleration;
	float run_in ;  // mm
	float run_out;  // mm
} TurnParameter;


const TurnParameter TurnParms[12] =
{

	{ // A_turnLeft45,
		  45.0f, SPEEDMAX_SPIN_TURN, SPIN_TURN_ACCELERATION, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	},
	{ // A_turnRight45
		 -45.0f, SPEEDMAX_SPIN_TURN, SPIN_TURN_ACCELERATION, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	},
	{ //  A_turnLeft90
		  90.0f, SPEEDMAX_SPIN_TURN, SPIN_TURN_ACCELERATION, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	},
	{ // A_turnRight90
		 -90.0f, SPEEDMAX_SPIN_TURN, SPIN_TURN_ACCELERATION, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	},
	{ // A_turnBack
		-180.0f, SPEEDMAX_SPIN_TURN, SPIN_TURN_ACCELERATION, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	},
	{ // A_moveEdgeForward,
		 0.0f, 0.0f, 0.0f, DIAG_CELL, SPEEDMAX_EXPLORE, 0.0f, EXPLORE_ACCELERATION, 0.0f, 0.0f
	},
	{ // A_moveHalfForward
		 0.0f, 0.0f, 0.0f, HALF_CELL, SPEEDMAX_EXPLORE, 0.0f, EXPLORE_ACCELERATION, 0.0f, 0.0f
	},
	{ // A_moveFullForward
		 0.0f, 0.0f, 0.0f, FULL_CELL, SPEEDMAX_EXPLORE, 0.0f, EXPLORE_ACCELERATION, 0.0f, 0.0f
	},
	{ // A_smoothLeft90,
		  90.0f, SPEEDMAX_SMOOTH_TURN, SMOOTH_TURN_ACCELERATION, 0.0f, SPEEDMAX_EXPLORE, SPEEDMAX_EXPLORE, EXPLORE_ACCELERATION, 15.0f, 10.0f
	},
	{ // A_smoothRight90,
		 -90.0f, SPEEDMAX_SMOOTH_TURN, SMOOTH_TURN_ACCELERATION, 0.0f, SPEEDMAX_EXPLORE, SPEEDMAX_EXPLORE, EXPLORE_ACCELERATION, 15.0f, 10.0f
	},
	{ // smoothTurnBack,
	    -180.0f, SPEEDMAX_SMOOTH_TURN, SMOOTH_TURN_ACCELERATION, 0.0f, SPEEDMAX_EXPLORE, SPEEDMAX_EXPLORE, EXPLORE_ACCELERATION, 0.0f, 0.0f
	},
	{ // smoothFullForward,
		  0.0f, 0.0f, 0.0f, FULL_CELL, SPEEDMAX_EXPLORE, SPEEDMAX_EXPLORE, EXPLORE_ACCELERATION, 0.0f, 0.0f
	},


};

#endif /* BRAINCONFIG_H_ */
