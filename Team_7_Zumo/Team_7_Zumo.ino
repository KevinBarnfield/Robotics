/*  Zumo Bot Competition
 *  Team 7
 */

#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

#define LED 13
#define pingPin 7
#define QTR_THRESHOLD 1500

#define FORWARD_SPEED 100
#define REVERSE_SPEED -250
#define TURN_SPEED 250

#define REVERSE_DURATION 500
#define TURN_DURATION 500

#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
 
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

/* Functions */
long distanceInches() {
  // long duration, inches;
  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  // duration = pulseIn(pingPin, HIGH);
  
  return (pulseIn(pingPin, HIGH) / 74 / 2);
}

void waitForButtonAndCountDown()
{
  digitalWrite(LED, HIGH);
  button.waitForButton();
  digitalWrite(LED, LOW);
  delay(5000);
}

/* Setup */
void setup() {
  Serial.begin(9600);
  pinMode(LED, HIGH);
  waitForButtonAndCountDown();
}

/* Main Loop */
void loop() {
  if (button.isPressed()) {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }

  sensors.read(sensor_values);

  if (sensor_values[0] < QTR_THRESHOLD) {
    // if leftmost sensor detects line,  reverse and turn to the right
    motors.setSpeeds(0, 0);
    delay(500);
    
    motors.setSpeeds(REVERSE_SPEED, REVERSE_SPEED);
    delay(REVERSE_DURATION);

    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);

  } else if (sensor_values[5] < QTR_THRESHOLD) { 
    motors.setSpeeds(0, 0);
    delay(500);
    
    // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(REVERSE_SPEED, REVERSE_SPEED);
    delay(REVERSE_DURATION);

    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);

  } else {
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    /*
    while (distanceInches() > 25){
      motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    }

    sensors.read(sensor_values);
    while (sensor_values[5] > QTR_THRESHOLD || sensor_values[0] > QTR_THRESHOLD) {
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
      sensors.read(sensor_values);
    }
    
    if (distanceInches() > 25){
      motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    }
    else {
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
      delay(500);
    }
    */
  }
}
