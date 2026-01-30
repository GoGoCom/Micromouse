/*
 * YoungMouse.cpp
 *
 *  Created on: Feb 10, 2024
 *      Author: David(Yong eel) Lee
*/

#include <Mice.h>
#include <BrainConfig.h>
#include <BodyConfig.h>

#include <YoungMouse.h>

#include <CDriveSensors.h>

#include <Buffers.h>
#include <Floodfill.h>
#include <Simulation.h>


//extern Direction dir_info[12] ;

//#define DEBUG_LOG  1

YoungMouse::YoungMouse( Simulation *simp )
{
	// TODO Auto-generated constructor stub
	miceInit(simp);

}

YoungMouse::~YoungMouse() {
	// TODO Auto-generated destructor stub
}

bool  YoungMouse::WalkToGoal ( ){
	return FindGoal( false );
}

bool  YoungMouse::RunToGoal  ( ){
	return FindGoal( true );
}

bool YoungMouse::FindGoal ( bool mode ) {

	// allocating maze solving resources
	mouse_queue = bufs.new_Queue();  // Initialize new stack
	visit_queue = bufs.new_Queue();

	SetResources();

	  if( mode == false ) { // false - from searching, true - optimized path

		// TRIP FROM START TO GOAL
		printf("log Young mouse goes to Goal position\n");
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
		  if( hsmp != NULL ) hsmp->ackReset(); // reset screen
#endif
		  ReadPath(mouse_queue);
		  mouse_direction = mouse_queue->mouse_dir;
		  MoveAction( mouse_queue, mouse_direction);

	  }

    printf("log Journey has been finished!\n");

    // Deallocate MazeBlocks and Stack
	ResetResources();
	bufs.delete_Queue (&mouse_queue);
    bufs.delete_Queue (&visit_queue);

  return true;
}

