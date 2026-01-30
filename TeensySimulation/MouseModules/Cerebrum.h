/*
 * Cerebrum.h
 *
 *  Created on: Feb 10, 2024
 *      Author: David(Yong eel) Lee
*/

#ifndef CEREBRUM_H_
#define CEREBRUM_H_

#define	IMPLEMENTATION	FIFO

#include <Mouse.h>

#include <Buffers.h>
#include <Floodfill.h>
#include <Nodes.h>

typedef struct MazeCells {

	Node * Block[SIZE][SIZE]; // x, y

} MazeCells;

class Cerebrum {
public:
	Cerebrum();
	virtual ~Cerebrum();

	Buffers    Bufs;
	Nodes      ns;
	Floodfill  fdf;
	Simulation *hSmp;

	const char *dir_ch[16] = { "N","E","S","W","NE","NW","SE","SW","EN","ES","WN","WS","err12","err13","err14","OT" };

	struct {
		uint8_t left;
		uint8_t forward;
		uint8_t right;
	} WallInfo[4] = { {WEST, NORTH,EAST}, {NORTH, EAST, SOUTH }, {EAST, SOUTH, WEST}, {SOUTH,WEST,NORTH} }  ;

	MazeCells  *mouse_maze;   // maze for keeping track of flood values and walls
	Stack      *mouse_stack;  // stack used for flood fill

	bool  flooded = false;


	// Functions
	void CerebrumInit(Simulation *simp);

	void SetResources  (void);
	void ResetResources(void);

	MazeCells * new_Maze (void);
	void delete_Maze (void);
	void print_map   (void);

	// update flag for whether goal or start cell was reached
	bool check_start_reached ( Node *this_node, bool * found_start) ;
	bool check_goal_reached  ( Node *this_node, bool * found_goal) ;

	// save or read the shortest path
	bool ReadPath ( Queue *this_queue );
	bool WritePath( Queue *this_queue );

	// function for updating the location and direction of mouse
	void  OptimizePath(void) ;
	void  StartToGoalReflooding( uint8_t x , uint8_t y );
	void  GoalToStartReflooding( uint8_t x , uint8_t y );

	void  SetGoalWall( Node *this_node, uint8_t mdir);
	void  SetWall    ( Node *this_node, const uint8_t dir);
	void  SetWallCell( Node *this_node, uint8_t mdir, bool wallFront, bool wallLeft, bool wallRight  );
	void  Reflooding ( Node *this_node, bool direction);
	void  PathDisplay(uint8_t dir, uint8_t dis, uint8_t mx, uint8_t my, bool pass);

	int   Diff_Angle(uint8_t sr, uint8_t ds);
	uint8_t EdgeRunDirection(uint8_t dir, uint8_t next_dir);

	uint8_t GetNextDirection   ( Node *this_node, uint8_t mdir, bool direction );
	uint8_t GetNextDirectionSub( Node *this_node, uint8_t mdir, bool direction );

};


#endif /* CEREBRUM_H_ */
