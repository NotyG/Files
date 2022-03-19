#!/usr/bin/env pybricks-micropython
# -*- coding: utf-8 -*-
from copy import deepcopy
import pathFinder
from miniStructures import Position
      #      |start|
      #         #
      #------->
maze=[[-1,-1,-1,-1,-1, -1], #мнимый защитный край
      [-1, 0, 0, 0, 0, -1], #первый ряд
      [-1, 0, 0, 0, 0, -1], #второй ряд
      [-1, 0, 0, 0, 0, -1],
      [-1, 0, 0, 0, 0, -1], #4 ряд
      [-1,-1,-1,-1,-1, -1]]#мнимый защитный край

startPos = Position(4, 2)
endPos = Position(1, 3)
mazeUnfold = pathFinder.waveUnfolding(deepcopy(maze), startPos, endPos)
for i in range(6):
    print(*mazeUnfold[i])
path, mazeFold = pathFinder.findPath(deepcopy(maze), startPos,endPos)
print()
if path == -1: print('NOPATH')
else:
      for i in range(len(mazeFold)):
            print(*mazeFold[i])
      print()
      for pos in path:
            print(pos.y, pos.x)