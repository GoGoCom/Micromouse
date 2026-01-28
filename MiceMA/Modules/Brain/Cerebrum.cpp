/*
 * Cerebrum.cpp
 *
 *  Created on: Feb 10, 2024
 *      Author: apex6
 */

#include <Mouse.h>
#include <BrainConfig.h>

#include <Cerebrum.h>

#include <Buffers.h>
#include <Floodfill.h>
#include <Simulation.h>
#include <Buffers.h>
#include <ee.h>
#include <eeConfig.h>

//#define DEBUG_LOG  1


Cerebrum::Cerebrum() {
	// TODO Auto-generated constructor stub

}

Cerebrum::~Cerebrum() {
	// TODO Auto-generated destructor stub
}

void Cerebrum::CerebrumInit(Simulation *simp) {
	hSmp = simp;
}

/*** Struct Constructors and Destructors ***/
/* MazeCells Constructor */
MazeCells * Cerebrum::new_Maze (void) {
	MazeCells * mouse_maze;
	uint8_t i, j;

	mouse_maze = (MazeCells *) malloc(sizeof(MazeCells));
	/* Allocate a new Node for each coord of maze */
	for (i = 0; i < SIZE; ++i)
		for (j = 0; j < SIZE; ++j)
			mouse_maze->Block[i][j] = ns.new_Node (i, j);
	/* setting the neighbors ptrs... must be done after all cells allocated */
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			mouse_maze->Block[i][j]->neighbours[WEST] = (i == 0) ? NULL : (mouse_maze->Block[i-1][j]);
			mouse_maze->Block[i][j]->neighbours[EAST] = (i == SIZE-1) ? NULL : (mouse_maze->Block[i+1][j]);
			mouse_maze->Block[i][j]->neighbours[SOUTH] = (j == 0) ? NULL : (mouse_maze->Block[i][j-1]);
			mouse_maze->Block[i][j]->neighbours[NORTH] = (j == SIZE-1) ? NULL : (mouse_maze->Block[i][j+1]);
		}
	}
	return mouse_maze;
}
/* MazeCells Destructor */
void Cerebrum::delete_Maze () {
	uint8_t i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			ns.delete_Node (&(mouse_maze->Block[i][j]));
	free(mouse_maze);
	mouse_maze = 0;
}

/* prints the flood values of each cell in the maze */
void Cerebrum::print_map () {
	char buf[30];
	uint8_t i, j, k;
	char dirc[4] = {'n','e','s','w' };

	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			sprintf(buf, "%3hd", mouse_maze->Block[i][j]->floodval);
			  if( hSmp != NULL ) {
				  for(k=0; k<4; k++) {
					  if( mouse_maze->Block[i][j]->neighbours[k] == NULL ) hSmp->setWall(i, j, dirc[k]);
					  delay(1);
				  }
				  hSmp->setText(i, j, (char *) buf);
				  delay(1);
			  }
		}
	}
}

/* update flag for whether goal cell was reached */
bool Cerebrum::check_start_reached ( Node *this_node, bool * found_start) {
  if (this_node->x == START_X && this_node->y == START_Y) {
#if SIMULATION == 1
    if( hSmp != NULL ) hSmp->setText(this_node->x, this_node->y, (char *) "S");
#endif
    *(found_start) = true;
    printf("log Start Coorinates Reached!\n");
    return true;
  }
  return false;
}

/* update flag for whether goal cell was reached */
bool Cerebrum::check_goal_reached ( Node *this_node, bool * found_goal) {
  if ( ( this_node->x >= GoalLeft && this_node->x <= GoalRight ) && ( this_node->y >= GoalLower  && this_node->y <= GoalUpper) ) {
#if SIMULATION == 1
    if( hSmp != NULL ) hSmp->setText(this_node->x, this_node->y, (char *) "G");
#endif
    *(found_goal) = true;
    printf("log Goal Coordinates Reached!\n");
    return true;
  }
  return false;
}


/* Function for setting the walls of this node */
void Cerebrum::SetWall (Node * this_node, const uint8_t dir) {

	this_node->neighbours[dir] = NULL;

#if SIMULATION == 1
	char dirc[4] = {'n','e','s','w' } ;

	if( hSmp != NULL ) hSmp->setWall(this_node->x, this_node->y, dirc[dir]);
#endif

}

void Cerebrum::SetGoalWall(Node *this_node, uint8_t mdir) {
    this_node->neighbours[mdir] = NULL;
    this_node->neighbours[dir_info[mdir].left90]  = NULL;
    this_node->neighbours[dir_info[mdir].right90] = NULL;
}

