/*
 * OldMouse.h
 *
 *  Created on: Nov 4, 2025
 *      Author: David(Yong eel) Lee
*/

#ifndef OLDMOUSE_H_
#define OLDMOUSE_H_

#include <CMice.h>

class OldMouse: public CMice {
public:
	OldMouse(Simulation *simp);
	virtual ~OldMouse();


#if SIMULATION == 1
	  int     length_frontwall();
	  void    update_sensors(void);
#endif

	  bool    WalkToGoal ( );
	  bool    RunToGoal  ( );

	  bool    FindGoal ( bool mode );
	  bool    StartToGoal(uint8_t startDir);
	  bool    GoalToStart(uint8_t startDir);

	  int     HowToGo(  uint8_t * mx, uint8_t * my, uint8_t * mdir, bool direction ); // thiking
	  uint8_t MoveAction(Queue * this_queue, uint8_t startDir); // moving
	  uint8_t MoveActionSub(uint8_t distance, uint8_t curDir, uint8_t nextDir); // moving sub

	  int     Buildshortcut(Queue * this_queue, uint8_t *px, uint8_t *py, uint8_t lx, uint8_t ly, uint8_t dir, bool state) ;
};

#endif /* OLDMOUSE_H_ */
