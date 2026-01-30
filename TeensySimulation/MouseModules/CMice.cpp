/*
 * CMice.cpp
 *
 *  Created on: Nov 2, 2025
 *      Author: David(Yong eel) Lee
*/

#include <Mice.h>
#include <BrainConfig.h>
#include <BodyConfig.h>

#include <CMice.h>

CMice::CMice() {
	// TODO Auto-generated constructor stub

}

CMice::~CMice() {
	// TODO Auto-generated destructor stub
}

void CMice::miceInit(Simulation *smp) {

	BrainInit(smp, &objBody);
	objBody.BodyInits();

}

void CMice::miceReset() {

	objBody.BodyResets();

}

void CMice::miceUpdate() {

	objBody.BodyUpdates();

}
