//
//        FRONT of igvc
//      ================
//      A     B C      D
//      ||             ||
//      ||             ||
//      ||             ||
//
//             {}

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
const int numReadingsA = 10;
int readingsA[numReadingsA];      // the readings from the analog input
int readIndexA = 0;              // the index of the current reading
int totalA = 0;                  // the running total
int averageA = 0;


const int numReadingsB = 10;
int readingsB[numReadingsB];      // the readings from the analog input
int readIndexB = 0;              // the index of the current reading
int totalB = 0;                  // the running total
int averageB = 0;


const int numReadingsC = 10;
int readingsC[numReadingsC];      // the readings from the analog input
int readIndexC = 0;              // the index of the current reading
int totalC = 0;                  // the running total
int averageC = 0;


const int numReadingsD = 10;
int readingsD[numReadingsD];      // the readings from the analog input
int readIndexD = 0;              // the index of the current reading
int totalD = 0;                  // the running total
int averageD = 0;

void setup() {
  pinMode(trigA, OUTPUT);
  pinMode(echoA, INPUT);


  pinMode(trigB, OUTPUT);
  pinMode(echoB, INPUT);


  pinMode(trigC, OUTPUT);
  pinMode(echoC, INPUT);

  pinMode(trigD, OUTPUT);
  pinMode(echoD, INPUT);
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
  Serial.print("A: ");
  Serial.print(getDistA());
  Serial.print("   B: ");
  Serial.print(getDistB());
  Serial.print("   C: ");
  Serial.print(getDistC());
  Serial.print("   D: ");
  Serial.print(getDistD());

  Serial.println("");


  delay(10);

}