void Cerebrum::OptimizePath(void)  {
	uint8_t i, j, k;

	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			Node *this_node=mouse_maze->Block[i][j];

			  if ( this_node->visited == false ) {
				  for(k=0; k<4; k++) {
					  if( (this_node->neighbours[k] != NULL) && ( this_node->neighbours[k]->visited == true ) ) {
						  this_node->neighbours[ k ]->neighbours[ dir_info[k].opposite  ] = NULL;
						  this_node->neighbours[ k ] = NULL;
					  }
				  }
			  }
		}
	}
}

uint8_t Cerebrum::EdgeRunDirection(uint8_t dir, uint8_t exit_dir) {


	switch ( dir ) {
	 case  NORTH :
		  switch(exit_dir ) {
			case EAST :
				return NORTHEAST;
			case WEST :
				return NORTHWEST;
		  }
		  break;
	 case  SOUTH :
		  switch(exit_dir ) {
			case EAST :
				return SOUTHEAST;
			case WEST :
				return SOUTHWEST;
		  }
		  break;
	 case  EAST :
		  switch(exit_dir ) {
			case NORTH :
				return EASTNORTH;
			case SOUTH :
				return EASTSOUTH;
		  }
		  break;
	 case  WEST :
		  switch(exit_dir ) {
			case NORTH :
				return WESTNORTH;
			case SOUTH :
				return WESTSOUTH;
		  }
		  break;
	 }

  return exit_dir;
}



void Cerebrum::PathDisplay(uint8_t dir, uint8_t dis, uint8_t mx, uint8_t my, bool pass) {

  if( ( 0<= dir ) && ( dir < 16 ) ) {
	  if( !pass )
		  printf("log P1 (%2d,%2d)-[%2s,%2d]\n",mx, my, dir_ch[dir], dis);
	  else
		  printf("log P2 (%2d,%2d)-[%2s,%2d]\n",mx, my, dir_ch[dir], dis);
  } else
	  printf("log direction error (%2d,%2d)-%d\n",mx, my, dir);
}

int Cerebrum::Diff_Angle(uint8_t sr, uint8_t ds){

	if( ds == dir_info[sr].left90   ) return -2;
	if( ds == dir_info[sr].left45   ) return -1;
	if( ds == dir_info[sr].right90  ) return +2;
	if( ds == dir_info[sr].right45  ) return +1;
	if( ds == dir_info[sr].opposite ) return  3;

	return 0;
}

void Cerebrum::Reflooding( Node *this_node, bool direction ) {

	Node *temp_node;

	uint8_t fillvalue = direction ? LARGEVAL : 0; // direction -- false -> start to Goal, true -> Goal to Start

    // with start as zero, update everycell's floodval
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
    	  mouse_maze->Block[i][j]->floodval = fillvalue;

    // set the start value to zero
    mouse_maze->Block[START_X][START_Y]->floodval = 0 ;

    fdf.push_open_neighbors(this_node, mouse_stack);
    while(!Bufs.is_empty_Stack(mouse_stack)) {
      Bufs.pop(mouse_stack, &temp_node);
#if DEBUG_LOG == 1
      printf("log NEW LOCATION: %d, %d, %d\n", temp_node->x, temp_node->y, mouse_stack->properties[1]);
#endif
      fdf.flood_fill(temp_node, mouse_stack, direction);
    }

#if DEBUG_LOG == 1
    	printf("log cells have been reflooded. \n");
        print_map();
#endif

}

// Reflooding process from start to goal
// Set everything to 255 !
void Cerebrum::StartToGoalReflooding( uint8_t x , uint8_t y  ) {

	Reflooding( mouse_maze->Block[x][y], true );

}

// Reflooding process from start to goal
// Set everything to 0 !
void Cerebrum::GoalToStartReflooding(uint8_t x , uint8_t y  ) {

	Reflooding( mouse_maze->Block[x][y], false );

#if SIMULATION == 1
    if( hSmp != NULL ) hSmp->clearAllColor();
#endif

}


bool Cerebrum::ReadPath(  Queue *this_queue ){
	ee_read(0x0, sizeof(Queue), (uint8_t *) this_queue);
    return true;
}

bool Cerebrum::WritePath(  Queue *this_queue ){
    ee_writeToRam(0x0, sizeof(Queue), (uint8_t *)  this_queue);
    ee_commit();
    return true;
}


void Cerebrum::SetResources() {
	// allocating maze solving resources
	mouse_maze = new_Maze();        // Initialize new maze
	mouse_stack = Bufs.new_Stack();  // Initialize new stack

	ee_init();
}
void Cerebrum::ResetResources(void) {

    Bufs.delete_Stack (&mouse_stack);
    delete_Maze();
}

