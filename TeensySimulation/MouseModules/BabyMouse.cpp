/*
 * BabyMouse.cpp
 *
 *  Created on: Feb 10, 2024
 *      Author: David(Yong eel) Lee
*/

#include <Mice.h>
#include <BrainConfig.h>
#include <BodyConfig.h>

#include <BabyMouse.h>

#include <CDriveSensors.h>

#include <Buffers.h>
#include <Floodfill.h>
#include <Simulation.h>

//extern Direction dir_info[12] ;

//#define DEBUG_LOG  1

BabyMouse::BabyMouse( Simulation *simp )
{
	// TODO Auto-generated constructor stub
	miceInit(simp);
}

BabyMouse::~BabyMouse() {
	// TODO Auto-generated destructor stub
}

bool  BabyMouse::WalkToGoal ( ){
	return FindGoal( false );
}

bool  BabyMouse::RunToGoal  ( ){
	return FindGoal( true );
}

bool BabyMouse::FindGoal ( bool mode ) {

	// allocating maze solving resources
	mouse_queue = bufs.new_Queue();  // Initialize new stack

	SetResources();

	  if( mode == false ) { // false - from searching, true - optimized path

		// TRIP FROM START TO GOAL
		printf("log Child mouse goes to Goal position\n");
		if( StartToGoal( NORTH) == true ) {
			printf("log go to Start position\n");
			if(GoalToStart( mouse_direction) ==  true ) {
				printf("log go to Goal position directly\n");

				uint8_t lx = START_X;
				uint8_t ly = START_Y;
				uint8_t startDir = NORTH;

				Buildshortcut( mouse_queue, &lx, &ly, lx, ly, startDir, true);
				mouse_queue->mouse_dir = startDir; // save last position
				WritePath(mouse_queue);
			    MoveAction(mouse_queue, startDir);

			}
		}

	  } else { // go to the goal directly without searching.

#if SIMULATION == 1
		  if( hsmp != NULL )
				hsmp->ackReset(); // reset screen
#endif
		  ReadPath(mouse_queue);
		  mouse_direction = mouse_queue->mouse_dir;
		  MoveAction( mouse_queue, mouse_direction);

	  }

    printf("log Journey has been finished!\n");

    // Deallocate MazeBlocks and Stack
	ResetResources();
	bufs.delete_Queue (&mouse_queue);

  return true;
}

bool BabyMouse::StartToGoal( uint8_t startDir) {

	mouse_x = START_X;
	mouse_y = START_Y;
	mouse_direction = startDir;

    while (1) {

  		int result = HowToGo ( &mouse_x, &mouse_y, &mouse_direction, false );
        if( result == -1 ) return false;
        if( result == 1 ) break;

        if( CheckBoundary( ) == false) return false;
    }
	turnBack();

    goal_x = mouse_x;
    goal_y = mouse_y;

    mouse_direction = dir_info[mouse_direction].opposite;

	StartToGoalReflooding(START_X, START_Y);

    return true;
}

bool BabyMouse::GoalToStart( uint8_t startDir) {

	mouse_direction = startDir;

    while (1) {

        int result = HowToGo ( &mouse_x, &mouse_y, &mouse_direction , true);
        if( result == -1 ) return false;
        if( result == 1 ) break;

        if( CheckBoundary( ) == false) return false;
    }
	turnBack();

    mouse_direction = dir_info[mouse_direction].opposite;

	OptimizePath(); // close the dead path

    GoalToStartReflooding(goal_x, goal_y );

    return true;
}

int  BabyMouse::HowToGo (  uint8_t * mx, uint8_t * my, uint8_t * mdir, bool direction ) {
	uint8_t lx, ly, dir;
	bool found_start = false, found_goal = false;
	uint8_t exit_dir;
	Node *this_node;

	runInfo this_runInfo;

	lx = *mx;
	ly = *my;
	dir = *mdir;

	this_node = mouse_maze->Block[lx][ly];

	if( !direction )
		check_goal_reached(this_node, &found_goal);
	else
		check_start_reached(this_node, &found_start);

	if( found_start|| found_goal ) {
		*mx = lx;
		*my = ly;
		this_node->visited = true;
		if( found_goal )  SetGoalWall(this_node, dir);
		return 1;
	}

#if SIMULATION == 1
	if( !this_node->visited ) { // No visited
		 if( hsmp != NULL ) hsmp->setColor(lx, ly, 'G');
	} else {
		 if( hSmp != NULL ) hSmp->setColor(lx, ly, 'Y');
	}
#endif

	if( !this_node->visited ) { // No visited
		update_sensors();
		//
		this_node->visited = true;

		SetWallCell (  this_node, dir, frontWall, leftWall , rightWall ) ;
	}

	exit_dir = GetNextDirection( this_node, dir, direction );

	int    dif = Diff_Angle(dir, exit_dir); // blocked
	if( dif == 3 ){
		turnBack();
		*mdir = exit_dir;
	} else {
		this_runInfo.distance = 1;
		this_runInfo.direction = exit_dir;
		bufs.put(mouse_queue, this_runInfo); // Visited path Exit -> push

		(*mdir) = MoveAction(mouse_queue, dir);

		if (exit_dir == NORTH) ly ++;
		else if (exit_dir == EAST) lx ++;
			 else if (exit_dir == SOUTH) ly --;
			 	  else if (exit_dir == WEST) lx --;
	}

	*mx   = lx;
	*my   = ly;

	return 0;
}


