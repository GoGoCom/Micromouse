/*
 * CBrain.cpp
 *
 *  Created on: Feb 10, 2024
 *      Author: David(Yong eel) Lee
*/
#include <Mouse.h>

#include <BrainConfig.h>
#include <BodyConfig.h>

#include <CBrain.h>
#include <CBody.h>

CBrain::CBrain() {
	// TODO Auto-generated constructor stub

}

CBrain::~CBrain() {
	// TODO Auto-generated destructor stub
}

void  CBrain::BrainInit( Simulation *smp, CBody *objBody ) {
	CerebrumInit(smp);
	CerebellumInit(smp, objBody);
}

bool  CBrain::FindGoal ( bool mode ){
	return true;
}
bool  CBrain::StartToGoal(uint8_t startDir){
	return true;
}
bool  CBrain::GoalToStart(uint8_t startDir){
	return true;
}

uint8_t CBrain::HowToGo (  uint8_t * mx, uint8_t * my, uint8_t * mdir, bool direction ){ // thiking
	return 0;
}

uint8_t CBrain::MoveAction(Queue * this_queue, uint8_t startDir) {	// moving
	return 0;
}


bool CBrain::CheckBoundary(  ) {
    // negative coord check ... for errors

	if (mouse_x < START_X || mouse_y < START_Y) {
	  printf("log NEGATIVE COORD: ERROR\n");
	  return false;
	}
	if ( (mouse_x > (SIZE - 1)) || (mouse_y > (SIZE - 1)) ) {
	  printf("log OVER COORD: ERROR\n");
	  return false;
	}
	return true;
}
