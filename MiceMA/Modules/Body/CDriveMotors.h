/*
 * CDriveMotors.h
 *
 *  Created on: Nov 2, 2025
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Peter Harrison / ukmars
*/

#ifndef CDRIVEMOTORS_H_
#define CDRIVEMOTORS_H_

class CDriveMotors {
public:
	CDriveMotors();
	virtual ~CDriveMotors();

    typedef enum
    {
    	DIRECTION_CCW = 0,  ///< Counter-Clockwise
        DIRECTION_CW  = 1   ///< Clockwise
    } Direction;

	//float g_battery_voltage;
	float battery_scale;
	float left_motor_volts, right_motor_volts;
	/***
	 * The motors module provides low  control of the drive motors
	 * in a two-wheel differential drive robot.
	 */
	void init(void);
	void reset_motors(void);
	void update_motors(float left_volts, float right_volts);
	/***
	 * @brief write zero volts to both motors
	 */
	void stop_motors(void);

	/***
	 * -255 <= pwm <= 255
	 * @brief set motor direction and PWM
	 */
	void setPWMLeft( uint16_t LpwmA, uint16_t  LpwmB);
	void setPWMRight(uint16_t LpwmA, uint16_t  LpwmB);

	void set_left_motor_pwm( int pwm);
	void set_right_motor_pwm(int pwm);

	/***
	 * The input voltage be any value and will be scaled to compensate for changes
	 * in battery voltage such that maximum drive to the motors is limited to the
	 * value of MAX_MOTOR_VOLTS in the defaults (normally +/- 6.0 Volts)
	 * @brief adjust the motor PWM to deliver the given volate to the motor
	 */
	void set_left_motor_volts( float volts);
	void set_right_motor_volts(float volts);


};

#endif /* CDRIVEMOTORS_H_ */
