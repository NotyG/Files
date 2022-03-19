#!/usr/bin/env pybricks-micropython
# -*- coding: utf-8 -*-
from pybricks.parameters import Color, Direction
class Position:
    def __init__(self, y, x):
        self.y = y
        self.x = x


class Figure:
    def __init__(self, x,  type = None, order = None, y=1, yStart = None, xStart = None):
        '''yStart and xStart will be even you dont specify them '''
        self.y = y
        self.x = x
        self._xStart = xStart or x
        self._yStart = yStart or y
        self._type = type
        self._order = order
        #self.direction = direction
        self.cost = None #чтобы вначале стоимости не было
        #решение стоит рассматривать в целом, но удобнее когда цена объекта привязана к объекту
    # def print(self): #log
    #    # print(self.y,' ',self.x) #,' ',self.direction
    #     pass
    def getType(self):
        return self._type
