#!/usr/bin/env pybricks-micropython
# -*- coding: utf-8 -*-
from pybricks.hubs import EV3Brick
from pybricks.ev3devices import (Motor, TouchSensor, ColorSensor,
InfraredSensor, UltrasonicSensor, GyroSensor)
from pybricks.parameters import Port, Stop, Direction, Button, Color
from pybricks.tools import wait, StopWatch, DataLog
from pybricks.robotics import DriveBase
from pybricks.media.ev3dev import SoundFile, ImageFile
def cellMove():
    goToBorder()
    robot.straight(150)


def goToBorder():
    nowColor = (line_sensor_right.reflection()+line_sensor_left.reflection())/2
    while abs( (line_sensor_right.reflection()+line_sensor_left.reflection())/2 -nowColor)<30:
        robot.drive(40,0)
    robot.drive(0,0)
    robot.straight(5)
    robot.drive(0,0)
    robot.stop()
    #ЗАЧЕМ? while это и есть if
    #разве что для читабельности
    if abs(line_sensor_left.reflection()-nowColor)<30:
        while abs(line_sensor_left.reflection()-nowColor)<30:
            left_motor.run(20)
    left_motor.run(0)
    if abs(line_sensor_right.reflection()-nowColor)<30:
        while abs(line_sensor_right.reflection()-nowColor)<30:
            right_motor.run(20)
    right_motor.run(0)


def align(dirOfAlign = 1):
    goToBorder()
    robot.straight(-85)
    robot.turn(dirOfAlign*90)
    goToBorder()
    robot.straight(-85)
    robot.turn(-dirOfAlign*90)

# This program requires LEGO EV3 MicroPython v2.0 or higher.
# Click "Open user guide" on the EV3 extension tab for more information.


# Create your objects here.


#driveBase.straight(-50)
# driveBase.drive(-30, 0)
#
#while color_sensor.reflection() > 20:
# wait(1)
#driveBase.drive(0, 0)
#wait(1000)

# '''
#
# cellMove()
# cellMove()
# driveBase.turn(90)
# align()
# cellMove()
# cellMove()
# align()
#
#
# cellMove()
#
# driveBase.turn(90)
#
# cellMove()
# cellMove()
# driveBase.turn(90)
# cellMove()
# '''

# cellMove()
# cellMove()
# cellMove()
# align()
# driveBase.turn(-90)
# cellMove()
# cellMove()
# driveBase.turn(-90)
# cellMove()
# cellMove()

# driveBase.straight(70)
# driveBase.turn(180)
# cellMove()
# align()
# driveBase.turn(-90)

# cellMove()
# driveBase.turn(180)
# cellMove()
# cellMove()
# driveBase.turn(90)
# cellMove()
# cellMove()



# '''
# driveBase.turn(90)
# cellMove()
# driveBase.turn(180)
# cellMove()
# cellMove()
# driveBase.turn(90)
# cellMove()
# cellMove()
# '''



def goLine():
    RED = 90
    WHITE = 100
    threshold = (RED + WHITE) / 2
    PROPORTIONAL_GAIN = 1.2
    DRIVE_SPEED = 50
    while color_sensor.reflection()<20:
        # Calculate the deviation from the threshold.
        deviation = line_sensor_right.reflection() - threshold

        # Calculate the turn rate.
        turn_rate = PROPORTIONAL_GAIN * deviation

        # Set the drive base speed and turn rate.
        robot.drive(-DRIVE_SPEED, turn_rate)

        # You can wait for a short time or do other things in this loop.
        wait(10)
        if color_sensor.color()==Color.RED:
            ev3.speaker.beep()
        wait(100)
        robot.drive(0,0)

        #setup main block
ev3 = EV3Brick()

left_motor = Motor(Port.B, Direction.CLOCKWISE)
right_motor = Motor(Port.C, Direction.CLOCKWISE)
color_sensor = ColorSensor(Port.S4)
line_sensor_left = ColorSensor(Port.S2)
line_sensor_right = ColorSensor(Port.S3)
WHEEL_DIAMETER = 54

# The axle track is the distance between the centers of each of the
# wheels. This is about 200 mm for the Tank Bot.
AXLE_TRACK = 115

robot = DriveBase(left_motor, right_motor, WHEEL_DIAMETER, AXLE_TRACK)
######################################################

def task():
    robot.straight(-260)
    align(-1)
    robot.turn(-90)
    cellMove()
    cellMove()
    robot.turn(-90)
    cellMove()
    ##in cube cell
    robot.turn(180)
    goToBorder()
    robot.straight(-85)
    cellMove()
    cellMove()
    robot.turn(-90)
    cellMove()

if __name__ == '__main__':
    task()