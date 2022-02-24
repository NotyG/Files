#!/usr/bin/env pybricks-micropython
# -*- coding: utf-8 -*-
from miniStructures import Position
from Robot import Robot
import pathFinder
from pybricks.hubs import EV3Brick
from pybricks.ev3devices import (Motor, TouchSensor, ColorSensor,
InfraredSensor, UltrasonicSensor, GyroSensor)
from pybricks.parameters import Port, Stop, Direction, Button, Color
# from pybricks.tools import wait, StopWatch, DataLog
from pybricks.robotics import DriveBase
# from pybricks.media.ev3dev import SoundFile, ImageFile

maze=[[-1,-1,-1,-1,-1, -1], #imagine defend row
      [-1, 0, 0, 0, 0, -1], #1st row
      [-1, 0, 0, 0, 0, -1], #sec row
      [-1, 0, 0, 0, 0, -1],
      [-1, 0, 0, 0, 0, -1], #fourth row
      [-1,-1,-1,-1,-1, -1]] 

# ev3 = EV3Brick()
left_motor = Motor(Port.B, Direction.CLOCKWISE)
right_motor = Motor(Port.C, Direction.CLOCKWISE)
color_sensor = ColorSensor(Port.S4)
line_sensor_left = ColorSensor(Port.S2)
line_sensor_right = ColorSensor(Port.S3)
gyro_sensor = GyroSensor(Port.S1)
WHEEL_DIAMETER = 56
AXLE_TRACK = 113
TURN_SPEED = 140
driveBase = DriveBase(left_motor, right_motor, WHEEL_DIAMETER, AXLE_TRACK)
# driveBase.settings(90, 0, 40, 0)
robot = Robot(driveBase, line_sensor_left, line_sensor_right,
 left_motor, right_motor,
  gyro_sensor, color_sensor,
  TURN_SPEED, 200,
  Position(2,1), 4)
# while True:
#       print(gyro_sensor.angle())
# #robot._cellMove()
robot.turn(90)
# # while robot.driveBase.distance() < 100:
# #       robot.driveBase.drive(200, 0)
# # robot.fastStop()
# # while True:
# #       print(robot.color_sensor.color())
# # startPos = Position(2, 1)
# # endPos = Position(4, 4)

# # path, mazeFold = pathFinder.findPath(maze, startPos, endPos)
# # # for pos in path:
# # #       print(pos.y, pos.x)
# # # for i in range(0, 6):
# # #     print(*mazeFold[i])

# # robot.align(-1)
# # robot.moveTo(path)