/*
 * AdultMouse.cpp
 *
 *  Created on: Feb 10, 2024
 *      Author: David(Yong eel) Lee
*/

#include <Mice.h>
#include <BrainConfig.h>
#include <BodyConfig.h>

#include <AdultMouse.h>

#include <CDriveSensors.h>

#include <Buffers.h>
#include <Floodfill.h>
#include <Simulation.h>


//extern Direction dir_info[12] ;

//#define DEBUG_LOG  1


#if SIMULATION == 1
void AdultMouse::update_sensors(void) {

	  if( hsmp != NULL ) { // reading the existence of walls in each direction, according to wall data  in simulation, walls will be checked by simulator
		  frontWall = hsmp->FrontWallFront(2);
		  leftWall  = hsmp->FrontWallLeft(1);
		  rightWall = hsmp->FrontWallRight(1);
	  }
}

#endif

AdultMouse::AdultMouse( Simulation *simp )
{
	// TODO Auto-generated constructor stub
	miceInit(simp);

}

AdultMouse::~AdultMouse() {
	// TODO Auto-generated destructor stub
}

bool  AdultMouse::WalkToGoal ( ){
	return FindGoal( false );
}

bool  AdultMouse::RunToGoal  ( ){
	return FindGoal( true );
}

bool AdultMouse::FindGoal ( bool mode ) {


	// allocating maze solving resources
	mouse_queue = bufs.new_Queue();  // Initialize new stack
	visit_queue = bufs.new_Queue();

	SetResources();
	readyToGo();

	  if( mode == false ) { // false - from searching, true - optimized path

		// TRIP FROM START TO GOAL
		printf("log Adult mouse goes to Goal position\n");
		if( StartToGoal( NORTH ) == true ) {
			printf("log go to Start position\n");
			if(GoalToStart( mouse_direction ) ==  true ) {
				printf("log go to Goal position directly\n");

				moveHalfForward(1); // move to half step

				uint8_t lx = START_X;
				uint8_t ly = START_Y;
				uint8_t startDir = NORTH;

				Buildshortcut( mouse_queue, &lx, &ly, lx, ly, startDir, true);
				mouse_queue->mouse_dir = startDir; // save last position
				WritePath(mouse_queue);
			    MoveAction(mouse_queue, startDir);

				moveHalfForward(1);
			}
		}

	  } else { // go to the goal directly without searching.

		  ReadPath(mouse_queue);

		  mouse_direction = mouse_queue->mouse_dir;
		  MoveAction( mouse_queue, mouse_direction );

		  moveHalfForward(1);
	  }

    printf("log Journey has been finished!\n");

    // Deallocate MazeBlocks and Stack
	ResetResources();
	bufs.delete_Queue (&mouse_queue);
    bufs.delete_Queue (&visit_queue);

  return true;
}

