/*
 * CDriveProfile.h
 *
 *  Created on: Nov 3, 2025
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Peter Harrison / ukmars
*/

#ifndef CDRIVEPROFILE_H_
#define CDRIVEPROFILE_H_

enum ProfileState : uint8_t {
  CS_IDLE = 0,
  CS_ACCELERATING = 1,
  CS_BRAKING = 2,
  CS_FINISHED = 3,
};

class CDriveProfile {
public:
	CDriveProfile();
	virtual ~CDriveProfile();

	void  init();
	void  reset();
	void  update();


	// write code here what you need
	void  clear_counters();
	bool  is_finished();
	void  start(float distance, float top_speed, float final_speed, float acceleration);
	void  stop();
	void  set_state(ProfileState state) ;
	float get_braking_distance();
	float position();
	float speed() ;
	float increment();
	float acceleration();
	void  set_speed(float speed);
	void  set_target_speed(float speed);
	// normally only used to alter position for forward error correction
	void  adjust_position(float adjustment);
	void  set_position(float position);
	// update is called from within systick and shoul dbe safe from interrupts
	void  finish() ;

private:
	volatile uint8_t m_state = CS_IDLE;
	volatile float m_speed = 0;
	volatile float m_position = 0;
	int8_t m_sign = 1;
	float m_acceleration = 0;
	float m_one_over_acc = 1;
	float m_target_speed = 0;
	float m_final_speed = 0;
	float m_final_position = 0;
};

#endif /* CDRIVEPROFILE_H_ */
