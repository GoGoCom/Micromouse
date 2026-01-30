/*
 * CDriveSensors.cpp
 *
 *  Created on: Nov 2, 2025
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Peter Harrison / ukmars
*/
#include <Mice.h>
#include <BodyConfig.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <CDriveSensors.h>

//extern ADC_HandleTypeDef hadc1;
extern Adafruit_SSD1306 display;

CDriveSensors::CDriveSensors() {
	// TODO Auto-generated constructor stub

}

CDriveSensors::~CDriveSensors() {
	// TODO Auto-generated destructor stub
}

void CDriveSensors::init() {

	// write code here what you need

}

void CDriveSensors::reset_sensors() {

	// write code here what you need
	disable_steering() ;
	reset_steering() ;
}

void CDriveSensors::update_sensors(float *battery_scale,  float *steering_adjustment) {
	*battery_scale       = update_battery_voltage();
	*steering_adjustment = update_wall_sensors();
}

/**
 * The steering adjustment is an angular error that is added to the
 * current encoder angle so that the robot can be kept central in
 * a maze cell.
 *
 * A PD controller is used to generate the adjustment and the two constants
 * will need to be adjusted for the best response. You may find that only
 * the P term is needed
 *
 * The steering adjustment is limited to prevent over-correction. You should
 * experiment with that as well.
 *
 * @brief Calculate the steering adjustment from the cross-track error.
 * @param error calculated from wall sensors, Negative if too far left
 * @return steering adjustment in degrees
 */
float CDriveSensors::calculate_steering_adjustment(float error) {
  // always calculate the adjustment for testing. It may not get used.
  float pTerm = STEERING_KP * error;
  float dTerm = STEERING_KD * (error - last_steering_error);
  float adjustment = (pTerm + dTerm) * LOOP_INTERVAL;
  // TODO: are these limits appropriate, or even needed?
  adjustment = Constrainf(adjustment, -STEERING_ADJUST_LIMIT, STEERING_ADJUST_LIMIT);
  last_steering_error = error;

  return adjustment;
}

void CDriveSensors::reset_steering() {
  last_steering_error   = 0;
}

void CDriveSensors::enable_steering() {
  reset_steering();
  steering_enabled = true;
};

void CDriveSensors::disable_steering() {
  steering_enabled = false;
}

/***************************************************************************/

float CDriveSensors::update_battery_voltage() {

	battery_adc_reading = MotorPower();

	float      battery_voltage = BATTERY_MULTIPLIER * battery_adc_reading ; // main battery voltage - 255; //1023; //4096;
	float      battery_scale = 255.0 / ( battery_voltage - 3.0f) ; //3.0f is diffrence with main batery and motor voltage

	return battery_scale;
}
/*********************************** Wall tracking **************************/
/***
 * This is for the basic, three detector wall sensor only
 *
 * Note: Runs in the systick interrupt. DO NOT call this directly.
 * @brief update the global wall sensor values.
 * @return robot cross-track-error. Too far left is negative.
 */
float CDriveSensors::update_wall_sensors() {


	right_wall_sensor_raw = GetValue(2);
	front_wall_sensor_raw = GetValue(1);
	left_wall_sensor_raw  = GetValue(0);

	// normalise to a nominal value of 100
	right_wall_sensor = (int)(right_wall_sensor_raw * RIGHT_SCALE);
	front_wall_sensor = (int)(front_wall_sensor_raw * FRONT_SCALE);
	left_wall_sensor  = (int)(left_wall_sensor_raw  * LEFT_SCALE);

	// set the wall detection flags
	left_wall_present  = left_wall_sensor  > LEFT_THRESHOLD;
	right_wall_present = right_wall_sensor > RIGHT_THRESHOLD;
	front_wall_present = front_wall_sensor > FRONT_THRESHOLD;

		// calculate the alignment errors - too far left is negative
	if (steering_enabled) {
		float error = 0;
		float right_error = RIGHT_NOMINAL - right_wall_sensor;
		float left_error  = LEFT_NOMINAL  - left_wall_sensor;

		if (left_wall_present && right_wall_present) {
		 error = left_error - right_error;
		} else if (left_wall_present) {
		 error = 2.0 * left_error;
		} else if (right_wall_present) {
		 error = -2.0 * right_error;
		}
		// the side sensors are not reliable close to a wall ahead.
		// TODO: The magic number 100 may need adjusting
		if (front_wall_sensor > 100) {
		 error = 0;
		}
		steering_adjustment = calculate_steering_adjustment(error);
	}
	else steering_adjustment = 0;

  return steering_adjustment;

}

