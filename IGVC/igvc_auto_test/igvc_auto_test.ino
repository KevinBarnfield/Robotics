// Connor Palin
// Gryphon Robotics IGVC Code
//********************************************************************************************

#include <Servo.h>
//Variable Definitions
#define pulseLong 1000
#define pulseShort 1990
#define motorLimitH 120
#define motorLimitL 67

#define d_stick A9  //drive
#define t_stick A8   // turn
#define auto_switch A12 //for auto on off
#define motorPin_L 50  //motor pins
#define motorPin_R 52  //motor pins

// A: trigger 48  echo 46
// B: trigger 53  echo 51
// C: trigger 49 echo 47
// D: trigger 29 echo 27

//SENSOR A (Left)
#define echoA 46 // Echo Pin for sensor A
#define trigA 48 // Trigger Pin for sensor A

#define echoB 51 // Echo Pin for sensor A
#define trigB 53 // Trigger Pin for sensor A

#define echoC 47 // Echo Pin for sensor B
#define trigC 49 // Trigger Pin for sensor C

#define echoD 27 // Echo Pin for sensor B
#define trigD 29 // Trigger Pin for sensor C

long durationA, distanceA; // Duration and distace varialbes for sensorA
long durationB, distanceB; // Duration and distace varialbes for sensorB
long durationC, distanceC; // Duration and distace varialbes for sensorC
long durationD, distanceD; // Duration and distace varialbes for sensorC



int maximumRange = 200; // Maximum range for all sensors
int minimumRange = 0; // Minimum range for all sensors

//averaging variables
const int numReadingsA = 3;
int readingsA[numReadingsA];      // the readings from the analog input
int readIndexA = 0;              // the index of the current reading
int totalA = 0;                  // the running total
int averageA = 0;


const int numReadingsB = 3;
int readingsB[numReadingsB];      // the readings from the analog input
int readIndexB = 0;              // the index of the current reading
int totalB = 0;                  // the running total
int averageB = 0;


const int numReadingsC = 3;
int readingsC[numReadingsC];      // the readings from the analog input
int readIndexC = 0;              // the index of the current reading
int totalC = 0;                  // the running total
int averageC = 0;


const int numReadingsD = 3;
int readingsD[numReadingsD];      // the readings from the analog input
int readIndexD = 0;              // the index of the current reading
int totalD = 0;                  // the running total
int averageD = 0;

Servo L_motor;  // motor objects
Servo R_motor;

long d_stick_in;   //input from reciever
long t_stick_in;   //input from reciever
long auto_switch_in; //inpit from reciever
long drive;        // -100 to 100 drive
long turn;       // -100 to 100 rotate
long L_motor_out;
long R_motor_out;

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

void setup() {

  pinMode(trigA, OUTPUT);
  pinMode(echoA, INPUT);


  pinMode(trigB, OUTPUT);
  pinMode(echoB, INPUT);


  pinMode(trigC, OUTPUT);
  pinMode(echoC, INPUT);

  pinMode(trigD, OUTPUT);
  pinMode(echoD, INPUT);

  //Attaching objects to pins
  L_motor.attach(motorPin_L);
  R_motor.attach(motorPin_R);
  //Serial Coms Start
  Serial.begin(9600);

  //reset smoothing arrays
  for (int thisReadingA = 0; thisReadingA < numReadingsA; thisReadingA++) {
    readingsA[thisReadingA] = 0;
  }

  for (int thisReadingB = 0; thisReadingB < numReadingsB; thisReadingB++) {
    readingsB[thisReadingB] = 0;
  }

  for (int thisReadingC = 0; thisReadingC < numReadingsC; thisReadingC++) {
    readingsC[thisReadingC] = 0;
  }

  for (int thisReadingD = 0; thisReadingD < numReadingsD; thisReadingD++) {
    readingsD[thisReadingD] = 0;
  }

}

