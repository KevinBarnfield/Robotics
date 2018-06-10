// Connor Palin - Extended by Kevin Barnfield and Spencer Ploeger
// Gryphon Robotics IGVC Code
//********************************************************************************************

#include <Servo.h>
#include <PingSensor.h>

//======== Variable Definitions =============

// FlySky Variables
#define pulseLong 1000
#define pulseShort 1990

#define d_stick A9            // drive
#define t_stick A8            // turn
#define auto_switch A12       // for auto on off
#define motorPin_L 50         // motor pins
#define motorPin_R 52         // motor pins

long d_stick_in;              // input from receiver
long t_stick_in;              // input from receiver
long auto_switch_in;          // input from receiver

// Motors
Servo L_motor;
Servo R_motor;

#define motorLimitH 120
#define motorLimitL 67

long drive;                         // -100 to 100 drive
long turn;                          // -100 to 100 rotate
long L_motor_out;
long R_motor_out;

// Ping Sensors
PingSensor A;                       // A: trigger 48  echo 46
PingSensor B;                       // B: trigger 53  echo 51
PingSensor C;                       // C: trigger 49 echo 47
PingSensor D;                       // D: trigger 29 echo 27

//=========== FUNCTIONS ================
void goForward(int s, int duration) {
  int L = map(-1 * s, -100, 100, motorLimitL, motorLimitH);
  int R = map(s, -100, 100, motorLimitL, motorLimitH);

  L_motor.write(L);
  R_motor.write(R);

  delay(duration);
}

void goRight(int s, int duration) {
  int L = map(-1 * s, -100, 100, motorLimitL, motorLimitH);
  int R = map(-1 * s, -100, 100, motorLimitL, motorLimitH);

  L_motor.write(L);
  R_motor.write(R);

  delay(duration);
}

void goLeft(int s, int duration) {
  int L = map(s, -100, 100, motorLimitL, motorLimitH);
  int R = map(s, -100, 100, motorLimitL, motorLimitH);

  L_motor.write(L);
  R_motor.write(R);

  delay(duration);
}

void stopMotors(int duration) {
  int L = map(0, -100, 100, motorLimitL, motorLimitH);
  int R = map(0, -100, 100, motorLimitL, motorLimitH);

  L_motor.write(L);
  R_motor.write(R);

  delay(duration);
}

//=========== SETUP ============
void setup() {

  //Attaching motors to pins
  L_motor.attach(motorPin_L);
  R_motor.attach(motorPin_R);

  // Attach pings to pins
  A.attach(46, 48);                 // A: trig 48 echo 46
  B.attach(51, 53);                 // B: trig 51 echo 53
  C.attach(47, 49);                 // C: trig 47 echo 49
  D.attach(27, 29);                 // D: trig 27 echo 29

  //Serial Coms Start
  Serial.begin(9600);
}

//=========== LOOP =============
void loop() {
  // Receive input from switch D on Flysky to determine mode
  auto_switch_in = pulseIn(auto_switch, HIGH, 30000);

  if (auto_switch_in < 1400) {                          // MANUAL MODE
    Serial.println("DRIVE MODE");

    // Input from drive/turn channels
    d_stick_in = pulseIn(d_stick, HIGH, 30000);
    t_stick_in = pulseIn(t_stick, HIGH, 30000);

    // Map inputs from channels to -100 to 100
    drive = (map(d_stick_in, pulseShort, pulseLong, -100, 100)) * -1;
    turn = (map(t_stick_in, pulseShort, pulseLong, -100, 100)) * 0.5;

    // If either channel goes to zero, stop the robot
    if (d_stick_in == 0 || t_stick_in == 0) {
      d_stick_in = 0;
      t_stick_in = 0;
      drive = 0;
      turn = 0;
    }

    // Calculate the speed of each motor
    L_motor_out = -1 * drive - turn;
    R_motor_out = drive - turn + 0;

    // Remap values to motor limits [67, 120]
    L_motor_out   = map(L_motor_out, -100, 100, motorLimitL, motorLimitH);
    R_motor_out   = map(R_motor_out, -100, 100, motorLimitL, motorLimitH);

    // Write values to each motor
    L_motor.write(L_motor_out);
    R_motor.write(R_motor_out);

    delay(10);
  } else if (auto_switch_in >= 1400) {              // AUTONOMOUS MODE
    Serial.println("AUTO MODE");
    
    Serial.print("A: ");
    Serial.print(A.getDist());
    Serial.print(" B: ");
    Serial.print(B.getDist());
    Serial.print(" C: ");
    Serial.print(C.getDist());
    Serial.print(" D: ");
    Serial.println(D.getDist());
//    // Algorithm
//    if (A.getDist() < 30 || B.getDist() < 30 || C.getDist() < 30 || D.getDist() < 30) {
//      //stopMotors(10);
//    } else if (A.getDist() < 100) {
//      goRight(40, 100);
//    } else if (D.getDist() < 100) {
//      goLeft(40, 10);
//    } else if (B.getDist() < 50 || C.getDist() < 50) {
//      if (A.getDist() < D.getDist()) {
//        goRight(40, 10);
//      } else if (D.getDist() < A.getDist()) {
//        goLeft(40, 10);
//      } else {
//        goForward(-40, 100);
//      }
//      stopMotors(10);
//    } else {
//      goForward(40, 10);
//    }
  }
}
