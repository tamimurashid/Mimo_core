#include <AFMotor.h>

AF_DCMotor left_forward(1);
AF_DCMotor left_backward(4);
AF_DCMotor right_forward(3);
AF_DCMotor right_backward(2);
void setup() {
  Serial.begin(9600);
  int max_speed = 255;
  // Set the speed of both motors
  left_forward.setSpeed(max_speed);
  left_backward.setSpeed(max_speed);
  right_forward.setSpeed(max_speed);
  right_backward.setSpeed(max_speed);

  // Initialize the motors
  left_forward.run(RELEASE);
  left_backward.run(RELEASE);
  right_forward.run(RELEASE);
  right_backward.run(RELEASE);
  // put your setup code here, to run once:

}

void loop() {
     left_forward.run(FORWARD);
     left_backward.run(FORWARD);
     right_forward.run(FORWARD);
     right_backward.run(FORWARD);
  // put your main code here, to run repeatedly:

}
