### Stepper Motor Addition to Lego Orrery

This design replaces the hand-crank operation of the Lego "Planet Earth and Moon in Orbit" set with a 28BYJ-48 stepper motor.

There are 2 parts to print:

- A shaft coupler between the stepper and a Technic axle at the input crank
  - A short Lego axle (you must provide, not printed) needs to be inserted to replace the hand-crank brown axle.
- A 28BYJ-48 stepper motor mount that slides onto the Lego model, no screws required to attach it to the model.
  - 2x M4 nut + screws needed to attach the motor to the part

The print parameters are not critical. Just make sure you use supports on the coupler and part. There are 2mm push-out holes to help remove supports where they may be added using a 1-1.5mm allen key or similar hard shaft to push it out.

Once the stepper is on, use your favorite method to drive the stepper.

The Arduino sketch firmware is in the `Firmware` directory.

The firmware is made to work on Teensy LC, but can be adapted to
any Arduino.

It requires only the ULN2003A-based driver board.

Links:

- [Thingiverse](https://www.thingiverse.com/thing:6900611)

