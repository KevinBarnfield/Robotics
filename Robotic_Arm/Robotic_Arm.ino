
#include <Servo.h>

#define xDir A2 //horizontal left right movement green wire
#define yDir A3 //orange is up down movement
#define bottomDir A1 //throttle control

int val_lx; // Bottom Servo
int val_ly; // Middle Servo
int val_rx; // Top servo

const int botServOff = 94;//this turns botServo off

Servo bottom;
Servo middle;
Servo top;

void setup() {
    bottom.attach(9);
    middle.attach(10);
    top.attach(11);
    val_lx = 160;
    val_ly = 90;
    val_rx = 50;
    //val_lx = 2;
    //val_ly = 2;
    //val_rx = 2;
    Serial.begin(9600);  
}

void loop() {
    // put your main code here, to run repeatedly:
    
    int ly = analogRead(yDir);
    if (ly >= 700) {
        if (val_ly <= 180) {
            val_ly = val_ly + 3;
        }
    } else if ( ly <= 440) {
        if (val_ly >=0) {
            val_ly = val_ly - 3;
        }
    }
    
    int lx = analogRead(xDir);
    if (lx >= 700) {
        if (val_lx <=180) {
            val_lx = val_lx + 3;    
        }
    } else if (lx <= 440) {
        if(val_lx >= 0){
            val_lx = val_lx - 3;    
        }
    }
    
    int rx = analogRead(bottomDir);
    if (rx >= 700) {
        if (rx <= 180) {
            val_rx = val_rx + 3;    
        }
        
    } else if ( rx <= 440) {
        if (val_rx >=0) {
            val_rx = val_rx - 3;    
        }
        
    }
        
    Serial.print("  LX: ");
    Serial.println(lx);
    Serial.print("  LY: ");
    Serial.print(ly);
    Serial.print("  RX: ");
    Serial.print(rx);
    //val_lx = map(val_lx, 900, 0, 0, 150);
    middle.write(val_lx);
    //val_ly = map(val_ly, 0, 900, 0, 180);
    top.write(val_ly);
    //val_rx = map(val_rx, 0, 900, 0, 180);
    bottom.write(val_rx);
        
    delay(50);
}
