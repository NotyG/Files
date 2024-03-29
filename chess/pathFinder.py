#!/usr/bin/env pybricks-micropython
# -*- coding: utf-8 -*-
from copy import deepcopy
from miniStructures import Position

paths = []
maxLevel = None
def waveUnfolding(maze, startPos, endPos): #maze - поле, startPos - Position,
    '''return unfolded maze\n
    if there is no path return 'NOPATH' '''
    wfront = 1
    maze[endPos.y][endPos.x] = 0 #костыль
    # print(startPos.y, startPos.x)
    # print(endPos.y, endPos.x)
    maze[startPos.y][startPos.x] = 'c' #todo зачем?
    #currentPositions = [startPos]
    currentPositions = []
    currentPositions.append(startPos)
    nextPositions = []
    while maze[endPos.y][endPos.x] == 0:
        for currentPos in currentPositions:
            for dY in range(-1, 2, 2):
                nextPositions.append(Position(currentPos.y + dY, currentPos.x))
            for dX in range(-1, 2, 2):
                nextPositions.append(Position(currentPos.y, currentPos.x + dX))
        #чтобы не менять список во время его перебора
        currentPositions = nextPositions.copy()  # нам не нужен указатель - это и есть указатель, @$##**
        for nextPos in nextPositions:
            if not(nextPos.x < len(maze) and nextPos.y < len(maze)):
                #просто проверка на то,
                # что такие клетки вообще существуют, пока не важно, что в них
                currentPositions.remove(nextPos)
                continue
            if maze[nextPos.y][nextPos.x] !=0: #проверка, что в клетках
                currentPositions.remove(nextPos)
            else:
                maze[nextPos.y][nextPos.x] = wfront

        nextPositions.clear()
        if len(currentPositions) == 0: #сверху мы отчистили непригодные, если ничего нет, значит нет пути
            return 'NOPATH'
        wfront += 1
    maze[startPos.y][startPos.x] = 0
    return maze #поле с развёрнутой волной

def waveFolding(maze, startPos, endPos, movesBefore = [], level = None):
    global paths, maxLevel
    if maze == 'NOPATH': return None
    if movesBefore == []: 
        level = 0
        moves = []
        maxLevel = maze[endPos.y][endPos.x]
    else: 
        level += 1
        moves = deepcopy(movesBefore)
    if level >= maxLevel and endPos == startPos:
        movesBefore.append(startPos)
        paths.append(movesBefore)
        return None
    maze[startPos.y][startPos.x] = 0
    currentPos = Position(endPos.y, endPos.x)
    moves.append(endPos)
    newPositions = []
    for d in range(-1, 2, 2):
        if type(maze[currentPos.y][currentPos.x + d]) == int:
            if maze[currentPos.y][currentPos.x] == maze[currentPos.y][currentPos.x + d] + 1:
                newPositions.append(Position(currentPos.y, currentPos.x + d))
        if type(maze[currentPos.y + d][currentPos.x]) == int:
            if maze[currentPos.y][currentPos.x] == maze[currentPos.y + d][currentPos.x] + 1:
                newPositions.append(Position(currentPos.y + d, currentPos.x))
    if len(newPositions) == 0:
        return -1
    #print('level', level, '\n', newPositions, '\n')
    for newPos in newPositions:
        waveFolding(deepcopy(maze), startPos, newPos, deepcopy(moves), level)
    for path in paths:
        path.reverse() #двигались с endPos до startPos
    return paths

def findPath(maze, startPos, endPos):
    '''please use deepcopy when set maze\n
    findPath return a path from startPos to endPos\n
    if there is no path return None\n
    '''
    #prints('in func')
    if( abs(endPos.x-startPos.x) == 1 and abs(endPos.y - startPos.y) == 0
    or abs(endPos.x-startPos.x) == 0 and abs(endPos.y - startPos.y) == 1):
        maze[endPos.y][endPos.x] = 'p'
        moves = [startPos, endPos]
        return moves

    return waveFolding(waveUnfolding(maze, startPos, endPos), startPos, endPos)


