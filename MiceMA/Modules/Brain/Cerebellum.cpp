/*
 * Cerebellum.cpp
 *
 *  Created on: Feb 10, 2024
 *      Author: David(Yong eel) Lee
*/

#include <Mouse.h>
#include <BrainConfig.h>
#include <BodyConfig.h>

#include <Cerebellum.h>
#include <CBody.h>

Cerebellum::Cerebellum() {
	// TODO Auto-generated constructor stub

}

Cerebellum::~Cerebellum() {
	// TODO Auto-generated destructor stub
}

void Cerebellum::CerebellumInit(Simulation *smp, CBody *objBody ) {

	pBody = objBody;
	hsmp  = smp;

}

//***************************************************************************//

void Cerebellum::update_sensors() {
  // reading the existence of walls in each direction, according to wall data
  //   in real mouse, walls will be checked by sensor

	// write code here what you need

	  rightWall = pBody->objEyes.right_wall_present;
	  leftWall  = pBody->objEyes.left_wall_present;
	  frontWall = pBody->objEyes.front_wall_present;

#if SIMULATION == 1
  {
	  frontWall = hsmp->wallFront();
	  leftWall  = hsmp->wallLeft ();
	  rightWall = hsmp->wallRight();
  }
#endif

}
//
//***************************************************************************//
/**
 * Before the robot begins a sequence of moves, this method can be used to
 * make sure everything starts off in a known state.
 *
 * @brief Reset profiles, counters and controllers. Motors off. Steering off.
 */


void Cerebellum::TestMoving(Simulation *simp) {

	  hsmp = simp;

	  pBody->start_motor_controllers();

	  moveFullForward(1);
	  turnLeft90();
	  turnRight90();
	  smoothLeft90();
	  smoothTurnBack();

	  delay(1);

	  pBody->reset_motor_controllers();

}

/**
 * The robot is assumed to be moving. This call will stop at a specific
 * distance. Clearly, there must be enough distance remaining for it to
 * brake to a halt.
 *
 * The current values for speed and acceleration are used.
 *
 * Calling this with the robot stationary is undefined. Don't do that.
 *
 * @brief bring the robot to a halt at a specific distance
 */
void Cerebellum::stop_at(float position) {

	// write code here what you need
	  float remaining = position - pBody->objMindForward.position();
	  pBody->objMindForward.start(remaining, pBody->objMindForward.speed(), 0, pBody->objMindForward.acceleration());
	  while (not pBody->objMindForward.is_finished()) {
		  pBody->objMouth.report_profile();
	  }
}

/**
 * The robot is assumed to be moving. This call will stop  after a
 * specific distance has been travelled
 *
 * Clearly, there must be enough distance remaining for it to
 * brake to a halt.
 *
 * The current values for speed and acceleration are used.
 *
 * Calling this with the robot stationary is undefined. Don't do that.
 *
 * @brief bring the robot to a halt after a specific distance
 */
void Cerebellum::stop_after(float distance) {

	// write code here what you need
	pBody->objMindForward.start(distance, pBody->objMindForward.speed(), 0, pBody->objMindForward.acceleration());
	while (not pBody->objMindForward.is_finished()) {
		pBody->objMouth.report_profile();
	}
}

/**
 * The robot is assumed to be moving. This utility function call will just
 * do a busy-wait until the forward profile gets to the supplied position.
 *
 * @brief wait until the given position is reached
 */
void Cerebellum::wait_until_position(float position) {

	// write code here what you need
	 while (pBody->objMindForward.position() < position) {
	    delay(2);
	  }
}

/**
 * The robot is assumed to be moving. This utility function call will just
 * do a busy-wait until the forward profile has moved by the given distance.
 *
 * @brief wait until the given distance has been travelled
 */
void Cerebellum::wait_until_distance(float distance) {

	// write code here what you need
	float target = pBody->objMindForward.position() + distance;

	wait_until_position(target);
}


/**
 * Used to bring the mouse to a halt, centred in a cell.
 *
 * If there is a wall ahead, it will use that for a reference to make sure it
 * is well positioned.
 *
 * TODO: the critical values are robot-dependent.
 *
 * TODO: need a function just to adjust forward position
 */