int getDistA()
{
  digitalWrite(trigA, LOW);
  delayMicroseconds(2);

  digitalWrite(trigA, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigA, LOW);
  durationA = pulseIn(echoA, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distanceA = durationA / 58.2;


  // subtract the last reading:
  totalA = totalA - readingsA[readIndexA];
  // read from the sensor:
  readingsA[readIndexA] = distanceA;
  // add the reading to the total:
  totalA = totalA + readingsA[readIndexA];
  // advance to the next position in the array:
  readIndexA = readIndexA + 1;

  // if we're at the end of the array...
  if (readIndexA >= numReadingsA) {
    // ...wrap around to the beginning:
    readIndexA = 0;
  }

  // calculate the average:
  averageA = totalA / numReadingsA;


  return averageA;
}

int getDistB()
{
  digitalWrite(trigB, LOW);
  delayMicroseconds(2);

  digitalWrite(trigB, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigB, LOW);
  durationB = pulseIn(echoB, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distanceB = durationB / 58.2;

  // subtract the last reading:
  totalB = totalB - readingsB[readIndexB];
  // read from the sensor:
  readingsB[readIndexB] = distanceB;
  // add the reading to the total:
  totalB = totalB + readingsB[readIndexB];
  // advance to the next position in the array:
  readIndexB = readIndexB + 1;

  // if we're at the end of the array...
  if (readIndexB >= numReadingsB) {
    // ...wrap around to the beginning:
    readIndexB = 0;
  }

  // calculate the average:
  averageB = totalB / numReadingsB;


  return averageB;
}

int getDistC()
{
  digitalWrite(trigC, LOW);
  delayMicroseconds(2);

  digitalWrite(trigC, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigC, LOW);
  durationC = pulseIn(echoC, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distanceC = durationC / 58.2;

  // subtract the last reading:
  totalC = totalC - readingsC[readIndexC];
  // read from the sensor:
  readingsC[readIndexC] = distanceC;
  // add the reading to the total:
  totalC = totalC + readingsC[readIndexC];
  // advance to the next position in the array:
  readIndexC = readIndexC + 1;

  // if we're at the end of the array...
  if (readIndexC >= numReadingsC) {
    // ...wrap around to the beginning:
    readIndexC = 0;
  }

  // calculate the average:
  averageC = totalC / numReadingsC;


  return averageC;
}

int getDistD()
{
  digitalWrite(trigD, LOW);
  delayMicroseconds(2);

  digitalWrite(trigD, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigD, LOW);
  durationD = pulseIn(echoD, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distanceD = durationD / 58.2;

  // subtract the last reading:
  totalD = totalD - readingsD[readIndexD];
  // read from the sensor:
  readingsD[readIndexD] = distanceD;
  // add the reading to the total:
  totalD = totalD + readingsD[readIndexD];
  // advance to the next position in the array:
  readIndexD = readIndexD + 1;

  // if we're at the end of the array...
  if (readIndexD >= numReadingsD) {
    // ...wrap around to the beginning:
    readIndexD = 0;
  }

  // calculate the average:
  averageD = totalD / numReadingsD;


  return averageD;
}


void loop() {

  auto_switch_in = pulseIn(auto_switch, HIGH, 30000);

  if (auto_switch_in < 1400) //drive mode
  {

    // put your main code here, to run repeatedly:
    d_stick_in = pulseIn(d_stick, HIGH, 30000);
    t_stick_in = pulseIn(t_stick, HIGH, 30000);

    drive = (map(d_stick_in, pulseShort, pulseLong, -100, 100)) * -1;
    turn = (map(t_stick_in, pulseShort, pulseLong, -100, 100)) * 0.5;

    if (d_stick_in == 0 || t_stick_in == 0) {
      d_stick_in = 0;
      t_stick_in = 0;
      drive = 0;
      turn = 0;
    }

    L_motor_out = -1 * drive - turn;
    R_motor_out = drive - turn + 0;

    //              Serial.println("L_motor");
    //              Serial.println(L_motor_out);
    //              Serial.println("R_motor");
    //              Serial.println(R_motor_out);

    L_motor_out   = map(L_motor_out, -100, 100, motorLimitL, motorLimitH);
    R_motor_out   = map(R_motor_out, -100, 100, motorLimitL, motorLimitH);

    L_motor.write(L_motor_out);
    R_motor.write(R_motor_out);

    Serial.print("Left: ");
    Serial.print(L_motor_out);
    Serial.print("      Right: ");
    Serial.println(R_motor_out);

    //              Serial.println("drive");
    //              Serial.println(drive);
    //              Serial.println("Turn");
    //              Serial.println(turn);
    //              Serial.println("drive stick");
    //              Serial.println(d_stick_in);
    //              Serial.println("Turn stick");
    //              Serial.println(t_stick_in);


    Serial.println("Drive mode");
    delay(10);

  }
  else if (auto_switch_in >= 1400) //auto mode
  {
    // Serial.println("Auto mode");
    //    if (getDistA() < 30 || getDistB() < 30 || getDistC() < 30 || getDistD() < 30) {
    //        //stopMotors(10);
    //    } else if (getDistA() < 100) {
    //        goRight(40, 100);
    //    } else if (getDistD() < 100) {
    //        goLeft(40, 10);
    //    } else if (getDistB() < 50 || getDistC() < 50) {
    //        if (getDistA() < getDistD()) {
    //            goRight(40, 10);
    //        } else if (getDistD() < getDistA()) {
    //            goLeft(40, 10);
    //        } else {
    //            goForward(-40, 100);
    //        }
    //        stopMotors(10);
    //    } else {
    //        goForward(40, 10);
    //    }


    if (getDistB() < 90)
    {
      stopMotors(20);
      goForward(-40, 1000);
      goRight(40, 500);
    }
    if (getDistC() < 90)
    {
      stopMotors(20);
      goForward(-40, 1000);
      goLeft(40, 500);
    }
    if (getDistA() < 120)
    {
      goRight(40, 300);
    }
    if (getDistD() < 120)
    {
      goLeft(40, 300);
    }


    goForward(40, 10);
  }
}

