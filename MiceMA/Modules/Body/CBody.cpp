/*
 * CBody.cpp
 *
 *  Created on: Nov 2, 2025
 *      Author: David(Yong eel) Lee
*/
#include <Mouse.h>
#include <BodyConfig.h>

#include <CBody.h>

CBody::CBody() {
	// TODO Auto-generated constructor stub

}

CBody::~CBody() {
	// TODO Auto-generated destructor stub
}

void CBody::start_motor_controllers() {
	reset_motor_controllers() ;
	//
	objEyes.enable_steering();
	enable_motor_controllers();
}

void CBody::reset_motor_controllers() {

	objMindForward.reset();
	objMindRotation.reset();
	objLegs.reset_motors();
    objEyes.reset_sensors();
    objArms.reset_encoders();

	disable_motor_controllers();

	// write code here what you need
	fwd_error = 0;
	rot_error = 0;
	old_fwd_error = 0;
	old_rot_error = 0;

}

void CBody::enable_motor_controllers() {
  controllers_output_enabled = true;
}

void CBody::disable_motor_controllers() {
  controllers_output_enabled = false;
}

float CBody::position_controller() {

	objMindForward.update();

	// write code here what you need
	fwd_error += objMindForward.increment() - objArms.robot_fwd_increment();
	float diff = fwd_error - old_fwd_error;
	old_fwd_error = fwd_error;
	float output = FWD_KP * fwd_error + FWD_KD * diff;

	return output;
}

float CBody::angle_controller() {

	objMindRotation.update();

	// write code here what you need
	rot_error += objMindRotation.increment() - objArms.robot_rot_increment();
	if (objEyes.steering_enabled) {
		rot_error += steering_adjustment;
	}
	float diff = rot_error - old_rot_error;
	old_rot_error = rot_error;
	float output =ROT_KP * rot_error + ROT_KD * diff;

	return output;
}

void CBody::update_motor_controllers() {

	// write code here what you need

	  float pos_output   = position_controller();
	  float rot_output   = angle_controller();
	  float left_output  = 0;
	  float right_output = 0;

	  left_output  += pos_output;
	  right_output += pos_output;

	  left_output  -= rot_output;
	  right_output += rot_output;

	  float v_fwd   = objMindForward.speed();
	  float v_rot   = objMindRotation.speed();
	  float v_left  = v_fwd - (PI / 180.0) * MOUSE_RADIUS * v_rot;
	  float v_right = v_fwd + (PI / 180.0) * MOUSE_RADIUS * v_rot;

	  left_output  += SPEED_FF * v_left;
	  right_output += SPEED_FF * v_right;

	  if (controllers_output_enabled) {
			objLegs.update_motors(left_output, right_output);
	  }
}

void CBody::BodyInits(){
	objEyes.init();
	objArms.init();
	objLegs.init();
	objMindForward.init();
	objMindRotation.init();
	objMouth.init(&objEyes, &objArms, &objLegs, &objMindForward, &objMindRotation);

	reset_motor_controllers() ; // legs(Motor) controller
}

void CBody::BodyResets() {

	reset_motor_controllers();
}

void CBody::BodyDisplay() {
	objEyes.SensorsDisplay();
}

// regulary updated by timer loop interrupt 500Hz
void CBody::BodyUpdates(){

	objEyes.update_sensors( &objLegs.battery_scale, &steering_adjustment );
	objArms.update_encoders();

	update_motor_controllers( );

}
