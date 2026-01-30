/*
 * Cerebellum.h
 *
 *  Created on: Feb 10, 2024
 *      Author: David(Yong eel) Lee
*/

#ifndef CEREBELLUM_H_
#define CEREBELLUM_H_

#include <Buffers.h>

class CBody;
class Simulation;

class Cerebellum  {
public:
	Cerebellum();
	virtual ~Cerebellum();

 	    CBody       *pBody;
		Simulation  *hsmp;
		Buffers     bufs;
		Queue 		*mouse_queue, *visit_queue;

		short mouse_pose = 0;

		bool leftWall;
		bool frontWall;
		bool rightWall;

// Functions
		void CerebellumInit(Simulation *smp, CBody *objBody ); //Simulation *smp, CDriveMotors *mot, CDriveSensors  *sns, CDriveProfile  *fwd, CDriveProfile *rot, AccelStepper *lst, AccelStepper *rst, CDriveReports  *rpt);
		void update_sensors();
		void TestMoving(Simulation *simp);

		void stopAndAdjust();
		void end_run();
		void stop_at(float distance);
		void stop_after(float distance);
		void wait_until_position(float position);
		void wait_until_distance(float distance);

		void turn(float angle, float omega, float alpha);
		void spin_turn(float degrees, float speed, float acceleration);

		void turnLeft45(void);
		void turnRight45(void);
		void turnLeft90(void);
		void turnRight90(void) ;
		void turnBack(void);

		void moveEdgeForward(short length);
		void moveHalfForward(short length);
		void moveFullForward(short length);

		void smoothLeft90(void);
		void smoothRight90(void);
		void smoothTurnBack(void);
		void smoothFullForward(short length);

		void turnSub(int mode);
		void moveSub(int mode, short length);
		void smoothSub(int mode);

		void readyToGo(void);
		void display_str(char *str);
};

#endif /* CEREBELLUM_H_ */
