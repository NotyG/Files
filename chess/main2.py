#!/usr/bin/env pybricks-micropython
# -*- coding: utf-8 -*-
from sys import exit
from copy import deepcopy
import chessSolution, pathFinder
from miniStructures import Position
from Robot import Robot
#не забыть сменить расшифровку цветов в фигуры
from pybricks.hubs import EV3Brick
from pybricks.ev3devices import (Motor, ColorSensor, GyroSensor)
from pybricks.parameters import Port, Stop, Direction, Button, Color
# from pybricks.tools import wait, StopWatch, DataLog
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
SOUTH = 2
NORTH = 4
EAST = 3
WEST = 1
WHEEL_DIAMETER = 56
AXLE_TRACK = 176
TURN_SPEED = 80
BASE_SPEED = 100
DISTANCE = 360 #36 * 10
DiSTANCE_TO_WHEELS = 80 #расстояние от датчиков линии(передних) до середины колёс
DISTANCE_TO_CELL = 130
POS_CHANGE_FROM_CENTER = -30 #мм, право+, лево- | если придётся робота сдвинуть чуть правее от центра зоны СТАРТ 
#не забыть сменить расшифровку цветов в фигуры
driveBase = DriveBase(left_motor, right_motor, WHEEL_DIAMETER, AXLE_TRACK)
robot = Robot(driveBase, line_sensor_left, line_sensor_right,
             left_motor, right_motor,
             gyro_sensor, color_sensor,
             TURN_SPEED, 60,
             Position(0,2.5), SOUTH,
             25)
orderFigures = []
positionFigures = ['green', 'blue', 'yellow', 'red']
#не забыть сменить расшифровку цветов в фигуры
#можно писать просто driveBase, так как robot.driveBase и driveBase - один и тот же объект

