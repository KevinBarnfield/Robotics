/**Platform Robot
 * @author Kevin Barnfield
 * @date Sept 21, 2017
 * @brief Arduino code for platform robot.
 */

//Testing the DC Motors
//Define Pins
//Motor A
int enableA = 10;
int pinA1 = 2;
int pinA2 = 3;

//Motor B
int enableB = 9;
int pinB1 = 5;
int pinB2 = 4;
//define time for run
// in milliseconds
int running = 10000; //10 secons
boolean play;

void setup() {
    Serial.begin (9600);
    //configure pin modes
    pinMode (enableA, OUTPUT);
    pinMode (pinA1, OUTPUT);
    pinMode (pinA2, OUTPUT); 
    
    pinMode (enableB, OUTPUT);
    pinMode (pinB1, OUTPUT);
    pinMode (pinB2, OUTPUT); 
    
    play = true;
}

//Defining functions so it's more easy
//motor functions
void motorAforward() {
    digitalWrite (pinA1, HIGH);
    digitalWrite (pinA2, LOW);
}

void motorBforward() {
    digitalWrite (pinB1, LOW);
    digitalWrite (pinB2, HIGH);
}

void motorAbackward() {
    digitalWrite (pinA1, LOW);
    digitalWrite (pinA2, HIGH);
}

void motorBbackward() {
    digitalWrite (pinB1, HIGH);
    digitalWrite (pinB2, LOW);
}

void motorAstop() {
    digitalWrite (pinA1, HIGH);
    digitalWrite (pinA2, HIGH);
}

void motorBstop() {
    digitalWrite (pinB1, HIGH);
    digitalWrite (pinB2, HIGH);
}
void motorAcoast() {
    digitalWrite (pinA1, LOW);
    digitalWrite (pinA2, LOW);
}

void motorBcoast() {
    digitalWrite (pinB1, LOW);
    digitalWrite (pinB2, LOW);
}

void motorAon() {
    digitalWrite (enableA, HIGH);
}

void motorBon() {
    digitalWrite (enableB, HIGH);
}

void motorAoff() {
    digitalWrite (enableA, LOW);
}

void motorBoff() {
    digitalWrite (enableB, LOW);
}

// Movement functions
void forward (int duration) {
    motorAforward();
    motorBforward();
    delay (duration);
}

void backward (int duration) {
    motorAbackward();
    motorBbackward();
    delay (duration);
}

void left (int duration) {
    motorAbackward();
    motorBforward();
    delay (duration);
}

void right (int duration) {
    motorAforward();
    motorBbackward();
    delay (duration);
}

void coast (int duration) {
    motorAcoast();
    motorBcoast();
    delay (duration);
}

void breakRobot (int duration) {
    motorAstop();
    motorBstop();
    delay (duration);
}

void disableMotors() {
    motorAoff();
    motorBoff();
}

void enableMotors() {
    motorAon();
    motorBon();
}

void loop() {
    enableMotors();

    forward (4000);
}