short CDriveSensors::SensorsDisplay(void) {
//	char buf[20];

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor( SSD1306_WHITE, SSD1306_BLACK);  
  display.setCursor(40, 50);
  display.println(battery_adc_reading);
  display.display(); 
  
//	right_wall_sensor_raw = analogRead(9);
//	front_wall_sensor_raw = analogRead(8);
//	left_wall_sensor_raw  = analogRead(7);

 // display.clearDisplay();
  
 // display.setTextSize(1); // Draw 2X-scale text
 // display.setTextColor(SSD1306_WHITE);

 // display.setCursor(25, 0);
 // display.println(front_wall_sensor_raw);
 // display.setCursor(75, 17);
 // display.println(right_wall_sensor_raw);
 // display.setCursor(20, 17);
 // display.println(left_wall_sensor_raw);
    
 // display.display();  
		//ssd1306_clearScreen();
/*
		sprintf(buf, "%04d", front_wall_sensor_raw );
		ssd1306_printFixed(25,  0 , buf, STYLE_NORMAL);
		sprintf(buf, "%04d", front_wall_sensor);
		ssd1306_printFixed(60,  0 , buf, STYLE_NORMAL);

		sprintf(buf, "%04d", left_wall_sensor_raw);
		ssd1306_printFixed(20, 17, buf, STYLE_NORMAL);
		sprintf(buf, "%04d", right_wall_sensor_raw );
		ssd1306_printFixed(75, 17, buf, STYLE_NORMAL);

		sprintf(buf, "%04d", left_wall_sensor);
		ssd1306_printFixed(20, 30, buf, STYLE_NORMAL);
		sprintf(buf, "%04d", right_wall_sensor);
		ssd1306_printFixed(75, 30, buf, STYLE_NORMAL);

		sprintf(buf, "%04d", battery_adc_reading );
		ssd1306_printFixed(40, 50 , buf, STYLE_NORMAL);
*/
		return None;

}

//***************************************************************************//

uint16_t CDriveSensors::ADC_Select_CHx( uint32_t Channel )
{
	/*
	ADC_ChannelConfTypeDef sConfig = {0};

	// Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	
	sConfig.Channel = Channel;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES; // 15, 28,56
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		// ignore Error_Handler();
	}

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1,1);
	uint32_t value = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
*/
	return 0; //(uint16_t) value;
}

/**
 * Paramerter pin: is the pin which we wish to send an IR pulse for.
 * This is called by the interrupt handler.``
 */
 /*
void CDriveSensors::IR_pulse(GPIO_TypeDef *GPIOPort, uint16_t GPIOPin) {
    if (cc1Flag == 0) {
    	HAL_GPIO_WritePin(GPIOPort, GPIOPin, GPIO_PIN_SET);
        cc1Flag = 1;
    } else {
    	HAL_GPIO_WritePin(GPIOPort, GPIOPin, GPIO_PIN_RESET);
        cc1Flag = 0;
    }
}
*/

// Read by timer interrupt.
uint16_t CDriveSensors::GetValue(int which) {

//	uint16_t value;
/*
	IR_pulse(SensorCfgParam[which].GPIOx, SensorCfgParam[which].EnablePin);
	value = ADC_Select_CHx( SensorCfgParam[which].AdcChannel  )	;
	IR_pulse(SensorCfgParam[which].GPIOx, SensorCfgParam[which].EnablePin);
*/
	return 0; //value;
}


uint16_t CDriveSensors::MotorPower(void) {

	return analogRead(14); //ADC_Select_CHx( SensorCfgParam[3].AdcChannel );

}


