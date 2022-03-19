#!/usr/bin/env pybricks-micropython
# -*- coding: utf-8 -*-
from miniStructures import Position
from Robot import Robot
import pathFinder
import chessSolution
from pybricks.hubs import EV3Brick
from pybricks.ev3devices import (Motor, TouchSensor, ColorSensor,
InfraredSensor, UltrasonicSensor, GyroSensor)
from pybricks.parameters import Port, Stop, Direction, Button, Color
# from pybricks.tools import wait, StopWatch, DataLog
from pybricks.robotics import DriveBase
# from pybricks.media.ev3dev import SoundFile, ImageFile
from copy import deepcopy
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
SOUTH = 2
NORTH = 4
EAST = 3
WEST = 1
driveBase = DriveBase(left_motor, right_motor, WHEEL_DIAMETER, AXLE_TRACK)
# driveBase.settings(90, 0, 40, 0)
robot = Robot(driveBase,
 line_sensor_left, line_sensor_right,
 left_motor, right_motor,
  gyro_sensor, color_sensor,
  TURN_SPEED, 100,
Position(4, 3), WEST,
  25)

# orderFigures=['blue', 'green', 'yellow', 'red']
# positionFigures = ['green', 'blue', 'yellow', 'red']
# solution = chessSolution.solve(orderFigures, positionFigures)
#path, _ = pathFinder.findPath(deepcopy(maze), Position(robot._currentPos.y, robot._currentPos.x), Position(solution[0].y, solution[0].x))

endPos = Position(3, 2)
path, _ = pathFinder.findPath(deepcopy(maze), robot._currentPos, endPos)

robot.moveBy(path)

# endPos = Position(1, 3)
# path, _ = pathFinder.findPath(deepcopy(maze), robot._currentPos, endPos)
# print('myPos', robot._currentPos.y, robot._currentPos.x)
# print('mydir', robot._currentDir)
# robot.moveBy(path)

# robot._cellMove()
#robot._cellMoveBack()
#robot.turn(90)
# while True:
#       print(robot.line_sensor_left.reflection() , '\t', robot.line_sensor_right.reflection(), 't', robot.color_sensor.color())
      #robot.lineDetectRedRight(100,None, -1, 1)
      
# while True:
#       print(gyro_sensor.angle())
# #robot._cellMove()
# robot.turn(90)
# # while robot.driveBase.distance() < 100:
# #       robot.driveBase.drive(200, 0)
# robot.fastStop()
# while True:
#       print(robot.color_sensor.color())
# # startPos = Position(2, 1)
# # endPos = Position(4, 4)

# # path, mazeFold = pathFinder.findPath(maze, startPos, endPos)
# # # for pos in path:
# # #       print(pos.y, pos.x)
# # # for i in range(0, 6):
#     print(*mazeFold[i])

# # robot.align(-1)
# # robot.moveTo(path)