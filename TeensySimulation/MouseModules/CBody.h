/*
 * CBody.h
 *
 *  Created on: Nov 2, 2025
 *      Author: David(Yong eel) Lee
*/

#ifndef CBODY_H_
#define CBODY_H_

#include <CDriveEncoders.h>
#include <CDriveMotors.h>
#include <CDriveProfile.h>
#include <CDriveReports.h>
#include <CDriveSensors.h>

class CBody {
public:
	CBody();
	virtual ~CBody();

	// Objects
	CDriveProfile  objMindForward, objMindRotation;
	CDriveSensors  objEyes;
	CDriveEncoders objArms;
	CDriveMotors   objLegs;
	CDriveReports  objMouth;

	// these are maintained only for logging

	bool  controllers_output_enabled;
	float old_fwd_error;
	float old_rot_error;
	float fwd_error;
	float rot_error;

	float steering_adjustment;

	// functions
	void  enable_motor_controllers();
	void  disable_motor_controllers();
	float position_controller();
	float angle_controller();
	void  start_motor_controllers();
	void  reset_motor_controllers();
	void  update_motor_controllers();

	void BodyInits();
	void BodyResets();
	void BodyUpdates();
	void BodyDisplay();
};

#endif /* CBODY_H_ */
