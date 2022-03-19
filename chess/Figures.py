# -*- coding: utf-8 -*-
class Figure():
    def __init__(self, x, type, direction = 1): #потому что никто не знает, что такое direction
        self._x = x
        self._y = 0
        self._xStart = x
        self._yStart = 0
        self._type = type
        self._xOld = None
        self._yOld = None
        self.direction = direction
        self.cost = None #чтобы вначале стоимости не было

    def getX(self):
        return self._x
    def getY(self):
        return self._y
    def getXStart(self):
        return self._xStart
    def getYStart(self):
        return self._yStart
    def getType(self):
        return self._type

    def setX(self, x):
        self._xOld = self._x
        self._x = x
    def setY(self, y):
        self._yOld = self._y
        self._y = y
    def setXStart(self, x):
        if self._xStart < 0:
            self._xStart = x
        else:  raise RuntimeError("Cannot set _xStart, _xStart was declared before, if you want to change _xStart it must be negative earlier")


