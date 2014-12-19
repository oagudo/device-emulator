#!/usr/bin/env python

import sys

sys.path.append('../../../../build/kernel')

from DeviceEmulatorKernel_ext import ErrorState, FinishedState, NotStartedState, RunningState, StoppedState

# Error state

error_description = "error description msg"
error_state = ErrorState(error_description)
assert error_state.to_string() == "Error"
assert error_state.allow_to_continue() == False
assert error_state.get_error_msg() == error_description


# Finished state

finished_state = FinishedState()
assert finished_state.allow_to_continue() == False
assert finished_state.get_error_msg() == ""

# Not started state

not_started_state = NotStartedState()
assert not_started_state.allow_to_continue() == False
assert not_started_state.get_error_msg() == ""

# Running state

running_state = RunningState()
assert running_state.allow_to_continue() == True
assert running_state.get_error_msg() == ""

# Stopped state

stopped_state = StoppedState()
assert stopped_state.allow_to_continue() == False
assert stopped_state.get_error_msg() == ""