if __name__ == '__main__':
      robot.goToBorder()
      #print('gotobore')
      lenActualColors = len(actualColors)
      for i in range(lenActualColors-1):
            color = robot.line_sensor_left.color()
            while not (color in actualColorsTemp): #robot.line_sensor_left.color()
                  color = robot.color_sensor.color()
                  robot.driveBase.drive(BASE_SPEED, 0)
            #print(robot.line_sensor_left.color() in actualColorsTemp)
            #print(robot.line_sensor_left.color())
            orderFigures.append(color)
            actualColorsTemp.remove(color)
      orderFigures.append(actualColorsTemp[0])
      print(orderFigures)
      
      robot.driveBase.straight(90)
      # while robot.line_sensor_left.color() != Color.RED:
      #       robot.driveBase.drive(BASE_SPEED, 0)
      # robot.fastStop()
      # while robot.line_sensor_right.color() != Color.RED:
      #       robot.right_motor.run(40)
      robot.fastStop()
      isLeftOnRedLine = False
      isRightOnRedLine = False
      #j = 0
      while not(isLeftOnRedLine and isRightOnRedLine):
            #print(j)
            robot.left_motor.run(BASE_SPEED)
            robot.right_motor.run(BASE_SPEED)
            if robot.line_sensor_left.color() == Color.RED:
                  robot.left_motor.stop()
                  robot.right_motor.run(40)
                  isLeftOnRedLine = True
            if robot.line_sensor_right.color() == Color.RED:
                  robot.right_motor.stop()
                  robot.left_motor.run(40)
                  isRightOnRedLine = True
            #j+=1      
      robot.fastStop()

      robot.driveBase.straight(50) #Расстояние от датчиков линии до колёс
      robot.fastStop()
      #FIXME
      orderFigures = [Color.BLUE, Color.GREEN, Color.YELLOW, Color.RED]
      #порядки заполнены
      for i in range(len(orderFigures)):
            if orderFigures[i] == Color.RED: orderFigures[i] = 'red'
            elif orderFigures[i] == Color.BLUE: orderFigures[i] = 'blue'
            elif orderFigures[i] == Color.YELLOW: orderFigures[i] = 'yellow'
            elif orderFigures[i] == Color.GREEN: orderFigures[i] = 'green'
      print(orderFigures)
      print(positionFigures)
      solution = chessSolution.solve(orderFigures, positionFigures)
      pos = Position(solution[0]._yStart, solution[0]._xStart) #
      print('pos', pos.y, pos.x)
      print('robot cpos', robot._currentPos.y, robot._currentPos.x, robot._currentDir)
      angle = robot._getTurnAngle(Position(0, pos.x))
      print('angle',angle)
      distance = abs(pos.x - robot._currentPos.x)  * 250

      robot.turn(angle)
      #robot.driveBase.straight(distance)
      if angle > 0:
            # robot.lineDetectRedRight(BASE_SPEED, distance - POS_CHANGE_FROM_CENTER, -1)
            robot.lineDetectRedCenter(BASE_SPEED, distance - POS_CHANGE_FROM_CENTER, -1)
            robot.turn(-90)
      if angle < 0: 
            # robot.lineDetectRedLeft(BASE_SPEED, distance + POS_CHANGE_FROM_CENTER, -1)
            robot.lineDetectRedCenter(BASE_SPEED, distance + POS_CHANGE_FROM_CENTER, 1)
            robot.turn(90)
      robot.driveBase.straight(DISTANCE_TO_CELL) #100 расстояние до клетки
      robot._currentPos = pos
      #мы в сетке
     # robot.turnSpeed = 120
      # print('in cells')
      robot._currentDir = SOUTH
      robot.isHaveACube = True
      path, trash = pathFinder.findPath(deepcopy(maze), Position(robot._currentPos.y, robot._currentPos.x), Position(solution[0].y, solution[0].x))
      robot.isHaveACube = False
      print('cpos', robot._currentPos.y, robot._currentPos.x)
      print('path')
      for pos in path:
            print(pos.y, pos.x)
      print('\nmaze')
      for j in range(len(maze)):
            print(*maze[j])
      print('cdir', robot._currentDir)
      #robot.moveToNearPosition(Position(robot._currentPos.y+1, robot._currentPos.x))
      # robot.baseSpeed = 40
      # robot.align()
      # robot.baseSpeed = 80
      robot.moveBy(path)
      maze[solution[0]._yStart][solution[0]._xStart] = 0
      maze[solution[0].y][solution[0].x] = -2
      #robot.driveBase.straight(25) #25
      #robot.driveBase.straight(-80) #-80 не требуется толкать кубик
      #доделать выравнивание
      
      #robot.moveToNearPosition(path[-2]) #второй с конца
      print('dir after 1', robot._currentDir)
      #robot.baseSpeed = 40
      # robot.align() 
      #robot.baseSpeed = 80
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
            # if i == 1: #выравниваемся после нулевого кубика
            #       robot.align(path[1]) #TODO 
            # if i < 4 and i!=1: #на выравнивание требуется время, без выравнивания робот ехать не будет - я переделал будет
            #       robot.align(path[1])
            print('after pathfind1')
            robot.moveBy(path)
            robot.isHaveACube = True
            print('dir', robot._currentDir)
            print('afterMove')
            path, _ = pathFinder.findPath(deepcopy(maze), robot._currentPos, Position(solution[i].y, solution[i].x))
            #if robot._getTurnAngle
            print('after pathfind2')
            robot.moveBy(path)
            robot.isHaveACube = False
            print('dir', robot._currentDir)
            maze[solution[i]._yStart][solution[i]._xStart] = 0
            maze[solution[i].y][solution[i].x] = -2
            # robot.driveBase.straight(25)
            # robot.driveBase.straight(-80)
            #доделать выравнивание
            #print('path')
            #print(path)
            robot.moveToNearPosition(path[-2]) #второй с конца
            print('alPos', robot._currentPos.y, robot._currentPos.x, robot._currentDir)
      if robot._currentPos.y == 1:
            robot.turn(robot._getTurnAngle(Position(0, robot._currentPos.x)))
      else:
            paths = [[],[],[],[]]
            for i in range(1, 5):
                  paths[i-1], _ = pathFinder.findPath(maze, robot._currentPos, Position(1, i))
            paths.sort(key = len)
                              # if len(paths) - paths.count([]) >= 2:
                  #       if len(paths[0]) >= len(paths[1]):
                  #             paths.remove(paths[0])
                  #       else: paths.remove(paths.remove(paths[1]))
            path = paths[0]
            robot.moveBy(path)
      robot.driveBase.straight(600)    
      print('endOfProgramm')