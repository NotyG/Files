import chessSolution
maze=[[-1,-1,-1,-1,-1, -1], #мнимый защитный край
      [-1, 0, 0, 0, 0, -1], #первый ряд
      [-1, 0, 0, 0, 0, -1], #второй ряд
      [-1, 0, 0, 0, 0, -1],
      [-1, 0, 0, 0, 0, -1], #4 ряд
      [-1,-1,-1,-1,-1, -1]]#мнимый защитный край

orderFigures=['green', 'blue', 'yellow', 'red']
positionFigures = ['blue', 'green', 'red', 'yellow']
solution = chessSolution.solve(orderFigures, positionFigures) #solution - список объектов Figure
# print(solution[0]._yStart, solution[0]._xStart)
for i in range(0, 4):
    maze[solution[i].y][solution[i].x] = solution[i].getType()
for i in range(0, 6):
    print(*maze[i])