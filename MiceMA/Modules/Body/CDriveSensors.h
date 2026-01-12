/*
 * CDriveSensors.h
 *
 *  Created on: Nov 2, 2025
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Peter Harrison / ukmars
*/

#ifndef CDRIVESENSORS_H_
#define CDRIVESENSORS_H_

#define None       0
#define Both       1
#define Left       2
#define Right      3
#define FrontNone  4
#define FrontBoth  5
#define FrontLeft  6
#define FrontRight 7

class CDriveSensors {
public:
	CDriveSensors();
	virtual ~CDriveSensors();


	/*** wall sensor variables ***/
	int   front_wall_sensor;
	int   left_wall_sensor;
	int   right_wall_sensor;

	int   front_wall_sensor_raw;
	int   left_wall_sensor_raw;
	int   right_wall_sensor_raw;

	/*** true if a wall is present ***/
	bool  left_wall_present;
	bool  front_wall_present;
	bool  right_wall_present;

	/*** steering variables ***/
	bool  steering_enabled;


	/***  Local variables ***/
	float last_steering_error = 0;
	float steering_adjustment;

	uint16_t battery_adc_reading;
	uint8_t  cc1Flag = 0;

	// Functions
	void  init();
	void  reset_sensors();
	void  update_sensors(float *battery_scale,  float *steering_adjustment) ;
	float update_battery_voltage();
	float update_wall_sensors();
	void  reset_steering();
	void  enable_steering();
	void  disable_steering();
	float calculate_steering_adjustment(float error);

	short    SensorsDisplay(void);
	uint16_t GetValue(int which) ; // read value
	uint16_t MotorPower(void);

	uint16_t ADC_Select_CHx( uint32_t Channel );
	void     IR_pulse(GPIO_TypeDef *GPIOPort, uint16_t GPIOPin) ;

	//
	inline int get_left_sensor() {
	  int value;
	//  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		value = left_wall_sensor;
	//  }
	  return value;
	}

	inline int get_front_sensor() {
	  int value;
	//  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		value = front_wall_sensor;
	//  }
	  return value;
	}

	inline int get_right_sensor() {
	  int value;
	//  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		value = right_wall_sensor;
	//  }
	  return value;
	}


	inline void wait_for_front_sensor() {
	  //enable_sensors();
	  while (front_wall_sensor < 250) {
		delay(10);
	  }
	  while (front_wall_sensor > 200) {
		delay(10);
	  }
	  //disable_sensors();
	  delay(500);
	}
	// TODO - make these NOT inline and move to UI

};

#endif /* CDRIVESENSORS_H_ */
