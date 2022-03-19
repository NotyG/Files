#!/usr/bin/env pybricks-micropython
# -*- coding: utf-8 -*-
from miniStructures import Position
#from copy import deepcopy
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

def waveFolding(maze, startPos, endPos):
    if maze == 'NOPATH': return None, None;
    maze[startPos.y][startPos.x] = 0
    currentPos = Position(endPos.y, endPos.x)
    moves = [endPos]
    newPos = None
    while not (currentPos.y == startPos.y and currentPos.x == startPos.x):
        for d in range(-1, 2, 2):
            if type(maze[currentPos.y][currentPos.x + d]) == int:
                if maze[currentPos.y][currentPos.x] == maze[currentPos.y][currentPos.x + d] + 1:
                    newPos = Position(currentPos.y, currentPos.x + d)
                    break
            if type(maze[currentPos.y + d][currentPos.x]) == int:
                if maze[currentPos.y][currentPos.x] == maze[currentPos.y + d][currentPos.x] + 1:
                    newPos = Position(currentPos.y + d, currentPos.x)
                    break
        maze[currentPos.y][currentPos.x] = 'p' #для визуализации,
        if newPos == None: return -1 #не нашлось такой позиции(методы применены в неправильном порядке)
        currentPos = newPos #указатель
        moves.append(currentPos)
        #print(currentPos.y, currentPos.x)
    moves.reverse() #двигались с endPos до startPos
    #moves.pop(0) #нам не требуется координата начальной точки- уже требуется,
    # а ещё Robot.moveToNearPosition(endPos) может остаться в клетке, если она стартовая и конечная
    return moves, maze

def findPath(maze, startPos, endPos):
    '''please use deepcopy when set maze\n
    findPath return a path from startPos to endPos\n
    if there is no path return None, None\n
    a, b = None, None;
    '''
    #prints('in func')
    if( abs(endPos.x-startPos.x) == 1 and abs(endPos.y - startPos.y) == 0
    or abs(endPos.x-startPos.x) == 0 and abs(endPos.y - startPos.y) == 1):
        maze[endPos.y][endPos.x] = 'p'
        moves = [startPos, endPos]
        return moves, maze

    return waveFolding(waveUnfolding(maze, startPos, endPos), startPos, endPos)
