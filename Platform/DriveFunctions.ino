/**Drive Functions
 * @author Kevin Barnfield
 * @date Sept 21, 2017
 */

void forward (int motorSpeed)
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, motorSpeed);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, motorSpeed);

    return;
}

void reverse (int motorSpeed)
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, motorSpeed);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, motorSpeed);

    return;
}

void  brake ()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    
    return;
}
