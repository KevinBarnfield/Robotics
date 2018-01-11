#include <Servo.h>

// Channels
#define CH1 A8  // Rotate Left/Right was A8
#define CH2 A9
#define CH3 A10 // Forward Reverse was A10
#define CH4 A11 // Strafe Left/Right was A11
#define CH5 A12 // Arm
#define CH6 A13 // Claw

// Motors (RF = Right Front)
#define RF 36
#define RB 38
#define LF 40
#define LB 42

Servo rightFront;
Servo rightBack;
Servo leftFront;
Servo leftBack;

#define motorLimitH 110
#define motorLimitL 70

// Arm
#define ARM 44
#define CLAW 46

Servo arm;
Servo claw;

// Pulse In from Controller
long pulseRotate;
long pulseDrive;
long pulseStrafe;
long pulseArm;
long pulseClaw;

long drive;
long strafe;
long rotate;
long lift;
long pinch;

long front_left  = 0;
long rear_left = 0;
long front_right = 0;
long rear_right  = 0;

#define pulseLong 900
#define pulseShort 2000

void setup() {
    
    Serial.begin(9600);

    // Pulse in from controller
    while (pulseRotate == 0 || pulseDrive == 0 || pulseStrafe == 0 ||
            pulseArm == 0 || pulseClaw == 0)
    {
        pulseRotate = pulseIn(CH1, HIGH, 30000);
        pulseDrive = pulseIn(CH3, HIGH, 30000);
        pulseStrafe = pulseIn(CH4, HIGH, 30000);
        pulseArm = pulseIn(CH5, HIGH, 30000);
        pulseClaw = pulseIn(CH6, HIGH, 30000);
        Serial.println(pulseRotate);
    }

    rightFront.attach(RF);
    rightBack.attach(RB);
    leftFront.attach(LF);
    leftBack.attach(LB);
    arm.attach(ARM);
    claw.attach(CLAW);
}

void loop() {
    
    // Pulse in from controller
    pulseRotate = pulseIn(CH1, HIGH, 30000);
    pulseDrive = pulseIn(CH3, HIGH, 30000);
    pulseStrafe = pulseIn(CH4, HIGH, 30000);
    pulseArm = pulseIn(CH5, HIGH, 30000);
    pulseClaw = pulseIn(CH6, HIGH, 30000);

    Serial.println("drive");
    Serial.println(pulseDrive);
    Serial.println("strafe");
    Serial.println(pulseStrafe);
    Serial.println("rotate");
    Serial.println(pulseRotate);

    if (pulseRotate != 0 && pulseDrive != 0 && pulseStrafe != 0 &&
        pulseArm != 0 && pulseClaw != 0)
    {
        // Mapping pulses to plus and minus 100%
        drive = map(pulseDrive, pulseShort, pulseLong, -100, 100);
        strafe = map(pulseStrafe, pulseShort, pulseLong, -100, 100);
        rotate = map(pulseRotate, pulseShort, pulseLong, -100, 100);
    
        // Calculating percentage for motors
        front_left    = drive + strafe  - rotate  + 15;
        rear_left     = -1*drive - strafe  - rotate  + 15 b  ;
        front_right   = (drive - strafe  + rotate  + 0)*-1;
        rear_right    = (-1*drive + strafe  + rotate  + 0)*-1;

        // Remapping to pulse values for motor controllers
        front_left    = map(front_left, -100, 100, motorLimitL, motorLimitH);
        rear_left     = map(rear_left, -100, 100, motorLimitL, motorLimitH);
        front_right   = map(front_right, -100, 100, motorLimitL, motorLimitH);
        rear_right    = map(rear_right, -100, 100, motorLimitL, motorLimitH);
    
        // Writing values to motors
        rightBack.write(rear_right);
        rightFront.write(front_right);
        leftBack.write(rear_left);
        leftFront.write(front_left);
    
        // Mapping values for arm servos
        lift = map(pulseArm,1000,1900,0,180);
        pinch = map(pulseClaw,1000,1900,0,180);

        // Writing values to arm servos
        arm.write(lift);
        claw.write(pinch);

    } else {
        rightFront.detach();
        rightBack.detach();
        leftFront.detach();
        leftBack.detach();
        arm.detach();
        claw.detach();
    }

    // Print to serial monitor
    /*Serial.println("drive");
    Serial.println(drive);
    Serial.println("strafe");
    Serial.println(strafe);
    Serial.println("rotate");
    Serial.println(rotate);
    /*
    Serial.println(" ");
    Serial.println("FLeft");
    Serial.println(front_left);
    Serial.println("FRight");
    Serial.println(front_right);
    Serial.println("RRight");
    Serial.println(rear_right);
    Serial.println(" ");
    Serial.println("RLeft");
    Serial.println(rear_left);
    */
    Serial.println("---------------------------");

    delay(1);
}
