/*
 * CDriveReports.h
 *
 *  Created on: Nov 3, 2025
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Peter Harrison / ukmars
*/

#ifndef CDRIVEREPORTS_H_
#define CDRIVEREPORTS_H_

class CDriveProfile;
class CDriveSensors;
class CDriveEncoders;
class CDriveMotors;

class CDriveReports {
public:
	CDriveReports();
	virtual ~CDriveReports();

	CDriveProfile  *pfwd, *prot;
	CDriveEncoders *penc;
	CDriveSensors  *psns;
	CDriveMotors   *pmot;


	uint32_t start_time;
	uint32_t report_time;
	uint32_t report_interval = REPORTING_INTERVAL;

	void init(CDriveSensors  *sns, CDriveEncoders *enc, CDriveMotors *mot, CDriveProfile  *fwd, CDriveProfile *rot);
	void report_profile();
	void report_profile_header();

	void report_sensor_track_header();
	void report_sensor_track();
	void report_sensor_track_raw();

	void report_front_sensor_track_header();
	void report_front_sensor_track();

	void report_wall_sensors();

	/**
	 * The encoder report is probably only useful for calibration.
	 * Repeatedly displays the left and right encoder totals along
	 * with how the robot interprets these as forward motion (mm)
	 * and rotation (deg).
	 *
	 * Report the header first to restart the reporting timer
	 *
	 * @brief Sends the encoder totals with robot position and angle
	 */
	void report_encoders();
	void report_encoder_header();

	/**
	 * The controllers work by comparing the profiled positin and angle
	 * with values obtained from the encoders.
	 *
	 * All four values are reported here.
	 *
	 * @brief Send the profiled and actual position and angle
	 */
	void report_pose();


};

#endif /* CDRIVEREPORTS_H_ */