void Cerebellum::stopAndAdjust() {

	// write code here what you need
	  float remaining = (FULL_CELL + HALF_CELL) - pBody->objMindForward.position();
	  pBody->objEyes.disable_steering();
	  pBody->objMindForward.start(remaining, pBody->objMindForward.speed(), 0, pBody->objMindForward.acceleration());
	  while (not pBody->objMindForward.is_finished()) {
	    if (pBody->objEyes.front_wall_sensor > (FRONT_REFERENCE - 150)) {
	      break;
	    }
	    delay(2);
	  }
	  if (pBody->objEyes.front_wall_present) {
	    while (pBody->objEyes.front_wall_sensor < FRONT_REFERENCE) {
	      pBody->objMindForward.start(10, 50, 0, 1000);
	      delay(2);
	    }
	  }
}

//***************************************************************************//

void Cerebellum::end_run() {

	// write code here what you need
	  bool has_wall = frontWall;
	  pBody->objEyes.disable_steering();
	  //log_status('T');
	  if( hsmp != NULL )
	  			  hsmp->turnBack();
	  else {
			float remaining = (FULL_CELL + HALF_CELL) - pBody->objMindForward.position();
			pBody->objMindForward.start(remaining, pBody->objMindForward.speed(), 30, pBody->objMindForward.acceleration());
			if (has_wall) {
			while (pBody->objEyes.get_front_sensor() < 850) {
			  delay(2);
			}
			} else {
			while (not pBody->objMindForward.is_finished()) {
			  delay(2);
			}
			}
			// Be sure robot has come to a halt.
			pBody->objMindForward.stop();

		    // Turn Back
			float angle   = TurnParms[A_turnBack].angle;
			float omega   = TurnParms[A_turnBack].omega;
			float alpha   = TurnParms[A_turnBack].alpha;

			spin_turn( angle, omega, alpha );
	  }
}


/**
 * Performs a turn. Regardless of whether the robot is moving or not
 *
 * The function is given three parameters
 *
 *  - angle  : positive is a left turn (deg)
 *  - omega  : angular velocity of middle phase (deg/s)
 *  - alpha  : angular acceleration of in/out phases (deg/s/s)
 *
 * If the robot is moving forward, it will execute a smooth, integrated
 * turn. The turn will only be repeatable if it is always performed at the
 * same forward speed.
 *
 * If the robot is stationary, it will execute an in-place spin turn.
 *
 * The parameter alpha will indirectly determine the turn radius. During
 * the accelerating phase, the angular velocity, will increase until it
 * reaches the value omega.
 * The minimum radius during the constant phase is
 *   radius = (speed/omega) * (180/PI)
 * The effective radius will be larger because it takes some time
 * for the rotation to accelerate and decelerate. The parameter alpha
 * controls that.
 *
 * Note that a real mouse may behave slightly different for left and
 * right turns and so the parameters for, say, a 90 degree left turn
 * may be slightly different to those for a 90 degree right turn.
 *
 * @brief execute an arbitrary in-place or smooth turn
 */
void Cerebellum::turn(float angle, float omega, float alpha) {
	// write code here what you need
	pBody->objMindRotation.reset();
	pBody->objMindRotation.start(angle, omega, 0, alpha);
	while (not pBody->objMindRotation.is_finished()) {
		pBody->objMouth.report_profile();
		delay(2);
	}
}

/**
 *
 * @brief turn in place. Force forward speed to zero
 */
void Cerebellum::spin_turn(float degrees, float speed, float acceleration) {

	// write code here what you need
	pBody->objMindForward.set_target_speed(0);
	while (pBody->objMindForward.speed() != 0) {
		delay(2);
	}
	turn(degrees, speed, acceleration);
};

void Cerebellum::turnSub(int mode) {
	// steeering off
	pBody->objEyes.disable_steering();

	float angle   = TurnParms[mode].angle;
	float omega   = TurnParms[mode].omega;
	float alpha   = TurnParms[mode].alpha;

	spin_turn( angle, omega, alpha );
}

