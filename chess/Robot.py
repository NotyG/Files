from pybricks.tools import wait
from pybricks.parameters import Direction
class Robot:
    def __init__(self, driveBase, line_sensor_left, line_sensor_right,
                 left_motor, right_motor,
                 gyro_sensor, color_sensor,
                 turnSpeed, baseSpeed,
                 currentPos, currentDir,
                 coincidence = 25):
        '''currentDir:\n
            west 1;\n
            east 3;\n
            north 2;\n
            south 4;\n
            coincidence is using in goToBorder()
            '''
        self.west = 1
        self.east = 3
        self.north = 4
        self.south = 2
        self.driveBase = driveBase
        self.line_sensor_right = line_sensor_right
        self.line_sensor_left = line_sensor_left
        self.left_motor = left_motor
        self.right_motor = right_motor
        self.gyro_sensor = gyro_sensor
        self.color_sensor = color_sensor

        self.isHaveACube = False
        self.coincidence = coincidence
        self._currentPos = currentPos
        self._currentDir = currentDir
        self.gyro_sensor.reset_angle(0)
        self.turnSpeed = turnSpeed
        self.baseSpeed = baseSpeed

    def _getTurnAngle(self, endPos):
        '''будет работать если x или y совпадает с позицией робота,
        Не меняет _currentDir на новое, это делает turn()'''
        # print(self._currentPos.y, self._currentPos.x)
        # print(endPos.y, endPos.x)
        dir = None
        turnAngle = 0
        dir = self._getAbsDirOfPosition(endPos)
        print('dir in getAngle', dir)
        if dir:
            turnAngle = 90 * (self._currentDir - dir)
            if abs(turnAngle) > 180: 
                turnAngle = (360 - abs(turnAngle)) * ((-turnAngle) / abs(turnAngle))
            #self._currentDir = dir
        # print('turnAngle', turnAngle)
        return turnAngle

    def chooseOptimalPath(self, paths):
        currentPos = self._currentPos
        minStraights, minTurns = 10000,10000  #FIXME TODO не нейтральное, но путь не может быть меншье 100000
        optimalPath = None
        for path in paths:
            currentStraights, currentTurns = self._countMoves(path)
            if (currentStraights + currentTurns) < (minStraights + minTurns): #currentstraight всегда одинаковый - предположение
                optimalPath = path
                # if currentTurns < minTurns:
                #     optimalPath = path
        return optimalPath

    def _countMoves(self, path):
        currentPos = self._currentPos
        countOfStraights = 0
        countOfTurns = 0
        for pos in path:
            if pos.x == self._currentPos.x and pos.y == self._currentPos.y:
                continue
            angle = self._getTurnAngle(pos)
            if angle == 180 and not self.isHaveACube:
                #self._cellMoveBack()
                countOfStraights += 1
            else:
                countOfTurns += abs(angle//90)
                countOfStraights += 1
                #self.turn(angle) #self._getTurnAngle(endPos)
                #self._cellMove()
            self._currentPos = pos
        self._currentPos = currentPos
        return countOfStraights, countOfTurns

    def moveToNearPosition(self, endPos):
        if endPos.x == self._currentPos.x and endPos.y == self._currentPos.y:
            return None
        #dir = self._getAbsDirOfPosition(endPos)
        #print(dir)
        #if abs(self._currentDir - dir) == 2 and not self.isHaveACube: #направления противоположны
        angle = self._getTurnAngle(endPos)
        if angle == 180 and not self.isHaveACube:
            self._cellMoveBack()
        else:
            self.turn(angle) #self._getTurnAngle(endPos)
            self._cellMove()
        self._currentPos = endPos
    
    def _getAbsDirOfPosition(self, endPos):
        '''возвращает направление к endPos, не учитывая направление робота
        endPos - смежная с текущей клеткой'''
        dir = None
        if endPos.x > self._currentPos.x:
            dir = self.east  # 'east'
        elif endPos.x < self._currentPos.x:
            dir = self.west  # 'west'
        elif endPos.y > self._currentPos.y:
            dir = self.south  # 'south'
        elif endPos.y < self._currentPos.y:
            dir = self.north  # 'north'
        return dir

    def turn(self, angle):
        '''turning by gyroscope\n
        zero | dont turn\n
        positive -> right\n
        negative <- left
        angle % 90 == 0'''
        if angle == 0: return None
        if angle > 0:
            dir = 1
        elif angle < 0:
            dir = -1
        self._currentDir = self._getDirAfterTurn(angle)
        self.gyro_sensor.reset_angle(0)
        self.driveBase.stop()
        #print('afterStop')
        angle -= 4 * dir  # там датчик криво стоит, поэтому так
        speedL = self.turnSpeed * dir
        speedR = self.turnSpeed * -1 * dir
        while abs(self.gyro_sensor.angle()) < abs(angle):
            self.left_motor.run(speedL)
            self.right_motor.run(speedR)
            # print(self.gyro_sensor.angle())
        self.left_motor.run(-speedL)
        self.right_motor.run(-speedR)
        wait(10)
        #print('afterCycle')
        self.fastStop()
        self.gyro_sensor.reset_angle(0)

    def moveBy(self, path):
        '''you CANNOT use Position as argument, you have to use a list of Position
        if you want to move to near position use moveToNearPosition(endpos)'''
        for position in path:
            self.moveToNearPosition(position)

#я не знаю как такое написать без спагетти
    def align(self, nextPos):
        if self._currentDir == self.north: 
            if self._currentPos.y - 1 == 0:
                if self._currentPos.x + 1 == 5:
                    self.turn(-90)
                    self._currentDir = self._getDirAfterTurn(-90)
                    self._align(-1, nextPos)
                elif self._currentPos.x - 1 == 0:
                    self.turn(90)
                    self._currentDir = self._getDirAfterTurn(90)
                    self._align(1, nextPos)
                else:
                    self.turn(90)
                    self._currentDir = self._getDirAfterTurn(90)
                    self._align(1, nextPos)
            else:
                if self._currentPos.x + 1 == 5:
                    self._align(-1, nextPos)
                elif self._currentPos.x - 1 ==0:
                    self._align(1, nextPos)
                else: 
                    self._align(1, nextPos)
        elif self._currentDir == self.south:
            if self._currentPos.y + 1 == 5:
               # self.align()
                if self._currentPos.x + 1 == 5:
                    self.turn(90)
                    self._currentDir = self._getDirAfterTurn(90)
                    self._align(1, nextPos)
                elif self._currentPos.x - 1 == 0:
                    self.turn(-90)
                    self._currentDir = self._getDirAfterTurn(-90)
                    self._align(-1, nextPos)
                else:
                    self.turn(90)
                    self._currentDir = self._getDirAfterTurn(90)
                    self._align(1, nextPos)
            else:
                if self._currentPos.x + 1 == 5:
                    self._align(1, nextPos)
                elif self._currentPos.x - 1 == 0:
                    self._align(-1, nextPos)
                else:
                    self._align(1, nextPos)
        elif self._currentDir == self.east:
            if self._currentPos.x + 1 == 5:
                if self._currentPos.y - 1 == 0:
                    self.turn(90)
                    self._currentDir = self._getDirAfterTurn(90)
                    self._align(1, nextPos)
                elif self._currentPos.y + 1 == 5:
                    self.turn(-90)
                    self._currentDir = self._getDirAfterTurn(-90)
                    self._align(-1, nextPos)
                else: 
                    self.turn(90)
                    self._currentDir = self._getDirAfterTurn(90)
                    self._align(1, nextPos)
            else:
                if self._currentPos.y - 1 == 0:
                    self._align(1, nextPos)
                elif  self._currentPos.y + 1 == 5:
                    self._align(-1, nextPos)
                else:
                    self._align(1, nextPos)
        elif self._currentDir == self.west:
            if self._currentPos.x - 1 == 0:
                if self._currentPos.y -1 == 0:
                    self.turn(-90)
                    self._currentDir = self._getDirAfterTurn(-90)
                    self._align(-1, nextPos)
                elif self._currentPos.y + 1 == 5:
                    self.turn(90)
                    self._currentDir = self._getDirAfterTurn(90)
                    self._align(1, nextPos)
                else:
                    self.turn(90)
                    self._currentDir = self._getDirAfterTurn(90)
                    self._align(1, nextPos)
            else:
                if self._currentPos.y -1 == 0:
                    self._align(-1, nextPos) 
                elif self._currentPos.y + 1 == 5:
                    self._align(1, nextPos)
                else:
                    self._align(1, nextPos)

    def _getDirAfterTurn(self, angle):
        '''pls angle only multiple to 90'''
        #список имитирует стрелку, если добавить 1 к северу, то окажешься на другой стороне списка, то есть на востоке
        directions = [self.east, self.south, self.west, self.north]
        angle = angle // 90
        newDir = (abs(angle) % 4) * (angle // abs(angle)) + directions.index(self._currentDir)
        newDir = newDir % 4
        return directions[newDir]

    def _align(self, dirOfAlign = 1, nextPos = None):
        self.goToBorder()
        self.driveBase.straight(-85)
        self.turn(dirOfAlign * 90)

        self.goToBorder()
        print('in align')
        print('nextPos')
        print(nextPos.y, nextPos.x)
        print(self._getAbsDirOfPosition(nextPos))
        print('cdir')
        print(self._currentDir)
        print(self._getDirAfterTurn(dirOfAlign*90))
        if self._getAbsDirOfPosition(nextPos) == self._getDirAfterTurn(dirOfAlign*90): 
            self._currentDir = self._getDirAfterTurn(dirOfAlign*90)
            self.driveBase.straight(-30)
        else:
            self.driveBase.straight(-85)
            self.turn(-dirOfAlign * 90)

    def turnTo0(self):
        '''turning the robot to gyroscope zero point'''
        self.turn(-(self.gyro_sensor.angle()))

    def lineDetectRedCenter(self, velocity, distance, side = 1, mode = None):
        RED = 90
        WHITE = 100
        threshold = RED #95  # (RED + WHITE) / 2 #просто красный
        if velocity <= 100: PROPORTIONAL_GAIN = 3
        elif velocity> 100: PROPORTIONAL_GAIN = 6
        PROPORTIONAL_GAIN *= side  # 1.2 #3
        self.driveBase.reset()
        if mode != 1:
            while self.driveBase.distance() < distance:
                deviation = self.color_sensor.reflection() - threshold
                turn_rate = PROPORTIONAL_GAIN * deviation
                self.driveBase.drive(velocity, turn_rate)
            self.driveBase.stop()
            self.fastStop()
        else:
            deviation = self.color_sensor.reflection() - threshold
            turn_rate = PROPORTIONAL_GAIN * deviation
            self.driveBase.drive(velocity, turn_rate)
            
    def lineDetectRedRight(self, velocity, distance, side=1, mode = None):
        '''mode = 1 if you want to disable inside cycle\n
            side - where is the line?\n
            right: side=1\n
            left:side=- 1'''
        RED = 90
        WHITE = 100
        threshold = RED #95  # (RED + WHITE) / 2 #просто красный
        if velocity <= 100: PROPORTIONAL_GAIN = 3
        elif velocity> 100: PROPORTIONAL_GAIN = 6
        PROPORTIONAL_GAIN *= side  # 1.2 #3
        self.driveBase.reset()
        if mode != 1:
            while self.driveBase.distance() < distance:
                deviation = self.line_sensor_right.reflection() - threshold
                turn_rate = PROPORTIONAL_GAIN * deviation
                self.driveBase.drive(velocity, turn_rate)
            self.driveBase.stop()
            self.fastStop()
        else:
            deviation = self.line_sensor_right.reflection() - threshold
            turn_rate = PROPORTIONAL_GAIN * deviation
            self.driveBase.drive(velocity, turn_rate)

    def lineDetectRedLeft(self, velocity, distance, side=1, mode = None):
        '''mode = 1 if you want to disable inside cycle\n
            side - where is the line?\n
            right: side= -1 \n
            left: side = -1'''
        RED = 70
        WHITE = 90
        threshold = RED #95  # (RED + WHITE) / 2
        if velocity <= 100: PROPORTIONAL_GAIN = 3
        elif velocity> 100: PROPORTIONAL_GAIN = 6
        PROPORTIONAL_GAIN *= side  # 1.2 #3
        self.driveBase.reset()
        if mode != 1:
            while self.driveBase.distance() < distance:
                deviation = self.line_sensor_left.reflection() - threshold
                turn_rate = PROPORTIONAL_GAIN * deviation
                self.driveBase.drive(velocity, turn_rate)
            self.driveBase.stop()
            self.fastStop()
        else:
            deviation = self.line_sensor_left.reflection() - threshold
            turn_rate = PROPORTIONAL_GAIN * deviation
            self.driveBase.drive(velocity, turn_rate)
        
    def goToBorder(self, velocity = None, dir = 1):
        '''its work in white and black colors, other colors dont work'''\
        #утверждение выше требует проверки, так как код изменился полностью
        velocity = velocity or self.baseSpeed
        nowColor = (self.line_sensor_right.reflection() + self.line_sensor_left.reflection()) / 2
        #print('nowcolor', nowColor)
        while( abs(self.line_sensor_left.reflection() - nowColor) < self.coincidence
            and abs(self.line_sensor_right.reflection() - nowColor) < self.coincidence):
            self.driveBase.drive(velocity*dir, 0)
        self.driveBase.stop()
        self.fastStop()
        # print(self.line_sensor_left.reflection() - nowColor, self.line_sensor_right.reflection() - nowColor)
    #    print('isleft smaller?', self.line_sensor_left.reflection() - nowColor < self.line_sensor_right.reflection() - nowColor)
   #     print('is right smaller?', self.line_sensor_left.reflection() - nowColor > self.line_sensor_right.reflection() - nowColor)
        isLeftInCell = False
        isRightInCell = False
        while not(isLeftInCell and isRightInCell):
            # print('leftdev', abs(self.line_sensor_left.reflection() - nowColor))
            # print('rightdev', abs(self.line_sensor_right.reflection() - nowColor))
            if abs(self.line_sensor_left.reflection() - nowColor) > self.coincidence and not isLeftInCell:
                # print('leftIn')
                isLeftInCell = True
                self.left_motor.run(-10*dir)
                self.right_motor.run(40*dir) 
            if abs(self.line_sensor_right.reflection() - nowColor) > self.coincidence and not isRightInCell:
                # print('rightIn')
                isRightInCell = True
                self.right_motor.run(-10*dir)
                self.left_motor.run(40*dir)
        # print('im in')
        self.fastStop()       
        self.driveBase.straight(5*dir)
        self.driveBase.drive(0, 0)
        self.driveBase.stop()

    def fastStop(self):
        '''stops robot completely'''
        self.driveBase.stop()
        self.left_motor.brake()
        self.right_motor.brake()
        self.left_motor.stop()
        self.right_motor.stop()

    def _cellMoveBack(self):
        self.goToBorder(None, -1)
        self.driveBase.straight(-90)
        self.fastStop()
        
    def _cellMove(self):
        self.goToBorder()
        self.driveBase.straight(150)
        self.fastStop()