# Arduino Fan Display
## Prototype lol

DIY device I made using an Arduino Uno and some free time. Device was resurrected with brand new refactored firmware (a lot of time passed from the moment this device was originally created).  

sketch.ino  - Arduino Sketch. outputArray contains binary image to be displayed.  
img2bin.py  - Python Script. Converts image to the outputArray format.  

Each LED owns his own bit in int value (1led=1; 2led=2; 3led=4 e.t.c.). Sum of active bits is the value of vertical line to be displayed in one time unit.  
Phototransistor checks for the new lap and triggers the controller using interrupts.

* Proof that this one actually works:  
![Oops. Image was here](https://github.com/DV1X3R/fan-display/raw/master/img/demo.gif)  

* Photo  
![Oops. Image was here](https://github.com/DV1X3R/fan-display/raw/master/img/photo.jpg)  

* Schema  
![Oops. Image was here](https://github.com/DV1X3R/fan-display/raw/master/img/schema.jpg)  
