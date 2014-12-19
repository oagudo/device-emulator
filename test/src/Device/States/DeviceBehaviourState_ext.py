#!/usr/bin/env python

import sys

sys.path.append('../../../../build/kernel')

from DeviceEmulatorKernel_ext import ErrorState, FinishedState, NotStartedState, RunningState, StoppedState

# Error state

error_description = "error description msg"
error_state = ErrorState(error_description)
assert error_state.to_string() == "Error"

# Finished state

finished_state = FinishedState()
assert finished_state.to_string() == "Finished"

# Not started state

not_started_state = NotStartedState()
assert not_started_state.to_string() == "NotStarted"

# Running state

assert RunningState.instance().to_string() == "Running"

# Stopped state

stopped_state = StoppedState()
assert stopped_state.to_string() == "Stopped"
