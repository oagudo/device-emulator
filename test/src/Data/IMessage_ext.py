#!/usr/bin/env python

import sys

sys.path.append('../../../build/model')

from DeviceEmulatorModel_ext import IMessage

class PythonDerived(IMessage):
    def to_string(self):
        return "PythonDerived to_string method"

p = PythonDerived()
print p.to_string()
