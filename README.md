# tiva-simple-stepper
super simple stepper library for h bridge drivers

None of this has been tested yet =)

This library is a simple C interface for H-bridge stepper drivers (AIN1, AIN2, BIN1, BIN2 inputs)

Due to the reqs of the application I'm using this for it currently only supports whole step mode.

There is an automatic ramp velocity profile generator.

Each stepper motor will need it's own hardware timer.
