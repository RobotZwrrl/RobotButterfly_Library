void imuPoseChangeCallback(uint8_t p) {

  if(getIMUState() != IMU_ACTIVE) {
    Serial << "IMU not active yet" << endl;
    return;
  }

  switch(p) {
    case IMU_Pose_Tilt_L: {

      Serial << "tilt left!" << endl;

      setServoAnim(&servo_animation_alert, SERVO_ANIM_FLUTTER, SERVO_ANIM_ALERT);
      setServoAnimFlutterWings(&servo_animation_alert, SERVO_ANIM_FLUTTER_WINGS_LEFT_HOME);
      setServoAnimFlutterPos(&servo_animation_alert, SERVO_ANIM_FLUTTER_POS_UP);
      setServoAnimSpeed(&servo_animation_alert, 200);
      setServoAnimDuration(&servo_animation_alert, 2000);
      startServoAnim(&servo_animation_alert);

      setNeoAnim(&neo_animation_alert, NEO_ANIM_SPRINKLE, NEO_ANIM_ALERT);
      setNeoAnimColours(&neo_animation_alert, NEO_GREEN, NEO_WHITE);
      setNeoAnimSpeed(&neo_animation_alert, 100);
      setNeoAnimDuration(&neo_animation_alert, 2000);
      startNeoAnim(&neo_animation_alert);

      playSound(SOUND_SMELL_WILDFLOWER);

    }
    break;
    case IMU_Pose_Tilt_R: {

      Serial << "tilt right!" << endl;

      setServoAnim(&servo_animation_alert, SERVO_ANIM_FLUTTER, SERVO_ANIM_ALERT);
      setServoAnimFlutterWings(&servo_animation_alert, SERVO_ANIM_FLUTTER_WINGS_RIGHT_HOME);
      setServoAnimFlutterPos(&servo_animation_alert, SERVO_ANIM_FLUTTER_POS_UP);
      setServoAnimSpeed(&servo_animation_alert, 200);
      setServoAnimDuration(&servo_animation_alert, 2000);
      startServoAnim(&servo_animation_alert);

      setNeoAnim(&neo_animation_alert, NEO_ANIM_SPRINKLE, NEO_ANIM_ALERT);
      setNeoAnimColours(&neo_animation_alert, NEO_BLUE, NEO_WHITE);
      setNeoAnimSpeed(&neo_animation_alert, 100);
      setNeoAnimDuration(&neo_animation_alert, 2000);
      startNeoAnim(&neo_animation_alert);

      playSound(SOUND_SMELL_DAISY);

    }
    break;
  }

}

