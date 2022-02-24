# -*- coding: utf-8 -*-
#!/usr/bin/env pybricks-micropython
from miniStructures import Figure, Position
from copy import deepcopy
import pathFinder
##в программе для робота прописать import chessSolution
##todo оценить сложность алгоритма
##todo оценить потребление памяти
##todo добавить type hints(необязательно)
##todo избавиться от глобальных переменных, кроме сетки(необязательно)
##todo некоторые функции отсюда добавить в класс Figure

maze=[[-1,-1,-1,-1,-1, -1], #мнимый защитный край
      [-1, -2, -2, -2, -2, -1], #первый ряд
      [-1, 0, 0, 0, 0, -1], #второй ряд
      [-1, 0, 0, 0, 0, -1],
      [-1, 0, 0, 0, 0, -1], #4 ряд
      [-1,-1,-1,-1,-1, -1]]#мнимый защитный край
# -1 -1 -1 -1 -1  перевёрнуто доп поля для того что бы начало было в (1; 1), а конец в (4; 4)
# -1  1  1  1  1
# -1  0  0  0  0
# -1  0  0  0  0
# -1  0  0  0  0



moves=[[],[],[],[]] #очень важная штука, десять раз подумать прежде чем менять

#movesSolve=[] #
#movesMax=[]  #ходы для решения являются максимальными, не требуется вторай список
#result=0
#maxResult = 0
#figurePosition = Figure(1,4,1) #что это?

# orderFigures=['red', 'blue', 'green', 'yellow']
# positionFigures = ['green','blue', 'yellow', 'red']
color_to_figure={
    'red': 's', #l      k       s       f
    'blue': 'l',#blue  green    red    yellow
    'green': 'k',#
    'yellow': 'f'#
}

def appendMoves(figure): #
    global moves
    type = figure.getType()
    if type == 'k': moves[0].append(figure)
    elif type == 'f': moves[1].append(figure)
    elif type == 's': moves[2].append(figure)
    elif type == 'l': moves[3].append(figure)

def getFromMoves(type): #
    global moves
   # type = mainFig.getType()
    if type == 'k': return moves[0]
    elif type == 'f': return moves[1]
    elif type == 's': return moves[2]
    elif type == 'l': return moves[3]
