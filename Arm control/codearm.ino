#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 100
#define SERVOMAX 500

#define BASE_SERVO 0
#define SHOULDER_SERVO 1
#define ELBOW_SERVO 2
#define WRIST_SERVO 4
#define GRIPPER_SERVO 5

int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void moveServoSmooth(int channel, int fromDeg, int toDeg, int delayTime = 30) {
  if (fromDeg < toDeg) {
    for (int angle = fromDeg; angle <= toDeg; angle++) {
      pwm.setPWM(channel, 0, angleToPulse(angle));
      delay(delayTime);
    }
  } else {
    for (int angle = fromDeg; angle >= toDeg; angle--) {
      pwm.setPWM(channel, 0, angleToPulse(angle));
      delay(delayTime);
    }
  }
}

void setup() {
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(500);

  moveServoSmooth(BASE_SERVO, 0, 30);
  delay(1000);

  moveServoSmooth(SHOULDER_SERVO, 0, 28);
  delay(1000);

  moveServoSmooth(GRIPPER_SERVO, 0, 30);
  delay(1000);

  moveServoSmooth(GRIPPER_SERVO, 30, 0);
  delay(1000);

  moveServoSmooth(SHOULDER_SERVO, 28, 0);
  delay(1000);

  moveServoSmooth(WRIST_SERVO, 0, 20);
  delay(1000);

  moveServoSmooth(BASE_SERVO, 30, 0);

  moveServoSmooth(ELBOW_SERVO, 0, 15);
  delay(1000);

  moveServoSmooth(WRIST_SERVO, 20, 0);
  delay(1000);

  moveServoSmooth(GRIPPER_SERVO, 0, 30);
  delay(1000);
}

void loop() {
}
