/*
 * BabyMouse.h
 *
 *  Created on: Feb 10, 2024
 *      Author: David(Yong eel) Lee
*/

#ifndef BABYMOUSE_H_
#define BABYMOUSE_H_

#include <CMice.h>

class BabyMouse:public CMice {
public:
	BabyMouse( Simulation *simp );
	virtual ~BabyMouse();

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

#endif /* BABYMOUSE_H_ */
