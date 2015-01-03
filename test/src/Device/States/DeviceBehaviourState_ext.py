#!/usr/bin/env python

import sys

sys.path.append('../../../../build/model')

from DeviceEmulatorModel_ext import ErrorState, FinishedState, NotStartedState, RunningState, StoppedState

# Error state

assert ErrorState.instance().to_string() == "Error"

# Finished state

assert FinishedState.instance().to_string() == "Finished"

# Not started state

NotStartedState.instance().to_string() == "NotStarted"

# Running state

assert RunningState.instance().to_string() == "Running"

# Stopped state

assert StoppedState.instance().to_string() == "Stopped"