#проверяем здесь можно ли ферзю и ладбе сдвинуть по горизантали, учитывая фигуры, которые стот в начальном ряду
#todo где надо поменть figure.y на figure._yStart(необяз), но воспринимать код будет проще
def move(mainFig):
    global moves, maze
    order = mainFig._order
    type = mainFig.getType()
   # print('mainPos')
    #if mainFig.getType == 'f': print(mainFig._xStart, mainFig._yStart)
    nextPosition = Figure(mainFig._xStart, type, order, mainFig._yStart, mainFig._yStart, mainFig._xStart)
    #print(nextPosition._yStart, nextPosition._xStart)
    # maze.reverse()
    # for i in range(0, 5):
    #     print(*maze[i])
    # maze.reverse()
    if type == 'k':
        for y in range(1, 5):
            for x in range(1,5):
                if maze[y][x]==0:
                    if abs(y - mainFig.y)+abs(x - mainFig.x)==3 and mainFig.y!=y and mainFig.x!=x:
                        nextPosition.x=x
                        nextPosition.y=y
                        appendMoves(Figure(nextPosition.x, nextPosition._type, nextPosition._order, nextPosition.y,nextPosition._yStart, nextPosition._xStart))
                        # print('k print y x',y, x)
                        # print(mainFig.y, mainFig.x)
                        #nextPosition.print()
    elif type == 'l':
        for y in range(1, 5):
            if maze[y][mainFig._xStart] == 0 and (y - mainFig.y) % 2 == order % 2:
                    nextPosition.x = mainFig._xStart
                    nextPosition.y = y
                    appendMoves(Figure(nextPosition.x, nextPosition._type, nextPosition._order, nextPosition.y,nextPosition._yStart, nextPosition._xStart))
                #nextPosition.print()
        for x in range(1, 5):
            if isFreePathToX_YStart(mainFig, x) and (x - mainFig.x) % 2 == order % 2:
                    nextPosition.x = x                                                  #ладья может сдвинуться в начальном ряду,
                    nextPosition.y = mainFig._yStart                                   #если клетки свободны и не мешают ей
                    appendMoves(Figure(nextPosition.x, nextPosition._type, nextPosition._order, nextPosition.y,nextPosition._yStart, nextPosition._xStart))
            # else:
            #     nextPosition.x = x
            #     nextPosition.y = mainFig._yStart
            #     appendMoves(Figure(nextPosition.x, type, order, nextPosition.y))
                #nextPosition.print()
    elif type == 's':
        i = 6  #на первой итерации надо 6, а на последующих на 2 меньше, это расстояние между позициями
        if mainFig.x + 3 <= 4:
            j = mainFig.x + 3  # находим крайнюю точку в которую можно встать
        else:
            j = mainFig.x - 3
        for y in range(4, 1, -1):
            for x in range(j, 5, i):  # будет проверять слегка лишнего, но if писать бессмысленно, столько же действий
                if x < 1: continue
                if maze[y][x] == 0 and (x - mainFig.x) % 2 == order % 2:  # в каждом ряду по две клетки на это и можно написать if
                    nextPosition.x = x
                    nextPosition.y = y
                    appendMoves(Figure(nextPosition.x, nextPosition._type, nextPosition._order, nextPosition.y,nextPosition._yStart, nextPosition._xStart))
                   # nextPosition.print()
            i -= 2
            j+=1
            # if j >= 0: j+= 1 #j += 1 * (-(j/abs(j)))
            # else: j-=1
    elif type == 'f':
        i = 6  #на первой итерации надо 6, а на последующих на 2 меньше, это расстояние между позициями
        if mainFig.x + 3 <= 4:
            j = mainFig.x + 3  # находим крайнюю точку в которую можно встать
        else:
            j = mainFig.x - 3
        for y in range(4, 1, -1):
            for x in range(j, 5, i):  # будет проверять слегка лишнего, но if писать бессмысленно, столько же действий
                if x < 1: continue
                if maze[y][x] == 0 and (x - mainFig.x) % 2 == order % 2:  # в каждом ряду по две клетки на это и можно написать if
                    nextPosition.x = x
                    nextPosition.y = y
                    appendMoves(Figure(nextPosition.x, nextPosition._type, nextPosition._order, nextPosition.y,nextPosition._yStart, nextPosition._xStart))
                   # nextPosition.print()
            i -= 2
            if j <= 0: j+= 1
            else: j-=1
        for y in range(1, 5):
            if maze[y][mainFig.x] == 0 and (y - mainFig.y) % 2 == order % 2:
                # if y==1:
                #     nextPosition.x = mainFig.x
                #     nextPosition.y = y
                #     appendMoves(Figure(nextPosition.x, type, order, nextPosition.y))
                nextPosition.x = mainFig._xStart
                nextPosition.y = y
               # print(nextPosition.y, nextPosition.x)
                appendMoves(Figure(nextPosition.x, nextPosition._type, nextPosition._order, nextPosition.y,nextPosition._yStart, nextPosition._xStart))
                #nextPosition.print()
        for x in range(1, 5):
            if isFreePathToX_YStart(mainFig, x) and (x - mainFig.x) % 2 == order % 2:
                nextPosition.x = x                    #ферзь может сдвинуться в начальном ряду,
                nextPosition.y = mainFig._yStart                                   #если клетки свободны и не мешают ей
               # print(nextPosition.y, nextPosition.x)
                appendMoves(Figure(nextPosition.x, nextPosition._type, nextPosition._order, nextPosition.y,nextPosition._yStart, nextPosition._xStart))
               # nextPosition.print()

