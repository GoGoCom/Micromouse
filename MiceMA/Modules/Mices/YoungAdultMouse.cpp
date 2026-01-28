/*
 * YoungAdultMouse.cpp
 *
 *  Created on: Nov 4, 2025
 *      Author: David(Yong eel) Lee
*/


#include <Mouse.h>
#include <BrainConfig.h>
#include <BodyConfig.h>

#include <YoungAdultMouse.h>

#include <CDriveSensors.h>

#include <Buffers.h>
#include <Floodfill.h>
#include <Simulation.h>


//extern Direction dir_info[12] ;

YoungAdultMouse::YoungAdultMouse(Simulation *simp )
{
	// TODO Auto-generated constructor stub
	miceInit(simp);

}

YoungAdultMouse::~YoungAdultMouse() {
	// TODO Auto-generated destructor stub
}


//#define DEBUG_LOG  1

#if SIMULATION == 1
int YoungAdultMouse::length_frontwall() {
	int length = 0;

	// find length from current to far front wall
	if( hsmp != NULL ) {
		  while( !hsmp->FrontWallFront(2 + length ) ) {
			  length ++;
		  }
	  }

   return length;
}

void YoungAdultMouse::update_sensors(void) {

  if( hsmp != NULL ) { // reading the existence of walls in each direction, according to wall data  in simulation, walls will be checked by simulator
	  frontWall = hsmp->FrontWallFront(2);
	  leftWall  = hsmp->FrontWallLeft(1);
	  rightWall = hsmp->FrontWallRight(1);
  }

}

#endif

bool  YoungAdultMouse::WalkToGoal ( ){
	return FindGoal( false );
}

bool  YoungAdultMouse::RunToGoal  ( ){
	return FindGoal( true );
}