bool YoungMouse::StartToGoal( uint8_t startDir) {

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

bool YoungMouse::GoalToStart( uint8_t startDir) {

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

    GoalToStartReflooding(goal_x, goal_y);

    return true;
}


int  YoungMouse::HowToGo (  uint8_t * mx, uint8_t * my, uint8_t * mdir, bool direction ) {
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
    if( !this_node->visited) { // No visited
		update_sensors();

		SetWallCell ( this_node, dir,  frontWall, leftWall , rightWall ) ;
    }
	exit_dir = GetNextDirection( this_node, dir, direction );
	int  dif = Diff_Angle(dir, exit_dir); // blocked

	if( dif == 3 ){
#if SIMULATION == 1
		if( hsmp != NULL ) hsmp->setColor(lx, ly, 'Y');
#endif
		this_node->visited = true;
		turnBack();
		*mdir = exit_dir;
	} else {

		if( !this_node->visited  )  {

			if (exit_dir == NORTH) 	ly ++;
			else if (exit_dir == EAST) lx ++;
				 else if (exit_dir == SOUTH) ly --;
					  else if (exit_dir == WEST) lx --;

#if SIMULATION == 1
			 if ( hsmp != NULL )  hsmp->setColor(*mx, *my, 'G');
#endif
			this_runInfo.distance = 2;
			this_runInfo.direction = exit_dir;
			bufs.put(mouse_queue, this_runInfo); // Visited path Exit -> push

			*mx   = lx;
			*my   = ly;

		} else {
			lx = *mx;
			ly = *my;
			Buildshortcut( mouse_queue, mx, my, lx, ly, dir, false);
		}

		(*mdir) = MoveAction(mouse_queue, dir); // true - 45, false 90 - go to 3 direction

		this_node->visited = true;
	}

	return 0;
}


uint8_t YoungMouse::MoveAction(Queue * this_queue, uint8_t startDir ) {
	  Queue *temp_queue;
	  uint8_t dir, exit_dir, sw;
	  runInfo this_runInfo, visit_runInfo;

// Now make faster run

	  dir = startDir;
	  sw = 0;
	  while (!bufs.is_empty_Queue(this_queue)) {
		  bufs.get(this_queue, &this_runInfo);
#if DEBUG_LOG == 1
		  PathDisplay(this_runInfo.direction, this_runInfo.distance, mouse_x, mouse_y, false);
#endif
		  exit_dir = this_runInfo.direction;
		  if( sw == 0 ) {
			  visit_runInfo.distance = this_runInfo.distance  ;
			  visit_runInfo.direction = this_runInfo.direction;
			  sw = 1;
		  } else {

			  if( this_runInfo.distance == 1 ) { // make a diagonal
				  if(dir_info[exit_dir].type == 8 ) {
					  if(  dir_info[dir].angle - dir_info[exit_dir].angle == 0 ) {
						  visit_runInfo.distance ++;
	#if DEBUG_LOG == 1
						  PathDisplay(this_runInfo.direction, this_runInfo.distance, mouse_x, mouse_y, false);
	#endif
					  }
					  else sw = 2;
				  }
				  else sw = 2;
			  }
			  else sw = 2;

		  }
		  if( sw == 2 ) {
			  bufs.put(visit_queue, visit_runInfo);
			  visit_runInfo.distance  = this_runInfo.distance  ;
			  visit_runInfo.direction = this_runInfo.direction;
			  sw = 1;
		  }

		/* update the direction */
		  dir = exit_dir;
	  }
	  bufs.put(visit_queue, visit_runInfo);  // last info

	  // run
  temp_queue = visit_queue;

  sw = 0;
  dir = startDir;
  while (!bufs.is_empty_Queue(temp_queue)) {
	  bufs.get(temp_queue, &this_runInfo);
#if DEBUG_LOG == 1
	  PathDisplay(this_runInfo.direction, this_runInfo.distance, mouse_x, mouse_y, true);
#endif
	  exit_dir = this_runInfo.direction;

	  if(dir_info[exit_dir].type == 8 ) { // type 8 - 8 directions
		  if( this_runInfo.distance == 1 ) {
			  switch( Diff_Angle(dir, exit_dir) ) {
				  case -2: dir = dir_info[dir].left45;
						  turnLeft45();
				  case -1: dir = dir_info[dir].left90;
						  turnLeft45();
						  moveHalfForward(this_runInfo.distance);
						  turnLeft45();
						  break;
				  case +2: dir = dir_info[dir].right45;
						  turnRight45();
				  case +1: dir = dir_info[dir].right90;
						  turnRight45();
						  moveHalfForward(this_runInfo.distance);
						  turnRight45();
				   default:
					  break;
			  }
		  }
		  if( this_runInfo.distance == 2 ) {
			  switch( Diff_Angle(dir, exit_dir) ) {
				  case -1:
						  turnLeft45();
						  moveHalfForward(this_runInfo.distance);
						  turnRight45();
						  break;
				  case -2: dir = dir_info[dir].left45;
						  turnLeft90();
						  moveHalfForward(this_runInfo.distance);
						  turnRight45();
						  break;
				  case +1:
						  turnRight45();
						  moveHalfForward(this_runInfo.distance);
						  turnLeft45();
						  break;
				  case +2: dir = dir_info[dir].right45;
						  turnRight90();
						  moveHalfForward(this_runInfo.distance);
						  turnLeft45();
						  break;
				  default:
					  break;
			  }

		  }
		  if( this_runInfo.distance > 2 ) {
			  switch( Diff_Angle(dir, exit_dir) ) {
				  case -2: dir = dir_info[dir].left90;
						  turnLeft90();
						  break;
				  case -1:dir = dir_info[dir].left45;
						  turnLeft45();
						  break;
				  case +2: dir = dir_info[dir].right90;
						  turnRight90();
						  break;
				  case +1:dir = dir_info[dir].right45;
						  turnRight45();
						  break;
				  default:
					  break;
			  }
			  moveEdgeForward(this_runInfo.distance);
		  }
	  }
	  else {	  // type 4 - 4 directions
		  switch( Diff_Angle(dir, exit_dir) ) {
			  case 0: dir = exit_dir;
				  break;
			  case 3:
				  turnBack();
				  dir = dir_info[dir].opposite;
				  break;
			  case -1:dir = dir_info[dir].left45;
				  turnLeft45();
				  break;
			  case +1:dir = dir_info[dir].right45;
				  turnRight45();
				  break;
			  case -2:dir = dir_info[dir].left90;
				  turnLeft90();
				  break;
			  case +2:dir = dir_info[dir].right90;
				  turnRight90();
			  default:
				  break;
		 }
		 moveHalfForward(this_runInfo.distance);
	  }
    }

  return dir;
}

int YoungMouse::Buildshortcut( Queue * this_queue, uint8_t *px, uint8_t *py, uint8_t lx, uint8_t ly, uint8_t dir, bool state) {
	  Node * this_node, *temp_node;
	  uint8_t cur_dir, exit_dir;
	  uint8_t mx, my, sw;
	  runInfo this_runInfo;
	  bool exit;

		sw = 0;
	    cur_dir = dir;
	    mx = lx;
	    my = ly;
	    exit = false;

	    temp_node = mouse_maze->Block[(*px)][(*py)];

		while ( 1 ) {

			this_node = mouse_maze->Block[mx][my];

			if(state == false ) // exit condition
			  exit =  ( this_node->visited == false ) || ( mx == START_X && my == START_Y );
			else
			  check_goal_reached(this_node, &exit);


#if SIMULATION == 1
			if(state == true ) if( hSmp != NULL )hSmp->setColor(mx, my, 'c');
#endif

			if( exit ) {

			  this_runInfo.distance = abs(temp_node->x - this_node->x) + abs(temp_node->y - this_node->y) ;

			  if( sw == 1 )
				  this_runInfo.distance = this_runInfo.distance * 2 - 1;  // last step
			  else
				  this_runInfo.distance = this_runInfo.distance * 2;

			  this_runInfo.direction = cur_dir;
			  Bufs.put(this_queue, this_runInfo); // Visited path Exit -> push

			  break;
			}

#if SIMULATION == 1
			if(state == false ) if( hSmp != NULL ) hSmp->setColor(mx, my, 'Y');
#endif

			exit_dir =  fdf.get_smallest_neighbor_dir(this_node, cur_dir);

			if( cur_dir != exit_dir ) {
				  this_runInfo.distance = abs(temp_node->x - this_node->x) + abs(temp_node->y - this_node->y) ;
				  if( this_runInfo.distance != 0 ) { // execept itself
					  if(this_runInfo.distance > 1) {
						  if( sw == 0 ) {
							  this_runInfo.distance = this_runInfo.distance * 2 - 1; // move 1 step
						  } else {
							  this_runInfo.distance = this_runInfo.distance * 2 - 2;
						  }
						  this_runInfo.direction = cur_dir;
						  Bufs.put(this_queue, this_runInfo); // change -> push
						  this_runInfo.direction=EdgeRunDirection( cur_dir, exit_dir);
						  this_runInfo.distance = 1;
						  Bufs.put(this_queue, this_runInfo); // change -> push
					  }
					  else if(this_runInfo.distance == 1) {
							  if( sw == 0 ) {
								  this_runInfo.direction=cur_dir;
								  Bufs.put(this_queue, this_runInfo); // move 1 step
							  }
							  this_runInfo.direction=EdgeRunDirection( cur_dir, exit_dir);
							  Bufs.put(this_queue, this_runInfo); // change -> push
						   }
					  sw = 1;
				  }
			      temp_node = this_node ; // next
			}

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

uint8_t  YoungMouse::GetNextDirection( Node *this_node, uint8_t mdir, bool direction ) {

  uint8_t   exit_dir;

    if(this_node->visited  || this_node->pathCount > 1 ){ // visited
    	Reflooding( this_node, direction );
    	exit_dir = fdf.get_smallest_neighbor_dir(this_node, mdir);
    } else {
    	exit_dir = GetNextDirectionSub( this_node, mdir, direction ) ;
    }

	return exit_dir;
}
