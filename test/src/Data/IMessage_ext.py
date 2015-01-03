#!/usr/bin/env python

import sys

from DeviceEmulatorModel_ext import IMessage

class PythonDerived(IMessage):
    def to_string(self):
        return "PythonDerived to_string method"

p = PythonDerived()
assert p.to_string() == "PythonDerived to_string method"
