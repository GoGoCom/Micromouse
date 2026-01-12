/*
 * CDriveEncoder.cpp
 *
 *  Created on: Nov 2, 2025
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Peter Harrison / ukmars
*/

#include <Mouse.h>
#include <BodyConfig.h>

#include <CDriveEncoders.h>

CDriveEncoders::CDriveEncoders() {
	// TODO Auto-generated constructor stub
}

CDriveEncoders::~CDriveEncoders() {
	// TODO Auto-generated destructor stub
}

void CDriveEncoders::init(void){

	// write code here what you need

	reset_encoders();

}

void CDriveEncoders::reset_encoders() {

	MotorCfgParam[LEFT].EncoderTIM_Instance->CNT  = 0;
	MotorCfgParam[RIGHT].EncoderTIM_Instance->CNT = 0;

    prevLEnc    = 0;
    prevREnc    = 0;

    s_robot_position = 0;
    s_robot_angle    = 0;

    s_robot_fwd_increment = 0;
    s_robot_rot_increment = 0;

}

// units are all in counts and counts per second
void CDriveEncoders::update_encoders() {

	int32_t left_delta;
	int32_t right_delta;

	float left_change ;
	float right_change ;

	// write code here what you need

	left_total  =  LEnc();
	right_total =  REnc();

	left_delta  =  LEnc()- prevLEnc;
	right_delta =  REnc()- prevREnc;

	prevLEnc = left_total ;
	prevREnc = right_total;

	left_change  = left_delta  * MM_PER_COUNT_LEFT;
	right_change = right_delta * MM_PER_COUNT_RIGHT;

	s_robot_fwd_increment = 0.5f * (right_change + left_change);
	s_robot_rot_increment = (right_change - left_change) * DEG_PER_MM_DIFFERENCE;

	s_robot_position += s_robot_fwd_increment;
	s_robot_angle    += s_robot_rot_increment;

}

float CDriveEncoders::robot_fwd_increment() {
  float distance;
//  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {  //__disable_irq() and __enable_irq()
	  distance = s_robot_fwd_increment;
//  }
  return distance;
}

float CDriveEncoders::robot_rot_increment() {
  float distance;
 // ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
	  distance = s_robot_rot_increment;
 // }
  return distance;
}

float CDriveEncoders::robot_position() {
  float distance;
 // ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
	  distance = s_robot_position;
 // }
  return distance;
}

float CDriveEncoders::robot_angle() {
  float angle;
  // ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
 	  angle = s_robot_angle;
  // }
  return angle;
}


int32_t CDriveEncoders::LEnc(void)
{
	return 	 ENCODER_LEFT_POLARITY*(int32_t) MotorCfgParam[LEFT].EncoderTIM_Instance->CNT;
}

int32_t CDriveEncoders::REnc(void)
{
	return 	ENCODER_RIGHT_POLARITY*(int32_t) MotorCfgParam[RIGHT].EncoderTIM_Instance->CNT;
}




