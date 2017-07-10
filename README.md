# EBikeLight
Intuitive lightswitch with dimmer for ebikes

The whole point of this micro-project was to be able to dim my 12-80V LED lights. 

After many experiments, including voltage buck converters, and analog PWM motor speed controllers, I had this great idea.

Point is to PWM the battery voltage going directly to the lights. I used a MOSFET that can handle my battery volts (50v in my case),
feed the Arduino off a 5v source (bafang display USB output). It is really beatifully simple, and compact.

The code and buttons lets you adjust your dim, and flick the button between full beams and dimmed, just like a car. The arduino
will remember your settings.


See wiki for wiring and demo video.
