/*
 * NewMouse.h
 *
 *  Created on: Nov 4, 2025
 *      Author: David(Yong eel) Lee
*/

#ifndef YOUNGADULTMOUSE_H_
#define YOUNGADULTMOUSE_H_

#include <CMice.h>

class YoungAdultMouse: public CMice {
public:
	YoungAdultMouse(Simulation *simp);
	virtual ~YoungAdultMouse();

	  bool  turnState = false;
	  bool  crossState = false;
	  bool  touch_goal = false;

      uint8_t  cr_x = 0, cr_y = 0;
      uint8_t  bcnt = 0;

      char color[12] = {'b','a','o','g','c', 'r','w','B','A','C','R','Y'};
      /*
      k	Black
      b	Blue
      a	Gray
      c	Cyan
      g	Green
      o	Orange
      r	Red
      w	White
      y	Yellow
      B	Dark Blue
      C	Dark Cyan
      A	Dark Gray
      G	Dark Green
      R	Dark Red
      Y	Dark Yellow
	  */

#if SIMULATION == 1
	   int      length_frontwall();
	   void     update_sensors();
#endif

		bool    WalkToGoal ( );
		bool    RunToGoal  ( );
		bool    FindGoal ( bool mode );
		bool    StartToGoal(uint8_t startDir);
		bool    GoalToStart(uint8_t startDir);

		int     HowToGo(  uint8_t * mx, uint8_t * my, uint8_t * mdir, bool direction ); // thiking
		uint8_t MoveAction   (Queue * this_queue, uint8_t startDir); // moving
		uint8_t MoveActionSub(uint8_t distance, uint8_t curDir, uint8_t nextDir); // moving sub

		int     Buildshortcut( Queue * this_queue, uint8_t *px, uint8_t *py, uint8_t lx, uint8_t ly, uint8_t dir, bool state, bool way) ;

		void    SetMousePosition ( uint8_t *mx, uint8_t *my, uint8_t *mdir, uint8_t cx, uint8_t cy, unsigned char cdir);
		void    SetEnterExit     ( Node *this_node, uint8_t enterdir, uint8_t exitdir);
		void    SetEnterDirection( Node *this_node, uint8_t enterdir);
		void    SetExitDirection ( Node *this_node, uint8_t exitdir);
		void    TurnSetting      ( Node *this_node, uint8_t * mx, uint8_t * my, uint8_t * mdir, uint8_t entry_dir );

};

#endif /* OLDMOUSE_H_ */