uint8_t Cerebrum::GetNextDirectionSub( Node *this_node, uint8_t mdir, bool direction ) {

  uint8_t   exit_dir = NORTH, type = 0;

	if ( this_node->neighbours[mdir] != NULL ) return mdir ; // prior forward direction

	if( !direction ) { // to goal position
		switch(mdir) {  // prior  goal direction
			case NORTH :
				type = this_node->x <= GoalLeft  ? 0 : 1;
				break;
			case SOUTH :
				type = this_node->x <= GoalLeft  ? 1 : 0;
				break;
			case EAST :
				type = this_node->y <= GoalLower ? 1 : 0;
				break;
			case WEST :
				type = this_node->y <= GoalLower ? 0 : 1;
				break;
			default :
				break;
		}
	}
	else { // to start position
		switch(mdir) {
			case NORTH :
			case WEST  :
						type = 1;
						break;
			case SOUTH :
			case EAST  :
						type = 0;
						break;
			default :
				break;
		}
	}

	if( type == 0 ) { // priority right
		if ( this_node->neighbours[dir_info[mdir].right90]  != NULL )  exit_dir = dir_info[mdir].right90  ;
		else if ( this_node->neighbours[dir_info[mdir].left90]  != NULL )  exit_dir = dir_info[mdir].left90  ;
			 else exit_dir = dir_info[mdir].opposite;  // backward direction
	} else {
		if ( this_node->neighbours[dir_info[mdir].left90]  != NULL )  exit_dir = dir_info[mdir].left90  ;
		else if ( this_node->neighbours[dir_info[mdir].right90]  != NULL )  exit_dir = dir_info[mdir].right90 ;
			 else exit_dir = dir_info[mdir].opposite;
	}

	return exit_dir;
}

uint8_t Cerebrum::GetNextDirection( Node *this_node, uint8_t mdir, bool direction ) {
  uint8_t   exit_dir = NORTH;

    if(this_node->visited ){ // visited

    	if( this_node->pathCount == 1) {
    		if( this_node->neighbours[ mdir ] != NULL ) exit_dir=mdir;
    		else if( this_node->neighbours[ dir_info[mdir].right90 ] != NULL ) exit_dir=dir_info[mdir].right90;
				 else if( this_node->neighbours[ dir_info[mdir].left90  ] != NULL ) exit_dir=dir_info[mdir].left90;
    	}

    	if( this_node->pathCount > 1) {

    		int diff = Diff_Angle(mdir, this_node->exitedDir);

    		if( diff!=0  ) {
				if( this_node->neighbours[ mdir ] != NULL )  {
					if( this_node->enteredDir != mdir ) return mdir;
				}
    		}
    		switch(diff) {
    			case -2 : if( this_node->neighbours[ dir_info[mdir].right90  ] == NULL )
								exit_dir = mdir;
						  else
							    exit_dir=dir_info[mdir].right90 ; // turned around left
    					break;
    			case +2 :
    					if( this_node->neighbours[ dir_info[mdir].left90  ] == NULL )
    						exit_dir = mdir;
    					else
    				        exit_dir= dir_info[mdir].left90 ; // turned around right
    					break;
    			case -1 :
    			case +1 :
    				     break;
    			case +3 :
    			default :
					if( ( this_node->neighbours[ dir_info[mdir].right90 ] != NULL ) && ( this_node->neighbours[ dir_info[mdir].left90  ] != NULL ) ) {
						 if(  this_node->passCount[ dir_info[mdir].left90 ] <= this_node->passCount[ dir_info[mdir].right90 ] ) exit_dir=dir_info[mdir].left90;
						 else exit_dir=dir_info[mdir].right90;
					}
					else if( this_node->neighbours[ dir_info[mdir].left90  ] == NULL ) exit_dir=dir_info[mdir].right90;
					     else if( this_node->neighbours[ dir_info[mdir].right90  ] == NULL ) exit_dir=dir_info[mdir].left90;
					break;
    		}

    	}

    } else {
    	 exit_dir = GetNextDirectionSub( this_node, mdir, direction ) ;
    }
	return exit_dir;
}


void Cerebrum::SetWallCell (  Node *this_node, uint8_t mdir, bool wallFront, bool wallLeft, bool wallRight  ) {

	if( wallLeft   ) SetWall(this_node, WallInfo[mdir].left);
	else this_node->pathCount++;
	if( wallFront  ) SetWall(this_node, WallInfo[mdir].forward);
	else this_node->pathCount++;
	if( wallRight  ) SetWall(this_node, WallInfo[mdir].right);
	else this_node->pathCount++;

}