uint8_t BabyMouse::MoveAction(Queue * this_queue, uint8_t startDir ) {
	Queue *temp_queue;
	  uint8_t dir, exit_dir;
	  runInfo this_runInfo;

  temp_queue = this_queue;

  dir = startDir;
  while (!bufs.is_empty_Queue(temp_queue)) {
	  bufs.get(temp_queue, &this_runInfo);
#if DEBUG_LOG == 1
		  PathDisplay(this_runInfo.direction, this_runInfo.distance, mouse_x, mouse_y, true);
#endif
	  exit_dir = this_runInfo.direction;

	  switch( Diff_Angle(dir, exit_dir) ) {
		  case 0: dir = exit_dir;
			  break;
		  case 3:
			  turnBack();
			  dir = dir_info[dir].opposite;
			  break;
		  case -1:
			  break;
		  case +1:
			  break;
		  case -2:
			  dir = dir_info[dir].left90;
			  turnLeft90();
			  break;
		  case +2:
			  dir = dir_info[dir].right90;
			  turnRight90();
		  default:
			  break;
	 }
	 moveFullForward(this_runInfo.distance);
  }

  return dir;
}

int BabyMouse::Buildshortcut( Queue * this_queue, uint8_t *px, uint8_t *py, uint8_t lx, uint8_t ly, uint8_t dir, bool state) {
	Node * this_node;
	uint8_t cur_dir, exit_dir;
	uint8_t mx, my;
	runInfo this_runInfo;
	bool exit;

	cur_dir = dir;
	mx = lx;
	my = ly;
	exit = false;

	while ( 1 ) {

		this_node = mouse_maze->Block[mx][my];

		if(state == false ) // exit condition
		  exit =  ( this_node->visited == false ) || ( mx == START_X && my == START_Y );
		else
		  check_goal_reached(this_node, &exit);

#if SIMULATION == 1
		if(state == true ) if( hSmp != NULL ) hSmp->setColor(mx, my, 'c');
#endif

		if( exit ) break;

#if SIMULATION == 1
		if(state == false ) if( hSmp != NULL ) hSmp->setColor(mx, my, 'Y');
#endif

		exit_dir =  fdf.get_smallest_neighbor_dir(this_node, cur_dir);

		if(state == false )
		  this_runInfo.direction=cur_dir;
		else
		  this_runInfo.direction=exit_dir;

		this_runInfo.distance = 1 ;
		Bufs.put(this_queue, this_runInfo); // move 1 step

		// update the appropriate location value x or y
		if (exit_dir == NORTH) my = my + 1;
		else if (exit_dir == EAST) mx = mx + 1;
			 else if (exit_dir == SOUTH) my = my - 1;
			 	  else if (exit_dir == WEST) mx = mx - 1;
		// update the direction
		cur_dir = exit_dir;
	}

	*px = mx;
	*py = my;

	return 0;
}

uint8_t BabyMouse::GetNextDirection(  Node *this_node, uint8_t mdir, bool direction ) {

  uint8_t   exit_dir = NORTH;

    if(this_node->pathCount > 1 ){ // exit > 1
    	Reflooding( this_node, direction );
    	exit_dir = fdf.get_smallest_neighbor_dir(this_node, mdir);
    } else {

    	if ( this_node->neighbours[mdir] != NULL ) exit_dir = mdir;
    	else if ( this_node->neighbours[dir_info[mdir].right90]  != NULL )  exit_dir = dir_info[mdir].right90  ;
    			else if ( this_node->neighbours[dir_info[mdir].left90]  != NULL )  exit_dir = dir_info[mdir].left90  ;
    				 else if ( this_node->neighbours[mdir] != NULL ) exit_dir = mdir;
    				 	  else exit_dir = dir_info[mdir].opposite;

    }
	return exit_dir;
}
