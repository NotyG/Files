#!/usr/bin/env pybricks-micropython
# -*- coding: utf-8 -*-
from sys import exit
from copy import deepcopy
import chessSolution, pathFinder
from miniStructures import Position
from Robot import Robot
#не забыть сменить расшифровку цветов в фигуры
from pybricks.hubs import EV3Brick
from pybricks.ev3devices import (Motor, TouchSensor, ColorSensor,
InfraredSensor, UltrasonicSensor, GyroSensor)
from pybricks.parameters import Port, Stop, Direction, Button, Color
#from pybricks.tools import wait#, StopWatch, DataLog
from pybricks.robotics import DriveBase
# from pybricks.media.ev3dev import SoundFile, ImageFile
      #      |start|
      #         #
      #------->
maze=[[-1,-1,-1,-1,-1, -1], #мнимый защитный край
      [-1, -2, -2, -2, -2, -1], #первый ряд
      [-1, 0, 0, 0, 0, -1], #второй ряд
      [-1, 0, 0, 0, 0, -1],
      [-1, 0, 0, 0, 0, -1], #4 ряд
      [-1,-1,-1,-1,-1, -1]]#мнимый защитный край
#print(maze)
actualColors = [Color.BLUE, Color.GREEN, Color.RED, Color.YELLOW]
actualColorsTemp = actualColors.copy()
left_motor = Motor(Port.B, Direction.CLOCKWISE)
right_motor = Motor(Port.C, Direction.CLOCKWISE)
color_sensor = ColorSensor(Port.S4)
line_sensor_left = ColorSensor(Port.S2)
line_sensor_right = ColorSensor(Port.S3)
gyro_sensor = GyroSensor(Port.S1)

WHEEL_DIAMETER = 56
AXLE_TRACK = 143
TURN_SPEED = 80
BASE_SPEED = 100
DISTANCE = 360 #36 * 10
#не забыть сменить расшифровку цветов в фигуры
driveBase = DriveBase(left_motor, right_motor, WHEEL_DIAMETER, AXLE_TRACK)
robot = Robot(driveBase, line_sensor_left, line_sensor_right,
             left_motor, right_motor,
             gyro_sensor, color_sensor,
             TURN_SPEED, 70,
             Position(0,1), 4,
             10)
orderFigures = []
positionFigures = []
#не забыть сменить расшифровку цветов в фигуры
#можно писать просто driveBase, так как robot.driveBase и driveBase - один и тот же объект

