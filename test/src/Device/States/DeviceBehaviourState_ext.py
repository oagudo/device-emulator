#!/usr/bin/env python

import sys

sys.path.append('../../../../build/kernel')

from DeviceEmulatorKernel_ext import ErrorState, FinishedState, NotStartedState, RunningState, StoppedState

# Error state

error_description = "error description msg"
error_state = ErrorState(error_description)
assert error_state.to_string() == "Error"

# Finished state

assert FinishedState.instance().to_string() == "Finished"

# Not started state

NotStartedState.instance().to_string() == "NotStarted"

# Running state

assert RunningState.instance().to_string() == "Running"

# Stopped state

assert StoppedState.instance().to_string() == "Stopped"
