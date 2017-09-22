/**Demo Functions
 * @author Not Kevin Barnfield
 * @date Sept 21, 2017
 * @brief Demo functions from L298 tutorial.
 */

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

