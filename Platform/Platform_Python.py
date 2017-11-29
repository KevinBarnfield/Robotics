'''
UGRT Mini IGVC
--------------
Date  : September 28, 2017
Brief : This file is meant to handle all the main
        input from the controller and map it to
        the motors.
'''

# Libraries
import RPI.GPIO as GPIO

# Constants
TOP = 200
BOT = -200

# Left Motor
enA = 29
in1 = 31
in2 = 33

# Right Motor
enB = 36
in3 = 38
in4 = 40

# Functions
def forward (speed, stick_x):
    global in1, in2, in3, in4

def reverse (speed, stick_x):
    global in1, in2, in3, in4

def stop ():
    global in1, in2, in3, in4
    GPIO.output(in1, GPIO.LOW)
    GPIO.output(in2, GPIO.LOW)
    GPIO.output(in3, GPIO.LOW)
    GPIO.output(in4, GPIO.LOW)

# Setup
GPIO.setmode(GPIO.BOARD)

GPIO.setup(enA, GPIO.OUT)
GPIO.setup(in1, GPIO.OUT)
GPIO.setup(in2, GPIO.OUT)

GPIO.setup(enB, GPIO.OUT)
GPIO.setup(in3, GPIO.OUT)
GPIO.setup(in4, GPIO.OUT)

# Loop
while True:
    # Get Inputs
    # For a later date...

    # Map Inputs
    r_trigger = map(r_input, 0, 100, 0, 255)
    l_trigger = map(l_input, 0, 100, 0, 255)
    stick_x = map(x_input, LEFT, RIGHT, 0, 100)
    stick_x = stick_x / 100

    # Basically, if the stick is pushed left then
    # we want to slow down the left wheel and so
    # we will adjust the speed on that by stick_x

    if abs(l_trigger - r_trigger) < 20:
        stop()
    else if r_trigger > l_trigger:
        forward(r_trigger, stick_x)
    else if l_trigger > r_trigger:
        reverse(l_trigger, stick_x)

# Cleanup
GPIO.cleanup()