def fillMoves(positionFigures):
   # global positionFigures, orderFigures
    for i in range(0, 4):
        move(positionFigures[i])#после просчёта освободить начальную ячейку так как сдвинулась, нужно для ладьи
        maze[positionFigures[i].y][positionFigures[i].x] =0

def isNotEqual(a, b, c, d):
    listChecker =[a,b,c,d]
    setChecker = set(listChecker)
   # print(listChecker, setChecker)
    if len(listChecker) == len(setChecker): return True
    else: return False

def isFreePathToX_YStart(mainFig, positionX):
    if mainFig._xStart == positionX: return False
    distance = abs(positionX - mainFig._xStart)
    freeCelss = 0
    k = 1
    if mainFig._xStart > positionX: k=-1
    for i in range(mainFig._xStart + 1*k, positionX + 1*k, 1*k): #если позиция фигуры больше, чем проверяемая, то разница будет отрицательная, а шаг -1
        if maze[1][i] == 0:
            freeCelss+=1
    if freeCelss == distance: return True
    else: return False

def isFreePath(mainFig, *figures): #figures - кортеж
    if len(figures) == 0: return True
    if mainFig.getType() == 's':
        for i in range(0, len(figures)):
            if( ((figures[i].x < mainFig.x and figures[i].x > mainFig._xStart)
                or (figures[i].x > mainFig.x and figures[i].x < mainFig._xStart))
                and (abs(figures[i].x - mainFig._xStart) == abs(figures[i].y - mainFig._yStart)) ):
                    return False

    elif mainFig.getType() == 'l':
        for i in range(0, len(figures)):
            if( (figures[i].x == mainFig.x and figures[i].y > mainFig._yStart and figures[i].y <= mainFig.y)
                or (figures[i].y == mainFig.y and figures[i].x > mainFig._xStart and figures[i].x <= mainFig.x)
                or (figures[i].y == mainFig.y and figures[i].x < mainFig._xStart and figures[i].x >= mainFig.x) ):
                return False
    elif mainFig.getType() == 'k': return True
    elif mainFig.getType() == 'f':
        mainFig._type = 'l'
        if isFreePath(mainFig, *figures) == False:
            mainFig._type = 'f'
            return False
        mainFig._type = 's'
        if isFreePath(mainFig, *figures) == False:
            mainFig._type = 'f'
            return False
        mainFig._type = 'f'
    return True

#проверяет может ли робот проехать по путям расставления фигур
def isAllPathFree(*figures):
    maze = [[-1, -1, -1, -1, -1, -1],  # мнимый защитный край
            [-1, 'l', 'k', 's', 'f', -1],  # первый ряд
            [-1, 0, 0, 0, 0, -1],  # второй ряд
            [-1, 0, 0, 0, 0, -1],
            [-1, 0, 0, 0, 0, -1],  # 4 ряд
            [-1, -1, -1, -1, -1, -1]]  # мнимый защитный край
    figuresPosition = (Position(figures[0].y, figures[0].x), Position(figures[1].y, figures[1].x),
                       Position(figures[2].y, figures[2].x), Position(figures[3].y, figures[3].x) )
    currentPos = Position(figures[0]._yStart, figures[0]._xStart)
    for i in range(1, 3):
        path, _ = pathFinder.findPath(deepcopy(maze), currentPos, figuresPosition[i])
        if path == None: return False
        maze[currentPos.y][currentPos.x] = 0
        maze[figuresPosition[i].y][figuresPosition[i].x] = 'f'
        for i in range(len(path)):
            print(path[i].y, path[i].x)
        if len(path) >= 2: currentPos = path[-2]
        else: currentPos = path[0]
    return True

# функция определяющая всё ли ок с таким построением фигур
# т.е. можно ли так сдвинуть фигур в нужном порядке и результат при таком сдвиге
def isOk(figure1, figure2, figure3, figure4):
    #print('isNotEqual?', isNotEqual((figure1.y, figure1.x), (figure2.y, figure2.x), (figure3.y, figure3.x), (figure4.y, figure4.x)))
    if (isNotEqual((figure1.y, figure1.x), (figure2.y, figure2.x), (figure3.y, figure3.x), (figure4.y, figure4.x))):
        if( (isFreePath(figure1)  # (a, b, c) - кортеж#
            and isFreePath(figure2, figure1)
            and isFreePath(figure3, figure1, figure2)
            and isFreePath(figure4, figure1, figure2, figure3))):
                return True
    return False

