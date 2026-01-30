/*
 * CMice.h
 *
 *  Created on: Nov 2, 2025
 *      Author: David(Yong eel) Lee
*/

#ifndef CMICE_H_
#define CMICE_H_

#include <CBody.h>
#include <CBrain.h>

class CMice: public CBrain {
public:
	CMice();
	virtual ~CMice();

	CBody          objBody;

	void miceInit(Simulation *smp);
	void miceReset();
	void miceUpdate();

};

#endif /* CMICE_H_ */
