class A():
    def __init__(self, cd):
        self.west = 1
        self.east = 3
        self.north = 4
        self.south = 2
        self._currentDir = cd
    def _getDirAfterTurn(self, angle):
        '''pls angle only multiple to 90'''
        directions = [self.east, self.south, self.west, self.north]
        angle = angle // 90
        newDir = (abs(angle) % 4) * (angle // abs(angle)) + directions.index(self._currentDir)
        newDir = newDir % 4
        return directions[newDir]
rob = A(4)
print(rob._getDirAfterTurn(180))