if __name__ == '__main__':
      robot.goToBorder()
      #print('gotobore')
      lenActualColors = len(actualColors)
      # for i in range(lenActualColors):
      
      #       while not (robot.line_sensor_left.color() in actualColors):
      #             robot.line_sensor_left.color()
      #             print(robot.line_sensor_left.color())
      #       print(robot.line_sensor_left.color())
      # exit()
      for i in range(lenActualColors-1):
            color = robot.line_sensor_left.color()
            while not (color in actualColorsTemp): #robot.line_sensor_left.color()
                  color = robot.line_sensor_left.color()
                  robot.driveBase.drive(BASE_SPEED, 0)
            #print(robot.line_sensor_left.color() in actualColorsTemp)
            #print(robot.line_sensor_left.color())
            orderFigures.append(color)
            actualColorsTemp.remove(color)
      orderFigures.append(actualColorsTemp[0])
      print(orderFigures)
      
      robot.driveBase.straight(100)
      while robot.line_sensor_left.color() != Color.RED:
            robot.driveBase.drive(BASE_SPEED, 0)
      robot.driveBase.stop()
      while robot.line_sensor_right.color() != Color.RED:
            robot.right_motor.run(TURN_SPEED)
      robot.driveBase.straight(30)
      robot.driveBase.stop()
      robot.turn(-90)

      robot.lineDetectRedRight(BASE_SPEED, DISTANCE)
      robot.turn(90)
      robot.driveBase.straight(35)
      robot.turn(90)
      actualColorsTemp = actualColors.copy()
      robot.driveBase.straight(30)
      color = robot.color_sensor.color()
      actualColorsTemp.remove(color)
      positionFigures.append(color)
      for i in range(lenActualColors-2):
            #color = robot.color_sensor.color()
            #while not (color in actualColorsTemp): #robot.line_sensor_left.color()
            robot.lineDetectRedRight(BASE_SPEED, 250, -1)
            color = robot.color_sensor.color()
            #print(color in actualColorsTemp)
            print(color)
            positionFigures.append(color)
            actualColorsTemp.remove(color)
      positionFigures.append(actualColorsTemp[0])
      positionFigures.reverse()
      
      #порядки заполнены

      for i in range(len(orderFigures)):
            if orderFigures[i] == Color.RED: orderFigures[i] = 'red'
            elif orderFigures[i] == Color.BLUE: orderFigures[i] = 'blue'
            elif orderFigures[i] == Color.YELLOW: orderFigures[i] = 'yellow'
            elif orderFigures[i] == Color.GREEN: orderFigures[i] = 'green'
      for i in range(len(positionFigures)) :
            if positionFigures[i] == Color.RED: positionFigures[i] = 'red'
            elif positionFigures[i] == Color.BLUE: positionFigures[i] = 'blue'
            elif positionFigures[i] == Color.YELLOW: positionFigures[i] = 'yellow'
            elif positionFigures[i] == Color.GREEN: positionFigures[i] = 'green'
      print(orderFigures)
      print(positionFigures)

      solution = chessSolution.solve(orderFigures, positionFigures)

      pos = Position(solution[0]._yStart, solution[0]._xStart) #1, 2
      print('pos', pos)
      print('robot cpos', robot._currentPos.y, robot._currentPos.x)
      distance = abs(pos.x -  robot._currentPos.x)  * 250
      robot.driveBase.straight(-50)
      angle = robot._getTurnAngle(Position(0, pos.x))
      robot.turn(angle)
      #print('after turn 180')
      robot.lineDetectRedLeft(BASE_SPEED, distance)
     # print('aftrerLine')
      if angle == 0:
            robot.turn(-90)
      else: robot.turn(90)
      #robot.turn(90)
     # print('afterturn 90')
      robot.driveBase.straight(100)
      robot._currentPos = pos
      #exit()
      #мы в сетке
     # robot.turnSpeed = 120
      print('in cells')
      path, trash = pathFinder.findPath(deepcopy(maze), robot._currentPos, Position(solution[0].y, solution[0].x))
      print('cpos', robot._currentPos.y, robot._currentPos.x)
      print('path')
      for pos in path:
            print(pos.y, pos.x)
      print('\nmaze')
      for j in range(len(maze)):
            print(*maze[j])
      print('cdir', robot._currentDir)
      robot.moveBy(path)
      maze[solution[0]._yStart][solution[0]._xStart] = 0
      maze[solution[0].y][solution[0].x] = -2
      robot.driveBase.straight(25)
      robot.driveBase.straight(-80)
      #доделать выравнивание
      
      robot.moveToNearPosition(path[-2]) #второй с конца
      print('dir after 1', robot._currentDir)
      robot.align() 
      print('after movenear')
      for i in range(1, 4):
            print('\n\nin', i,'cycle')
            print('maze')
            for j in range(len(maze)):
                  print(*maze[j])
            print('\ncpos', robot._currentPos.y, robot._currentPos.x, '\nendPos', solution[i]._yStart, solution[i]._xStart)
            if(solution[i]._yStart == solution[i].y and solution[i]._xStart == solution[i].x):
                  continue
            path, _ = pathFinder.findPath(deepcopy(maze), robot._currentPos, Position(solution[i]._yStart, solution[i]._xStart))
            print('after pathfind1')
            robot.moveBy(path)
            print('dir', robot._currentDir)
            print('afterMove')
            path, _ = pathFinder.findPath(deepcopy(maze), robot._currentPos, Position(solution[i].y, solution[i].x))
            print('after pathfind2')
            robot.moveBy(path)
            print('dir', robot._currentDir)
            maze[solution[i]._yStart][solution[i]._xStart] = 0
            maze[solution[i].y][solution[i].x] = -2
            robot.driveBase.straight(25)
            robot.driveBase.straight(-80)
            #доделать выравнивание
            #print('path')
            #print(path)
            robot.moveToNearPosition(path[-2]) #второй с конца
            print('alPos', robot._currentPos.y, robot._currentPos.x, robot._currentDir)
            if i < 3: #на выравнивание требуется время единожды можно выравняться
                  robot.align()
      if robot._currentPos.y == 1:
            robot.turn(robot._getTurnAngle(Position(0, robot._currentPos.x)))
      else:
            paths = [[],[],[],[]]
            for i in range(1, 5):
                  paths[i-1], _ = pathFinder.findPath(maze, robot._currentPos, Position(1, i))
                  if i >= 2:
                        if len(paths[i-1]) >= len(paths[i-2]):
                              paths.remove(paths[i-1])
                        else: paths.remove(paths.remove(paths[i-2]))
            path = paths[0]
            robot.moveBy(path)
      robot.driveBase.straight(600)    
      print('endOfProgramm')