#!/usr/bin/env pybricks-micropython
# -*- coding: utf-8 -*-
from copy import deepcopy
import pathFinder as pathFinder
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

startPos = Position(1, 1)
endPos = Position(4, 3)
mazeUnfold = pathFinder.waveUnfolding(deepcopy(maze), startPos, endPos)
for i in range(6):
    print(*mazeUnfold[i])
paths = pathFinder.findPath(deepcopy(maze), startPos,endPos)
# for path in paths:
#       print(path.y, path.x)


for path in paths:
      tempMaze = deepcopy(maze)
      for pos in path:
            tempMaze[pos.y][pos.x] = 'p'
      for j in range(6):
            print(*tempMaze[j])
      print('\n')
print(len(paths), )
      