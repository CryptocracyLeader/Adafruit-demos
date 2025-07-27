# Adafruit-demos
Adafruit Circuit Playground projects

The demo fftry uses the onboard microphone to pick up sound, then uses the fast fourier transform feature to split
the sound into frequency buckets. In each cycle the buckets have a different value corresponding to the amplitude
heard for that frequency range. This information is written to a buffer then the buffer is used to change the color
and brightness of the lights. Using the two onboard buttons we can cycle between different color modes stored in
a circular linked list defined in ll.h.

ll is a folder containing some tests of the linked list implementation, and bin_therm uses the onboard thermometer
on the microcontroller to read the temperature then use the lights to display the temperature in binary and change 
color according to the temperature.

persistence is a work in progress project inspired by a proffesor I had who made a persistence of vision light stick
for burning man. I am attempting to recreate that albeit on a much smaller scale initially.
