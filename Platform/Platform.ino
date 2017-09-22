/**Platform Robot
 * @author Kevin Barnfield
 * @date Sept 21, 2017
 * @brief Arduino code for platform robot.
 */

// Connect motor controller pins to Arduino digital pins
// Motor A
int enA = 7;
int in1 = 6;
int in2 = 5;

// Motor B
int enB = 8;
int in3 = 10;
int in4 = 9;

void setup()
{
    // Set all the motor control pins to outputs
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
}

void demoOne()
{
    // This function will run the motors in both directions at a fixed speed
    
    // Turn on motor A
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    
    // Set speed to 200 out of possible range 0~255
    analogWrite(enA, 200);
    
    // Turn on motor B
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    // Set speed to 200 out of possible range 0~255
    analogWrite(enB, 200);
    delay(2000);
    
    // Change motor directions
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(2000);
    
    // Turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

void demoTwo()
{
    // This function will run the motors across the range of possible speeds
    // note that maximum speed is determined by the motor itself and the operating voltage
    // the PWM values sent by analogWrite() are fractions of the maximum speed possible 
    // by your hardware
    // turn on motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    
    // Accelerate from zero to maximum speed
    for (int i = 0; i < 256; i++) {
        analogWrite(enA, i);
        analogWrite(enB, i);
        delay(20);
    }
    
    // Deccelerate from maximum speed to 0
    for (int i = 255; i >= 0; --i) {
        analogWrite(enA, i);
        analogWrite(enB, i);
        delay(20);
    }
    
    // Turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

void loop()
{
    demoOne();
    delay(1000);

    demoTwo();
    delay(1000);
}
