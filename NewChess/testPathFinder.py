#!/usr/bin/env pybricks-micropython
# -*- coding: utf-8 -*-
from copy import deepcopy
import pathFinder
from miniStructures import Position
      #      |start|
      #         #
      #------->
maze=[[-1,-1,-1,-1,-1, -1], #мнимый защитный край
      [-1, 0, -2, -2, 0, -1], #первый ряд
      [-1, 0, 0, 0, 0, -1], #второй ряд
      [-1, 0, 0, 's', 'd', -1],
      [-1, 0, 0, 'p', 0, -1], #4 ряд
      [-1,-1,-1,-1,-1, -1]]#мнимый защитный край

startPos = Position(1, 1)
endPos = Position(4, 4)
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