#!/usr/bin/env python

import sys

sys.path.append('../../../../build/kernel')

from DeviceEmulatorKernel_ext import ErrorState, FinishedState, NotStartedState, RunningState, StoppedState

# Error state

error_description = "error description msg"
error_state = ErrorState(error_description)
assert error_state.to_string() == "Error"
assert error_state.allow_to_continue() == False


# Finished state

finished_state = FinishedState()
assert finished_state.allow_to_continue() == False

# Not started state

not_started_state = NotStartedState()
assert not_started_state.allow_to_continue() == False

# Running state

running_state = RunningState()
assert running_state.allow_to_continue() == True

# Stopped state

stopped_state = StoppedState()
assert stopped_state.allow_to_continue() == False
