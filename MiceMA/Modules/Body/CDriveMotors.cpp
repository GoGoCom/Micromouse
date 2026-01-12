/*
 * CDriveMotors.cpp
 *
 *  Created on: Nov 2, 2025
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Peter Harrison / ukmars
*/
#include <Mouse.h>
#include <BodyConfig.h>

#include <CDriveMotors.h>

CDriveMotors::CDriveMotors() {
	// TODO Auto-generated constructor stub
}

CDriveMotors::~CDriveMotors() {
	// TODO Auto-generated destructor stub
}

void CDriveMotors::init(void) {

	// write code here what you need
    stop_motors();
}

void CDriveMotors::reset_motors(void) {

	// write code here what you need
    stop_motors();
}
void CDriveMotors::update_motors(float left_volts, float right_volts) {
	  set_left_motor_volts(  left_volts);
	  set_right_motor_volts(right_volts);
}

void CDriveMotors::stop_motors() {
	set_left_motor_volts( 0);
	set_right_motor_volts(0);
}

void CDriveMotors::setPWMLeft(uint16_t LpwmA, uint16_t  LpwmB){
	*MotorCfgParam[LEFT].PWM_TIM_CCRa = LpwmA; // backward
	*MotorCfgParam[LEFT].PWM_TIM_CCRb = LpwmB; // foreward
}

void CDriveMotors::setPWMRight(uint16_t LpwmA, uint16_t  LpwmB){
	*MotorCfgParam[RIGHT].PWM_TIM_CCRa = LpwmA; // backward
	*MotorCfgParam[RIGHT].PWM_TIM_CCRb = LpwmB; // foreward
}

void CDriveMotors::set_left_motor_pwm(int pwm) {
	  pwm =  MOTOR_LEFT_POLARITY * Constrain(pwm, -255, 255);
	  if (pwm < 0) {
		  setPWMLeft(-pwm, 0); // backward
	  } else {
		  setPWMLeft(0, pwm);    // forward
	  }
}

void CDriveMotors::set_right_motor_pwm(int pwm) {
	  pwm = MOTOR_RIGHT_POLARITY * Constrain(pwm, -255, 255);
	  if (pwm < 0) {
		  setPWMRight(-pwm, 0); // backward
	  } else {
		  setPWMRight(0, pwm);    // forward
	  }
}

void CDriveMotors::set_left_motor_volts(float volts) {
	left_motor_volts = Constrainf(volts, -MAX_MOTOR_VOLTS, MAX_MOTOR_VOLTS);
	int motorPWM = (int)(left_motor_volts * battery_scale);
	set_left_motor_pwm(motorPWM);
}

void CDriveMotors::set_right_motor_volts(float volts) {
	right_motor_volts = Constrainf(volts, -MAX_MOTOR_VOLTS, MAX_MOTOR_VOLTS);
	int motorPWM = (int)(right_motor_volts * battery_scale);
	set_right_motor_pwm(motorPWM);
}


