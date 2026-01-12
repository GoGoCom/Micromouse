/*
 * CDriveReports.cpp
 *
 *  Created on: Nov 3, 2025
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Peter Harrison / ukmars
*/
#include <Mouse.h>
#include <BodyConfig.h>

#include <CDriveEncoders.h>
#include <CDriveMotors.h>
#include <CDriveProfile.h>
#include <CDriveSensors.h>

#include <CDriveReports.h>

#define DEBUG_LOGGING 1

CDriveReports::CDriveReports() {
	// TODO Auto-generated constructor stub
}

CDriveReports::~CDriveReports() {
	// TODO Auto-generated destructor stub
}

void CDriveReports::init(CDriveSensors  *sns, CDriveEncoders *enc, CDriveMotors *mot, CDriveProfile  *fwd, CDriveProfile *rot) {
	pmot  = mot;
	psns  = sns;
	penc  = enc;
	pfwd  = fwd;
	prot  = rot;
}

// note that the Serial device has a 64 character buffer and, at 115200 baud
// 64 characters will take about 6ms to go out over the wire.
void CDriveReports::report_profile_header() {
#if DEBUG_LOGGING == 1
  printf("\n time robotPos robotAngle fwdPos  fwdSpeed rotpos rotSpeed fwdVolts rotVolts\n");
  start_time = millis();
  report_time = start_time;
#endif
}

void CDriveReports::report_profile() {
#if DEBUG_LOGGING == 1
  if (millis() >= report_time) {
    report_time += report_interval;

	// write code here what you need
    //    printf("%04ld %7.2f %7.2f    %7.2f   %7.2f %7.2f %7.2f %7.2f %7.2f \n", millis() - start_time,penc->robot_position(),penc->robot_angle(),pfwd->position(),pfwd->speed(),prot->position(),prot->speed(),50 * (pmot->right_motor_volts + pmot->left_motor_volts),50 * (pmot->right_motor_volts - pmot->left_motor_volts) );
//        printf("%04ld %7.2f %7.2f    %7.2f   %7.2f %7.2f %7.2f %7.2f %7.2f / %ld, %ld / %7.2f\n", millis() - start_time,penc->robot_position(),penc->robot_angle(),pfwd->position(),pfwd->speed(),prot->position(),prot->speed(),pmot->right_motor_volts , pmot->left_motor_volts, penc->left_total, penc->right_total, penc->s_robot_fwd_increment );
        printf("%7ld %7ld:%7.2f %7.2f    %7.2f   %7.2f %7.2f %7.2f %7.2f %7.2f \n", penc->LEnc(), penc->REnc(), penc->robot_position(),penc->robot_angle(),pfwd->position(),pfwd->speed(),prot->position(),prot->speed(),pmot->right_motor_volts , pmot->left_motor_volts );

  }
#else
  delay(2);
#endif
}

//***************************************************************************//

void CDriveReports::report_sensor_track_header() {
#if DEBUG_LOGGING == 1
  printf("\n time robotPos robotAngle left right front error adjustment\n");
  start_time = millis();
  report_time = start_time;
#endif
}

void CDriveReports::report_sensor_track() {
#if DEBUG_LOGGING == 1
  if (millis() >= report_time) {

	// write code here what you need
	printf("%04ld <> %7.2f %7.2f      %4d %4d %4d  : %7.2f : %7.2f %7.2f \n", millis() - start_time,penc->robot_position(),penc->robot_angle(),psns->left_wall_sensor_raw,psns->front_wall_sensor_raw,psns->right_wall_sensor_raw,psns->steering_adjustment , pmot->left_motor_volts, pmot->right_motor_volts);

  }
#else
  delay(2);
#endif
}

void CDriveReports::report_sensor_track_raw() {
#if DEBUG_LOGGING == 1
  if (millis() >= report_time) {
    report_time += report_interval;

	// write code here what you need
    printf("%ld %f %f %d %d %d %f \n", millis() - start_time,penc->robot_position(),penc->robot_angle(),psns->left_wall_sensor_raw,psns->right_wall_sensor_raw,psns->front_wall_sensor_raw, psns->steering_adjustment);

  }
#else
  delay(2);
#endif
}

void CDriveReports::report_front_sensor_track_header() {
#if DEBUG_LOGGING == 1
  printf("\n time pos front_normal front_raw\n");
  start_time = millis();
  report_time = start_time;
#endif
}

void CDriveReports::report_front_sensor_track() {
#if DEBUG_LOGGING == 1
  if (millis() >= report_time) {
    report_time += report_interval;

	// write code here what you need
    printf("%ld %f %d %d \n",millis() - start_time,fabsf(penc->robot_position()),psns->front_wall_sensor,psns->front_wall_sensor_raw);

  }
#else
  delay(2);
#endif
}

//***************************************************************************//

void CDriveReports::report_encoder_header() {
#if DEBUG_LOGGING == 1
  printf("\n left right position angle\n");
  start_time = millis();
  report_time = start_time;
#endif
}

void CDriveReports::report_encoders() {
#if DEBUG_LOGGING == 1
  if (millis() >= report_time) {
    report_time += report_interval;

	// write code here what you need
//    printf("%7ld %7ld , %7d %7d , %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f\n", penc->encoder_left_total(),penc->encoder_right_total(), int(penc->robot_position()),int(penc->robot_angle()), pmot->t0_left_output, pmot->t0_right_output, pmot->t1_left_output, pmot->t1_right_output, pmot->t2_left_output ,  pmot->t2_right_output, pmot->right_motor_volts , pmot->left_motor_volts );
    printf("%7ld %7ld , %7d %7d , %8.2f %8.2f\n", penc->LEnc(),penc->REnc(), int(penc->robot_position()),int(penc->robot_angle()),  pmot->right_motor_volts , pmot->left_motor_volts );

  }
#else
  delay(2);
#endif
}

//***************************************************************************//

void CDriveReports::report_pose() {
#if DEBUG_LOGGING == 1

	// write code here what you need
	  printf("Angle (deg): %f  Position (mm): %f  fwd : %f rot : %f \n", penc->robot_angle(),penc->robot_position(),pfwd->position(),prot->position());

#else
  delay(2);
#endif
}

//***************************************************************************//

void CDriveReports::report_wall_sensors() {

	// write code here what you need
  int left_raw;
  int front_raw;
  int right_raw;
  int left;
  int front;
  int right;
 // ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
	left = psns->left_wall_sensor;
	front = psns->front_wall_sensor;
	right = psns->right_wall_sensor;
	left_raw = psns->left_wall_sensor_raw;
	front_raw = psns->front_wall_sensor_raw;
	right_raw = psns->right_wall_sensor_raw;
//  }
 printf("RAW %d, %d, %d <-> %d, %d, %d\n",left_raw,front_raw,right_raw, left,front,right);
}