#заполняет поле cost для каждой фигуры
def findCosts(figures): #кортеж
    for i in range(0, 4):
        if figures[i].getType() == 'k':
            figures[i].cost = 3 #But ↓
            if figures[i].x == figures[i]._xStart and figures[i].y == figures[i]._yStart:
                #так нужно для коня,
                # остальные фигуры могут это посчитать
                figures[i].cost = 0
            continue
        if figures[i]._yStart == figures[i].y:
            figures[i].cost = abs(figures[i].x - figures[i]._xStart)
        else:
            figures[i].cost = abs(figures[i].y - figures[i]._yStart)

def findResult(orderFigures):
    movesSol = [Figure(-1), Figure(-1), Figure(-1), Figure(-1)]
    costMax = 0 #не нейтральный, но у нас меньше нуля не бывает
    for figure1 in getFromMoves(orderFigures[0]):
        for figure2 in getFromMoves(orderFigures[1]):
            for figure3 in getFromMoves(orderFigures[2]):
                for figure4 in getFromMoves(orderFigures[3]):#O = 10^4 #можно применить дп и не считать cost заново для каждой фигуры
                   # print('isok')
                    #print(isOk(figure1, figure2, figure3, figure4))
                    if isOk(figure1, figure2, figure3, figure4):
                        if isAllPathFree(figure1, figure2, figure3, figure4):
                            figures = (figure1, figure2, figure3, figure4)
                            findCosts(figures)

                            cost = figure1.cost + figure2.cost + figure3.cost + figure4.cost
                            #print('current cost', cost)
                            if cost > costMax:
                                for i in range(0, 4):
                                    movesSol[i] = figures[i]
                                costMax = cost
    #print('maxCost', costMax)
    return movesSol
#минусы isOk:
# 1.если обнаруживает, что что-то совпадает, а совпадает два начальных, то продолжит перебирать 3 и 4 дальше
# 2. если 2ая фигура перекрывает путь для 1ой, всё равно перебираем варианты, хоть они уже и заведомо не верны
# решение: писать флаги
# минус решения: прибавка в скорости незначительная?


#сюда попадают сырые значения, ещё в цветах
def solve(orderFigures, positionFigures): #fillMoves заполняет moves в нужном порядке для каждой фигуры
    orderFigures = [color_to_figure[orderFigures[i]] for i in range(0, 4)]  # то в каком порядке перемещать ТИПЫ фигур, список строк
    positionFigures = [Figure(i, color_to_figure[positionFigures[i - 1]],  # то как фигуры стоят на поле объекты, список Figure
                              orderFigures.index(color_to_figure[positionFigures[i - 1]]) + 1) for i in range(1, 5)]
    
    for figure in positionFigures:
        print(figure.getType(), figure._yStart, figure._xStart)
    
    
    # x фигуры соответствует порядку считывания, в списке фигуры стоят тоже в порядке считывания, поэтому
    # её x равен индексу элемента в списке + 1
    # а порядок в котором её надо сдвинуть соответствует её индексу в списке порядка движения
    print('on board', end= ' ')
    for i in range(4):
        print(positionFigures[i].getType(), end=' ')
    print('\norder', end='    ')
    print(*orderFigures)
    positionFigures.sort(key=lambda x: x._order, reverse=False) #теперь positionFigures содержит фигуры в порядке их движения

    appendMoves(positionFigures[3])#чтобы была возможность оставить последнюю фугуру на месте
    fillMoves(positionFigures)
    s = getFromMoves('s')
    for pos in s:
        print(pos.y, pos.x)
    return findResult(orderFigures)

