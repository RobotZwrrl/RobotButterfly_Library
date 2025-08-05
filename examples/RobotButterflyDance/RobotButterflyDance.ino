/* Robot Butterfly Dance
 * --------------------------
 * Respond to the IMU poses with different
 * light patterns and servo animations!
 * when at rest, flap the wings every 20s.
 */

#include <RobotButterfly.h>

RobotButterfly robotbutterfly;

void imuPoseChangeCallback(uint8_t p);
long last_movement_rest = 0;


void setup() {
  Serial.begin(9600);
  robotbutterfly = RobotButterfly();
  
  robotbutterfly.init(true, false);

  robotbutterfly.onPoseChangeCallback_client = imuPoseChangeCallback;

  pinMode(LED_HEARTBEAT_PIN, OUTPUT);
  pinMode(LED_COMMS_PIN, OUTPUT);

  setAnimations();
  setTaskPriorities();

  Serial << "Welcome to Robot Butterfly!" << endl;
  playSound(SOUND_ALERT_STARTUP);

}

void loop() {
  
  robotbutterfly.update();

  if(getIMUState() != IMU_ACTIVE) {
    digitalWrite(LED_HEARTBEAT_PIN, LOW);
    digitalWrite(LED_COMMS_PIN, LOW);
  } else {
    digitalWrite(LED_HEARTBEAT_PIN, HIGH);
    digitalWrite(LED_COMMS_PIN, HIGH);
  }

  if(getIMUPose() == IMU_Pose_Home && getIMUState() == IMU_ACTIVE) {
    
    if(millis()-last_movement_rest >= 20000 && millis() > 10000) {
      
      setServoAnim(&servo_animation_alert, SERVO_ANIM_FLUTTER, SERVO_ANIM_ALERT);
      setServoAnimFlutterWings(&servo_animation_alert, SERVO_ANIM_FLUTTER_WINGS_BOTH_UP);
      setServoAnimDuration(&servo_animation_alert, 3000);
      startServoAnim(&servo_animation_alert);
      last_movement_rest = millis();

    }
  }

}


void setAnimations() {

  // servo animation home
  setServoAnim(&servo_animation_home, SERVO_ANIM_POSITION, SERVO_ANIM_HOME);
  setServoAnimPositionLeft(&servo_animation_home, SERVO_ANIM_POSITION_UP);
  setServoAnimPositionRight(&servo_animation_home, SERVO_ANIM_POSITION_UP);
  startServoAnim(&servo_animation_home);

  // servo animation alert
  setServoAnim(&servo_animation_alert, SERVO_ANIM_NONE, SERVO_ANIM_ALERT);
  startServoAnim(&servo_animation_alert);

  // neo animation home
  setNeoAnim(&neo_animation_home, NEO_ANIM_SQUIGGLE, NEO_ANIM_HOME);
  setNeoAnimColours(&neo_animation_home, NEO_GREEN, NEO_PURPLE);
  setNeoAnimDuration(&neo_animation_home, 500);
  startNeoAnim(&neo_animation_home);

  // neo animation alert
  setNeoAnim(&neo_animation_alert, NEO_ANIM_NONE, NEO_ANIM_ALERT);
  startNeoAnim(&neo_animation_alert);

}


void setTaskPriorities() {
  setButtonsTaskPriority(PRIORITY_BUTTONS_LOW);
  setIMUTaskPriority(PRIORITY_IMU_MID);
  setNeoAnimationTaskPriority(PRIORITY_NEOANIM_MID);
  setProximityTaskPriority(tskIDLE_PRIORITY);
  setSensorsTaskPriority(tskIDLE_PRIORITY);
  setServoAnimationTaskPriority(PRIORITY_SERVOANIM_HIGH);
  setSoundTaskPriority(PRIORITY_SOUND_MID);
}

