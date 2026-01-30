/*
 * YoungMouse.h
 *
 *  Created on: Feb 10, 2024
 *      Author: David(Yong eel) Lee
*/

#ifndef YOUNGMOUSE_H_
#define YOUNGMOUSE_H_

#include <CMice.h>

class YoungMouse: public CMice  {
public:
	YoungMouse( Simulation *simp );
	virtual ~YoungMouse();

	  bool    WalkToGoal ( );
	  bool    RunToGoal  ( );

	  bool    FindGoal ( bool mode );
	  bool    StartToGoal(uint8_t startDir);
	  bool    GoalToStart(uint8_t startDir);

	  int     HowToGo (  uint8_t * mx, uint8_t * my, uint8_t * mdir, bool direction ); // thiking
	  uint8_t MoveAction(Queue * this_queue, uint8_t startDir); // moving

	  int     Buildshortcut( Queue * this_queue, uint8_t *px, uint8_t *py, uint8_t lx, uint8_t ly, uint8_t dir, bool state) ;
	  uint8_t GetNextDirection( Node *this_node, uint8_t mdir, bool direction );
};

#endif /* YOUNGMOUSE_H_ */
