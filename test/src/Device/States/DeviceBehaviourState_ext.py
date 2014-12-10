#!/usr/bin/env python

import sys

sys.path.append('../../../../build/kernel')

from DeviceEmulatorKernel_ext import ErrorState, FinishedState

# Error state

error_description = "error description msg"
error_state = ErrorState(error_description)
assert error_state.is_error_state() == True
assert error_state.allow_to_continue() == False
assert error_state.get_error_msg() == error_description


# Finished state

finished_state = FinishedState()
assert finished_state.is_error_state() == False
assert finished_state.allow_to_continue() == False
assert finished_state.get_error_msg() == ""