bool YoungAdultMouse::FindGoal ( bool mode ) {


	// allocating maze solving resources
	mouse_queue = bufs.new_Queue();  // Initialize new stack
	visit_queue = bufs.new_Queue();

	SetResources();
	readyToGo();

	  if( mode == false ) { // false - from searching, true - optimized path

		// TRIP FROM START TO GOAL
		printf("log YoungAdult mouse goes to Goal position\n");
		if( StartToGoal( NORTH ) == true ) {
			printf("log go to Start position\n");
			if(GoalToStart( mouse_direction ) ==  true ) {
				printf("log go to Goal position directly\n");

				moveHalfForward(1); // move to half step

				uint8_t lx = START_X;
				uint8_t ly = START_Y;
				uint8_t startDir = NORTH;

				Buildshortcut( mouse_queue, &lx, &ly, lx, ly, startDir, true, true);
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

bool YoungAdultMouse::StartToGoal( uint8_t startDir) {

	mouse_x = START_X;
	mouse_y = START_Y; // to North
	mouse_direction = startDir;

	SetWallCell ( mouse_maze->Block[mouse_x][mouse_y], mouse_direction,  0, 1 , 1 ) ; // Start Cell
	mouse_maze->Block[mouse_x][mouse_y]->visited = true;

#if SIMULATION == 1
	if( hsmp != NULL )
		  hsmp->setColor(mouse_x, mouse_y, 'G');
#endif

	touch_goal = false;

    while (1) {

		int result = HowToGo ( &mouse_x, &mouse_y, &mouse_direction , false);
		if( result == -1 ) return false;
		if( result == 1 ) break;

		if( CheckBoundary( ) == false) return false;

    }

	StartToGoalReflooding(START_X, START_Y);

    return true;
}

bool YoungAdultMouse::GoalToStart( uint8_t startDir) {

	mouse_direction = startDir;

    // TRIP FROM GOAL TO START
    while (1) {

        int result = HowToGo ( &mouse_x, &mouse_y, &mouse_direction,  true);
        if( result == -1 ) return false;
        if( result == 1 ) break;

        if( CheckBoundary( ) == false) return false;
    }

	OptimizePath(); // close the dead path

    GoalToStartReflooding(goal_x, goal_y );
    print_map(); // for debug test

    return true;
}


int  YoungAdultMouse::HowToGo (  uint8_t * mx, uint8_t * my, uint8_t * mdir, bool direction ) {

	Node *forward_node;
	bool found_start = false, found_goal = false;
	uint8_t entry_dir, cur_dir, exit_dir;       /* will hold the next direction to go */



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

//		 if( found_start|| found_goal ) {
		 if( found_start ) {

			moveHalfForward(1);
		    TurnSetting( this_node, mx, my, mdir, entry_dir );

			return 1;
		 }

         if( this_node->visited == false ) { // No visited

			update_sensors();

			SetWallCell ( this_node, cur_dir, frontWall, leftWall , rightWall ) ;

			if( this_node->pathCount == 0 ){ // blocked

#if SIMULATION == 1
				if( hsmp != NULL ) hsmp->setColor(this_node->x, this_node->y, 'Y');
#endif

				turnState = true;
				crossState = false;

			    TurnSetting( this_node, mx, my, mdir, entry_dir );

				//printf("log no path  %2d, %2d [%s]- %s, %s\n", this_node->x, this_node->y, dir_ch[cur_dir], dir_ch[this_node->enteredDir], dir_ch[this_node->exitedDir] );

				return 0;
			}

			exit_dir = GetNextDirection( this_node, cur_dir, direction );
			exit_dir = MoveActionSub(1, cur_dir, exit_dir );

			SetEnterDirection( this_node, entry_dir) ;
			SetExitDirection( this_node->neighbours[this_node->enteredDir], cur_dir);
		    SetMousePosition( mx, my, mdir, this_node->x, this_node->y, exit_dir );

			//  printf("log forward  %2d, %2d [%s]- %s, %s\n", this_node->x, this_node->y, dir_ch[cur_dir], dir_ch[this_node->enteredDir], dir_ch[this_node->exitedDir] );

			if(this_node->pathCount > 1 ) {
				crossState = true;
				cr_x=this_node->x;
				cr_y=this_node->y;
			}


#if SIMULATION == 1
			if( ( hsmp != NULL ) && (this_node->visited ) ) hsmp->setColor(this_node->x, this_node->y, 'G');
#endif

         } else { // visited

		 	 // Stop and thinking


 		    if( ( !direction ) && (check_goal_reached(this_node, &found_goal)) ) {

 		    	goal_x = this_node->x;
				goal_y = this_node->y;

		         if( this_node->neighbours[entry_dir] == NULL ) {
		        	 printf("log Blocked found a goal %d, %d, %d\n",this_node->x,this_node->y, entry_dir );
		        	 return -1; // blocked!
		         }
 				SetMousePosition( mx, my, mdir, this_node->neighbours[entry_dir]->x, this_node->neighbours[entry_dir]->y, cur_dir );

 				touch_goal = true;

 				return 1;
 		    }

			 if(  direction== false && this_node->x == START_X && this_node->y == START_Y   ) { // turn back to goal

			    TurnSetting( this_node, mx, my, mdir, entry_dir );

				return 0;
			 }

	    	 if( (touch_goal == false) && (turnState == false) && (crossState == true ) ) {

	#if SIMULATION == 1
					if( hsmp != NULL ) hsmp->setColor(this_node->x, this_node->y, 'Y');
	#endif
					if( (cr_x!=this_node->x) || (cr_y!=this_node->y) ) {
					    TurnSetting( this_node, mx, my, mdir, entry_dir );

						crossState = false;
						return 0;
					}

	    	 }

	    	  // stop thinking

	 		if( direction == true ) Reflooding( this_node, direction ); // already visited before flooding -> only once ok!

			 if(Buildshortcut( mouse_queue, mx, my, this_node->x, this_node->y, cur_dir, false, direction) == -1 ) {
				printf("log build error %d, %d, %d, %d\n", this_node->x, this_node->y,this_node->enteredDir, this_node->exitedDir );
				return -1; // false
			 }
			 bcnt ++;
			 if( bcnt == 11 ) bcnt =0;

			 (*mdir) = MoveAction(mouse_queue, cur_dir); // true - 45, false 90 - go to 3 direction
			 if( dir_info[*mdir].type == 8 ) {
				printf("log angle error %d, %d,(%d), %d, %d\n", this_node->x, this_node->y,*mdir, this_node->enteredDir, this_node->exitedDir );
				return -1; // false
			 }
			 return 0;
		}

	return 0;
}

void YoungAdultMouse::TurnSetting(   Node *this_node, uint8_t * mx, uint8_t * my, uint8_t * mdir, uint8_t entry_dir ) {

	smoothTurnBack();
    SetEnterExit( this_node, entry_dir, entry_dir);

    SetMousePosition( mx, my, mdir, this_node->x, this_node->y, this_node->exitedDir);
}

uint8_t YoungAdultMouse::MoveAction(Queue * this_queue, uint8_t startDir ) {
	  Queue *temp_queue;
	  uint8_t dir, exit_dir, sw;       /* will hold the next direction to go */
	  runInfo this_runInfo, visit_runInfo;  /* used for in-between start->goal, goal->start transition */

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
	  dir=MoveActionSub(this_runInfo.distance, dir, exit_dir );
      delay(1);
    }

  return dir;
}

uint8_t YoungAdultMouse::MoveActionSub(uint8_t distance, uint8_t curDir, uint8_t nextDir ) {

	uint8_t dir = curDir, exit_dir = nextDir;

	  if(dir_info[exit_dir].type == DIR8) {
			  if( distance == 1 ) {
				  switch( Diff_Angle(dir, exit_dir) ) { // never happend ?
				  	  case -2: dir = dir_info[dir].left45;
				  	  printf("log D1 doubt tl45 rl90\n");
						  turnLeft45();
					  case -1: dir = dir_info[dir].left90;
					  	  smoothLeft90();
						  break;
					  case +2: dir = dir_info[dir].right45;
				  	  printf("log D1 doubt tr45 rr90\n");
						  turnRight45();
					  case +1: dir = dir_info[dir].right90;
						  smoothRight90();
					   default:
						  break;
				  }
			  }
			  if( distance == 2 ) {
				  switch( Diff_Angle(dir, exit_dir) ) {
					  case -1:
						  smoothLeft90();
						  smoothRight90();
						  break;
				  	  case -2: dir = dir_info[dir].left45; // when ?
				  	  printf("log D2 doubt tl45 rl90 rr90\n");
				  	  	  smoothLeft90();
				  	  	  smoothRight90();
						  break;
					  case +1:
						  smoothRight90();
						  smoothLeft90();
						  break;
					  case +2: dir = dir_info[dir].right45;
				  	  printf("log D2 doubt tr45 rr90 rl90\n");
				  	  	  smoothRight90();
				  	  	  smoothLeft90();
						  break;
					  default:
						  break;
				  }

			  }
			  if( distance > 2 ) {
				  int status = Diff_Angle(dir, exit_dir);
				  switch( status ) {
					  case -2: dir = dir_info[dir].left90; // never happend ?
				  	  printf("log D3 doubt tl90 \n");
						  turnLeft90();
						  break;
					  case -1:
						  if( distance % 2 ) {
							  mouse_pose = +45;
						  } else {
							  mouse_pose = -45;
						  }
						  dir = dir_info[dir].left45;
						  turnLeft45();
						  break;
					  case +2: dir = dir_info[dir].right90;
				  	  printf("log D3 doubt tr90 \n");
							  turnRight90();
						  break;
					  case +1:
						  if( distance % 2 ) {
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

				moveEdgeForward(distance);

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
			  	  	  smoothFullForward(distance);
					  break;
				  case 3:
					  smoothTurnBack();
					  if(distance > 1 ) smoothFullForward(distance);
					  dir = dir_info[dir].opposite;
					  break;
				  case -1:dir = dir_info[dir].left45;
					  turnLeft45();
					  smoothFullForward(distance);
					  break;
				  case +1:dir = dir_info[dir].right45;
					  turnRight45();
					  smoothFullForward(distance);
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

  return dir;
}

int YoungAdultMouse::Buildshortcut( Queue * this_queue, uint8_t *px, uint8_t *py, uint8_t lx, uint8_t ly, uint8_t dir, bool state, bool direction) {
  Node * this_node, *temp_node;   /* the node at this position x, y */
  uint8_t entry_dir, cur_dir, exit_dir;       /* will hold the next direction to go */
  uint8_t mx, my;

  runInfo this_runInfo;  /* used for in-between start->goal, goal->start transition */
  bool exit, exit1;

    cur_dir = dir;
    mx = lx;
    my = ly;
    exit = false;
    exit1 = false;

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

		if( (!direction) && (exit1)) {

			  while (!bufs.is_empty_Queue(this_queue)) {
				  bufs.get(this_queue, &this_runInfo);
			    }

		    cur_dir = dir;
		    mx = lx;
		    my = ly;
		    exit1 = false;

			printf("log noexit  %2d, %2d [%s]- %s, %s\n", this_node->x, this_node->y, dir_ch[cur_dir], dir_ch[this_node->enteredDir], dir_ch[this_node->exitedDir] );
			continue;

		}

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
		if(state == false ) if( hSmp != NULL ) hSmp->setColor(mx, my, color[bcnt]);
#endif

		if(direction == false) // search fastway
			exit_dir =  GetNextDirection(this_node, cur_dir, direction);
		else // floodfill
			exit_dir = fdf.get_smallest_neighbor_dir(this_node, cur_dir);

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

		if(state == false) {// search fastway
		  if( turnState ) {
			  if( this_node->pathCount > 1 ) {
				this_node->neighbours[entry_dir] = NULL;
				this_node->pathCount --;
				turnState = false;
			  }
		  }
		  SetEnterExit( this_node, entry_dir, exit_dir);
		}

//		  printf("log backward %2d, %2d [%s]- %s, %s\n", this_node->x, this_node->y, dir_ch[cur_dir], dir_ch[this_node->enteredDir], dir_ch[this_node->exitedDir] );

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

void YoungAdultMouse::SetMousePosition( uint8_t *mx, uint8_t *my, uint8_t *mdir, uint8_t cx, uint8_t cy, unsigned char cdir){
	*mx   = cx;
	*my   = cy;
	*mdir = cdir;
}

void YoungAdultMouse::SetEnterExit( Node *this_node, uint8_t enterdir, uint8_t exitdir) {
	SetEnterDirection( this_node, enterdir) ;
	SetExitDirection(  this_node, exitdir ) ;
}

void YoungAdultMouse::SetEnterDirection( Node *this_node, uint8_t enterdir) {

	this_node->visited = true;
	this_node->enteredDir = enterdir;
	this_node->passCount[this_node->enteredDir] ++;

}

void YoungAdultMouse::SetExitDirection( Node *this_node, uint8_t exitdir) {

	this_node->exitedDir  = exitdir;
	this_node->passCount[this_node->exitedDir] ++;

}
