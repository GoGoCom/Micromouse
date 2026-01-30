/*
 * CBrain.h
 *
 *  Created on: Feb 10, 2024
 *      Author: David(Yong eel) Lee
*/

#ifndef CBRAIN_H_
#define CBRAIN_H_

#include <Cerebellum.h>
#include <Cerebrum.h>

class CBody;

class CBrain :  public Cerebrum,  public Cerebellum {
public:
	CBrain();
	virtual ~CBrain();

      uint8_t mouse_direction= NORTH;    /* keeps track of direction that mouse is moving in */
      uint8_t mouse_x = 0, mouse_y = 0; /* keeps track of current row = mouse_y, col = mouse_x value mouse is in within maze */
      uint8_t goal_x  = 0, goal_y  = 0; /* keeps track of goal's x, y, once found */

	  void  BrainInit( Simulation *smp, CBody *objBody ); //Simulation *smp, CDriveMotors *mot, CDriveSensors  *sns, CDriveProfile  *fwd, CDriveProfile *rot, AccelStepper *lst, AccelStepper *rst, CDriveReports  *rpt);
	  bool  FindGoal ( bool mode );
	  bool  StartToGoal(uint8_t startDir);
	  bool  GoalToStart(uint8_t startDir);

	  uint8_t HowToGo (  uint8_t * mx, uint8_t * my, uint8_t * mdir, bool direction ); // thiking
	  uint8_t MoveAction(Queue * this_queue, uint8_t startDir); // moving

	  bool CheckBoundary(  );

};

#endif /* CBRAIN_H_ */
