/*
 * CDriveProfile.cpp
 *
 *  Created on: Nov 3, 2025
 *      Author: David(Yong eel) Lee
 *      Cited from     Author: Peter Harrison / ukmars
*/

#include <Mouse.h>
#include <BodyConfig.h>

#include <CDriveProfile.h>

CDriveProfile::CDriveProfile() {
	// TODO Auto-generated constructor stub

}

CDriveProfile::~CDriveProfile() {
	// TODO Auto-generated destructor stub
}

void CDriveProfile::init() {

	// write code here what you need

}

void CDriveProfile::reset() {

	// write code here what you need
	//   ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
	    m_position = 0;
	    m_speed = 0;
	    m_target_speed = 0;
	    m_state = CS_IDLE;
	//  }

}
// update is called from within systick and shoul dbe safe from interrupts
void CDriveProfile::update() {

	// write code here what you need
	  if (m_state == CS_IDLE) {
	    return;
	  }
	  float delta_v = m_acceleration * LOOP_INTERVAL;
	  float remaining = fabsf(m_final_position) - fabsf(m_position);
	  if (m_state == CS_ACCELERATING) {
	    if (remaining < get_braking_distance()) {
	      m_state = CS_BRAKING;
	      if (m_final_speed == 0) {
	        m_target_speed = m_sign * 5.0f;
	      } else {
	        m_target_speed = m_final_speed;
	      };
	    }
	  }
	  // try to reach the target speed
	  if (m_speed < m_target_speed) {
	    m_speed += delta_v;
	    if (m_speed > m_target_speed) {
	      m_speed = m_target_speed;
	    }
	  }
	  if (m_speed > m_target_speed) {
	    m_speed -= delta_v;
	    if (m_speed < m_target_speed) {
	      m_speed = m_target_speed;
	    }
	  }
	  // increment the position
	  m_position += m_speed * LOOP_INTERVAL;
	  if (m_state != CS_FINISHED && remaining < 0.125) {
	    m_state = CS_FINISHED;
	    m_target_speed = m_final_speed;
	  }

}

// not used?
void CDriveProfile::clear_counters() {
//   ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    m_position = 0;
//   }
}

bool CDriveProfile::is_finished() { return m_state == CS_FINISHED; }

void CDriveProfile::start(float distance, float top_speed, float final_speed, float acceleration) {
  m_sign = (distance < 0) ? -1 : +1;
  if (distance < 0) {
    distance = -distance;
  }
  if (distance < 1.0) {
    m_state = CS_FINISHED;
    return;
  }
  if (final_speed > top_speed) {
    final_speed = top_speed;
  }

  m_position = 0;
  m_final_position = distance;
  m_target_speed = m_sign * fabsf(top_speed);
  m_final_speed = m_sign * fabsf(final_speed);
  m_acceleration = fabsf(acceleration);
  if (m_acceleration >= 1) {
    m_one_over_acc = 1.0f / m_acceleration;
  } else {
    m_one_over_acc = 1.0;
  }
  m_state = CS_ACCELERATING;
}

void CDriveProfile::stop() {
//   ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    m_target_speed = 0;
//   }
  finish();
}

void CDriveProfile::finish() {
//   ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    m_speed = m_target_speed;
    m_state = CS_FINISHED;
//   }
}

void CDriveProfile::set_state(ProfileState state) { m_state = state; }

float CDriveProfile::get_braking_distance() {
  return fabsf(m_speed * m_speed - m_final_speed * m_final_speed) * 0.5 * m_one_over_acc;
}

float CDriveProfile::position() {
  float pos;
//  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos = m_position;
//  }
  return pos;
}

float CDriveProfile::speed() {
  float speed;
//   ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    speed = m_speed;
//   }
  return speed;
}

float CDriveProfile::increment() {
  float inc;
//   ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    inc = m_speed * LOOP_INTERVAL;
//   }
  return inc;
}

float CDriveProfile::acceleration() {
  float acc;
//   ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    acc = m_acceleration;
//   }
  return acc;
}

void CDriveProfile::set_speed(float speed) {
//  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    m_speed = speed;
//  }
}
void CDriveProfile::set_target_speed(float speed) {
//  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    m_target_speed = speed;
//  }
}

// normally only used to alter position for forward error correction
void CDriveProfile::adjust_position(float adjustment) {
//  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
	 m_position += adjustment;
//  }
}

void CDriveProfile::set_position(float position) {
//  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
	 m_position = position;
//  }
}
