/**Platform Robot
 * @author Kevin Barnfield
 * @date Sept 21, 2017
 * @brief Arduino code for platform robot.
 */

#include "Globals.h"

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

void loop()
{
    demoOne();
    delay(1000);

    demoTwo();
    delay(1000);
}