void Cerebellum::turnLeft45(void) {
	ssd1306_printFixedN(0,16,"T Left 45 ", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->turnLeft45();
#else
	// write code here what you need
	turnSub(A_turnLeft45) ;
#endif
}

void Cerebellum::turnRight45(void) {
	ssd1306_printFixedN(0,16,"T Right45 ", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->turnRight45();
#else
	// write code here what you need
	turnSub(A_turnRight45) ;
#endif
}

void Cerebellum::turnLeft90(void) {
	ssd1306_printFixedN(0,16,"T Left 90 ", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->turnLeft90();
#else
	// write code here what you need
	turnSub(A_turnLeft90) ;
#endif
}

void Cerebellum::turnRight90(void) {
	ssd1306_printFixedN(0,16,"T Right90 ", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->turnRight90();
#else
	// write code here what you need
	turnSub(A_turnRight90) ;
#endif
}

void Cerebellum::turnBack(void) {
	ssd1306_printFixedN(0,16,"T Back    ", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->turnBack();
#else
	// write code here what you need
	turnSub(A_turnBack) ;
#endif
}

void Cerebellum::moveSub(int mode, short length){
	// steeering on
	pBody->objEyes.enable_steering();

	float distance     = TurnParms[mode].distance * length;
	float top_speed    = TurnParms[mode].top_speed;
	float end_speed    = TurnParms[mode].final_speed;
	float acceleration = TurnParms[mode].acceleration;

	pBody->objMindForward.start(distance, top_speed, end_speed, acceleration);
	while (not pBody->objMindForward.is_finished()) {
	//	pBody->objMouth.report_profile();
		delay(2);
	}
}

void Cerebellum::moveEdgeForward(short length) {
	ssd1306_printFixedN(0,16,"E Forward ", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->moveEdgeForward(length);
#else
	// write code here what you need
	moveSub(A_moveEdgeForward, length);
#endif
}

void Cerebellum::moveHalfForward(short length) {
	ssd1306_printFixedN(0,16,"H Forward ", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->moveHalfForward(length);
#else
	// write code here what you need
	moveSub(A_moveHalfForward, length);
#endif
}

void Cerebellum::moveFullForward(short length) {
	ssd1306_printFixedN(0,16,"F Forward ", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->moveFullForward(length);
#else
	// write code here what you need
	moveSub(A_moveFullForward, length);
#endif
}

void Cerebellum::smoothSub(int mode) {
	// steeering off
	  pBody->objEyes.disable_steering();

	  float angle   = TurnParms[mode].angle;
	  float omega   = TurnParms[mode].omega;
	  float alpha   = TurnParms[mode].alpha;
	  float run_in  = TurnParms[mode].run_in;
	  float run_out = TurnParms[mode].run_out;
	  float tspeed  = TurnParms[mode].top_speed;
	  float espeed  = TurnParms[mode].final_speed;
	  float accel   = TurnParms[mode].acceleration;

	  float distance = FULL_CELL + 10 + run_in - pBody->objMindForward.position();

	  if( pBody->objMindForward.speed() == 0 )
		  pBody->objMindForward.start(distance, tspeed, espeed, accel );
	  else
		  pBody->objMindForward.start(distance, pBody->objMindForward.speed(), espeed, accel );

	  while (not pBody->objMindForward.is_finished()) {
		//pBody->objMouth.report_profile();
	    if (pBody->objEyes.front_wall_sensor > FRONT_THRESHOLD) {
	    	pBody->objMindForward.set_state(CS_FINISHED);
	    }
	  }
	  pBody->objMindRotation.start(angle, omega, 0, alpha);
	  while (not pBody->objMindRotation.is_finished()) {
	    //pBody->objMouth.report_profile();
	      delay(2);

	  }
	  pBody->objMindForward.start(run_out, pBody->objMindForward.speed(), espeed, accel );
	  while (not pBody->objMindForward.is_finished()) {
		 // pBody->objMouth.report_profile();
	      delay(2);
	  }
	  pBody->objMindForward.set_position(FULL_CELL - SENSING_POSITION_GAP);
}

void Cerebellum::smoothLeft90(void) {
	ssd1306_printFixedN(0,16,"S L90", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->runLeft();
#else
	// write code here what you need
	smoothSub(A_smoothLeft90);
#endif
}

void Cerebellum::smoothRight90(void) {
	ssd1306_printFixedN(0,16,"S R90", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->runRight();
#else
	// write code here what you need
	smoothSub(A_smoothRight90);
#endif
}

void Cerebellum::smoothTurnBack(void) {
	ssd1306_printFixedN(0,16,"S BAK", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->turnBack();
#else
	// write code here what you need

	  bool has_wall = frontWall;

	  float angle   = TurnParms[A_smoothTurnBack].angle;
	  float omega   = TurnParms[A_smoothTurnBack].omega;
	  float alpha   = TurnParms[A_smoothTurnBack].alpha;
	  float tspeed  = TurnParms[A_smoothTurnBack].top_speed;
	  float espeed  = 0.0f; //TurnParms[A_smoothTurnBack].final_speed;
	  float accel   = TurnParms[A_smoothTurnBack].acceleration;

	  pBody->objEyes.disable_steering();

	  float remaining = (FULL_CELL + HALF_CELL) - pBody->objMindForward.position() ;

	  pBody->objMindForward.start(remaining, pBody->objMindForward.speed(), 30.0f, pBody->objMindForward.acceleration());
	  if (has_wall) {
	    while (pBody->objEyes.get_front_sensor() < FRONT_REFERENCE) {
	      delay(2);
	    }
	  } else {
	    while (not pBody->objMindForward.is_finished()) {
	      delay(2);
	    }
	  }
	  // Be sure robot has come to a halt.
	  pBody->objMindForward.stop();

	  spin_turn(angle, omega, alpha);

	  pBody->objMindForward.start(HALF_CELL - SENSING_POSITION_GAP, tspeed, espeed, accel); // ? 0.0f -> speed
	  while (not pBody->objMindForward.is_finished()) {
	    delay(2);
	  }

	  pBody->objMindForward.set_position(FULL_CELL  - SENSING_POSITION_GAP); // - remaining
#endif
}

void Cerebellum::smoothFullForward(short length) {
	ssd1306_printFixedN(0,16,"S FWD", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->moveFullForward(length);
#else
	// write code here what you need
	pBody->objEyes.enable_steering();

	float distance     = TurnParms[A_moveFullForward].distance * length - SENSING_POSITION_GAP;
	float top_speed    = TurnParms[A_moveFullForward].top_speed;
	float end_speed    = TurnParms[A_moveFullForward].final_speed;
	float acceleration = TurnParms[A_moveFullForward].acceleration;

	pBody->objMindForward.start(distance, top_speed, end_speed, acceleration);
	while (not pBody->objMindForward.is_finished()) {
		//pBody->objMouth.report_encoders();
		if (pBody->objEyes.front_wall_sensor > FRONT_THRESHOLD) {
			pBody->objMindForward.set_state(CS_FINISHED);
		}
	}
	pBody->objMindForward.set_position(FULL_CELL-SENSING_POSITION_GAP);
	// pBody->objMindForward.adjust_position(FULL_CELL-10);
	// wait_until_position(FULL_CELL - 10.0);

#endif
}

void Cerebellum::readyToGo(void) {
	ssd1306_printFixedN(0,16,"Ready", STYLE_NORMAL, FONT_SIZE_2X);
#if SIMULATION == 1
	hsmp->ackReset(); // reset screen
	hsmp->moveHalfForward(1);
#else
	// write code here what you need

	delay(500);

	pBody->objMindForward.start(BACK_WALL_TO_CENTER, SPEEDMAX_EXPLORE, SPEEDMAX_EXPLORE, EXPLORE_ACCELERATION);
	while (not pBody->objMindForward.is_finished()) {
		delay(2);
	}
	pBody->objMindForward.set_position(HALF_CELL);
	wait_until_position(FULL_CELL - SENSING_POSITION_GAP);

#endif
}




