/*
 * CDriveEncoder.h
 *
 *  Created on: Nov 2, 2025
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Peter Harrison / ukmars
*/

#ifndef CDRIVEENCODERS_H_
#define CDRIVEENCODERS_H_

class CDriveEncoders {
public:
	CDriveEncoders();
	virtual ~CDriveEncoders();


//
	float s_robot_position;
	float s_robot_angle;

	float s_robot_fwd_increment ;
	float s_robot_rot_increment ;

	int32_t prevLEnc;
	int32_t prevREnc;

	int32_t left_total;
	int32_t right_total;


// Functions
	void  init(void);
	void  reset_encoders();
	void  update_encoders();

	float robot_fwd_increment();
	float robot_rot_increment();

	float robot_position();
	float robot_angle();

	int32_t LEnc(void);
	int32_t REnc(void);

};

#endif /* CDRIVEENCODERS_H_ */
