# Adafruit-demos
Adafruit Circuit Playground projects

The demo fftry uses the onboard microphone to pick up sound, then uses the fast fourier transform feature to split
the sound into frequency buckets. In each cycle the buckets have a different value corresponding to the amplitude
heard for that frequency range. This information is written to a buffer then the buffer is used to change the color
and brightness of the lights. Using the two onboard buttons we can cycle between different color modes stored in
a circular linked list defined in ll.h.
