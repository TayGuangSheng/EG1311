#include <Servo.h>

// Constants
int SERVO_PIN = 9;
int MOTOR_GROUND =7;
int MOTOR_HIGH = 2;
int ECHO_PIN = 11;
int TRIG_PIN = 10;
float SPEED_OF_SOUND = 0.0345;
Servo servo;

// Flag
bool reverse = false;

// Changable variable (adjust through testing)
int distance = 8;
int angle = 130;

 
void setup() { 
  pinMode(MOTOR_GROUND, OUTPUT);
  pinMode(MOTOR_HIGH, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  servo.attach(SERVO_PIN, 600, 2400);
  servo.write(0);
} 

void loop() { 
  // Check if the robot is going back or forward
  if(reverse){
    digitalWrite(MOTOR_HIGH, LOW); 
    digitalWrite(MOTOR_GROUND, HIGH); 
  } else {
    digitalWrite(MOTOR_HIGH, HIGH); 
    digitalWrite(MOTOR_GROUND, LOW); 
  }

  // Measure the distance
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIG_PIN, LOW);
  int microsecs = pulseIn(ECHO_PIN, HIGH); 
  float cms = microsecs * SPEED_OF_SOUND / 2; 

  // Print out distance (delete in final product)
  Serial.println(cms); 

  /** 
  Operation when the robot reach the wall.
  The flag "reverse" so that this only triggered once, and
  to indicate that the robot start going backward 
  */
  if(cms < distance && !reverse){
    reverse = true;

    // Stop before the wall
    digitalWrite(MOTOR_HIGH, LOW); 
    digitalWrite(MOTOR_GROUND, LOW);

    // Throwing the ball
    servo.write(0);
    delay(200);
    servo.write(angle);
    delay(1000);
    servo.write(0);
  }
}