bool AdultMouse::StartToGoal( uint8_t startDir) {

	mouse_x = START_X;
	mouse_y = START_Y;
	mouse_direction = startDir;

	SetWallCell ( mouse_maze->Block[mouse_x][mouse_y], mouse_direction,  0, 1 , 1 ) ; // Start Cell
	mouse_maze->Block[mouse_x][mouse_y]->visited = true;

#if SIMULATION == 1
	if( hsmp != NULL ) hsmp->setColor(mouse_x, mouse_y, 'G');
#endif

    while (1) {

        int result = HowToGo ( &mouse_x, &mouse_y, &mouse_direction , false);
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

bool AdultMouse::GoalToStart( uint8_t startDir) {

	moveHalfForward(1);

	mouse_direction = startDir;

    // TRIP FROM GOAL TO START
    while (1) {

        int result = HowToGo ( &mouse_x, &mouse_y, &mouse_direction, true );
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


int  AdultMouse::HowToGo (  uint8_t * mx, uint8_t * my, uint8_t * mdir, bool direction ) {

	bool found_start = false, found_goal = false;
	uint8_t cur_dir, entry_dir, exit_dir;
	Node *forward_node;
	runInfo this_runInfo;

	cur_dir = *mdir; // current mouse direction
	entry_dir =  dir_info[cur_dir].opposite;

	// GetFrontCell
	 forward_node=mouse_maze->Block[*mx][*my]->neighbours[cur_dir];
	if( forward_node == NULL) {
	 printf("log Blocked to go %d, %d, %d\n",*mx,*my, cur_dir);
	 return -1; // blocked!
	}

	Node   *this_node =  mouse_maze->Block[forward_node->x][forward_node->y];   /* the node at this position x, y */

	 if( !direction )
		check_goal_reached(this_node, &found_goal);
	 else
		check_start_reached(this_node, &found_start);

   if( found_start|| found_goal ) {
		*mx = this_node->x;
		*my = this_node->y;
		this_node->visited = true;

		if( found_goal )  SetGoalWall(this_node, cur_dir);

		moveHalfForward(1);

		return 1;
	}

	if( !this_node->visited ) { // No visited

		update_sensors();

		SetWallCell ( this_node, cur_dir, frontWall, leftWall , rightWall ) ;

		if( this_node->pathCount == 0 ){ // blocked

#if SIMULATION == 1
			if( hsmp != NULL ) hsmp->setColor(this_node->x, this_node->y, 'Y');
#endif

			this_node->visited = true;

			smoothTurnBack();

			*mx   = this_node->x;
			*my   = this_node->y;
			*mdir = entry_dir ;

			return 0;
		}

		exit_dir = GetNextDirection( this_node, cur_dir, direction );
		this_runInfo.distance = 1;
		this_runInfo.direction = exit_dir;
		bufs.put(mouse_queue, this_runInfo); // Visited path Exit -> push

		(*mdir) = MoveAction(mouse_queue, cur_dir); // true - 45, false 90 - go to 3 direction

#if SIMULATION == 1
		if( ( hsmp != NULL ) && (!this_node->visited ) ) hsmp->setColor(this_node->x,this_node->y, 'G');
#endif

		this_node->visited = true;

		*mx = this_node->x;
		*my = this_node->y;

	}  else { // visited
		// stop and thinking

		Reflooding( this_node, direction ); // already visited before flooding -> only once ok!
		Buildshortcut( mouse_queue, mx, my, this_node->x, this_node->y, cur_dir, false); // false

		(*mdir) = MoveAction(mouse_queue, cur_dir); // true - 45, false 90 - go to 3 direction
	}

	return 0;
}


uint8_t AdultMouse::MoveAction(Queue * this_queue, uint8_t startDir ) {
	Queue *temp_queue;
	uint8_t dir, exit_dir, sw;
	runInfo this_runInfo, visit_runInfo;

// Now run faster
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

  temp_queue = visit_queue;

  sw = 0;
  dir = startDir;
  while (!bufs.is_empty_Queue(temp_queue)) {
	  bufs.get(temp_queue, &this_runInfo);
#if DEBUG_LOG == 1
	  PathDisplay(this_runInfo.direction, this_runInfo.distance, mouse_x, mouse_y, true);
#endif
	  exit_dir = this_runInfo.direction;
	  if(dir_info[exit_dir].type == 8) {
			  if( this_runInfo.distance == 1 ) {
				  switch( Diff_Angle(dir, exit_dir) ) { // never happend ?
				  	  case -2: dir = dir_info[dir].left45;
						  turnLeft45();
					  case -1: dir = dir_info[dir].left90;
					  	  smoothLeft90();
						  break;
					  case +2: dir = dir_info[dir].right45;
						  turnRight45();
					  case +1: dir = dir_info[dir].right90;
						  smoothRight90();
					   default:
						  break;
				  }
			  }
			  if( this_runInfo.distance == 2 ) {
				  switch( Diff_Angle(dir, exit_dir) ) {
					  case -1:
						  smoothLeft90();
						  smoothRight90();
						  break;
				  	  case -2: dir = dir_info[dir].left45; // when ?
						  smoothLeft90();
						  smoothRight90();
						  break;
					  case +1:
						  smoothRight90();
						  smoothLeft90();
						  break;
					  case +2: dir = dir_info[dir].right45;
						  smoothRight90();
						  smoothLeft90();
						  break;
					  default:
						  break;
				  }

			  }
			  if( this_runInfo.distance > 2 ) {
				  int status = Diff_Angle(dir, exit_dir);
				  switch( status ) {
					  case -2: dir = dir_info[dir].left90; // never happend ?
						  turnLeft90();
						  break;
					  case -1:
						  if( this_runInfo.distance % 2 ) {
							  mouse_pose = +45;
						  } else {
							  mouse_pose = -45;
						  }
						  dir = dir_info[dir].left45;
						  turnLeft45();
						  break;
					  case +2: dir = dir_info[dir].right90;
						  turnRight90();
						  break;
					  case +1:
						  if( this_runInfo.distance % 2 ) {
						  	  mouse_pose = -45;
						  } else {
 						  	  mouse_pose = +45;
						  }
						  dir = dir_info[dir].right45;
						  turnRight45();
						  break;
					  default:
						  break;
				  }

				moveEdgeForward(this_runInfo.distance);

				if ( mouse_pose == -45 ) {
					  turnRight45();
					  mouse_pose = 0 ;
					  dir = dir_info[dir].right45;
				}
				if ( mouse_pose == +45 ) {
					  turnLeft45();
					  mouse_pose = 0 ;
					  dir = dir_info[dir].left45;
				}
			  }
	  } else {
			  switch( Diff_Angle(dir, exit_dir) ) {
			  	  case 0: dir = exit_dir;
			  	  	  smoothFullForward(this_runInfo.distance);
						break;
				  case 3:
					  smoothTurnBack();
					  if(this_runInfo.distance > 1 ) smoothFullForward(this_runInfo.distance);
					  dir = dir_info[dir].opposite;
					  break;
				  case -1:dir = dir_info[dir].left45;
					  turnLeft45();
					  smoothFullForward(this_runInfo.distance);
					  break;
				  case +1:dir = dir_info[dir].right45;
					  turnRight45();
					  smoothFullForward(this_runInfo.distance);
					  break;
				  case -2:dir = dir_info[dir].left90;
					  smoothLeft90();
					  break;
				  case +2:dir = dir_info[dir].right90;
					  smoothRight90();
				  default:
					  break;
			}
	  }
      delay(1);
    }

  return dir;
}

int AdultMouse::Buildshortcut( Queue * this_queue, uint8_t *px, uint8_t *py, uint8_t lx, uint8_t ly, uint8_t dir, bool state) {
	Node * this_node, *temp_node;
	uint8_t entry_dir, cur_dir, exit_dir;
	uint8_t mx, my;

	runInfo this_runInfo;
	bool exit;

    cur_dir = dir;

    mx = lx;
    my = ly;
    exit = false;

    temp_node = mouse_maze->Block[(*px)][(*py)];

	while ( 1 ) {

	    entry_dir =  dir_info[cur_dir].opposite;

		this_node = mouse_maze->Block[mx][my];

		if(state == false ) // exit condition
		  exit =  ( this_node->visited == false ) || ( mx == START_X && my == START_Y );
		else
		  check_goal_reached(this_node, &exit);

#if SIMULATION == 1
		if(state == true ) if( hSmp != NULL ) hSmp->setColor(mx, my, 'c');
#endif

		if( exit ) {

			if( this_node->neighbours[entry_dir] == NULL ) {
			 printf("log Blocked exit %d, %d, %d\n",this_node->x,this_node->y, entry_dir );
			 return -1; // blocked!
			}

			*px =this_node->neighbours[entry_dir]->x;
			*py =this_node->neighbours[entry_dir]->y;

			this_runInfo.direction = cur_dir;
			this_runInfo.distance = abs(temp_node->x - this_node->x) + abs(temp_node->y - this_node->y) ;
			if( this_runInfo.distance > 1 ) {
			  this_runInfo.distance = this_runInfo.distance - 1 ; // - 1; not arrived to corner
			  Bufs.put(this_queue, this_runInfo); // Visited path Exit -> push
			}
			return 0;
		}

#if SIMULATION == 1
		if(state == false ) if( hSmp != NULL ) hSmp->setColor(mx, my, 'Y');
#endif

		exit_dir =  fdf.get_smallest_neighbor_dir(this_node, cur_dir);
		if( cur_dir != exit_dir ) {
			  this_runInfo.distance = abs(temp_node->x - this_node->x) + abs(temp_node->y - this_node->y) ;
			  if( this_runInfo.distance != 0 ) { // execept itself
					  if(this_runInfo.distance > 1) {
						  this_runInfo.direction = cur_dir;
						  this_runInfo.distance = this_runInfo.distance -1 ;
						  Bufs.put(this_queue, this_runInfo); // change -> push
						  this_runInfo.direction=EdgeRunDirection( cur_dir, exit_dir);
						  this_runInfo.distance = 1;
						  Bufs.put(this_queue, this_runInfo); // change -> push
					  }
					  else if(this_runInfo.distance == 1) {
							  this_runInfo.direction=EdgeRunDirection( cur_dir, exit_dir);
							  Bufs.put(this_queue, this_runInfo); // change -> push
						   }
			  }
		      temp_node = this_node ; // next
		}

		if( this_node->neighbours[exit_dir] == NULL ) {
		 printf("log Blocked back %d, %d, %d\n",this_node->x,this_node->y, exit_dir );
		 return -1; // blocked!
		}

		mx =this_node->neighbours[exit_dir]->x;
		my =this_node->neighbours[exit_dir]->y;
		// update the direction
		cur_dir =exit_dir;

	}

	*px = mx;
	*py = my;

	return 0;
}

