Introduction
---
In this project our objective was to develop a proximity sensor which can measure the distance to a given object accurately and display it on an LCD screen and to indicate when a given distance typing on a keypad to the instrument is reached.

• The accuracy achieved by the instrument is a key component and it is designed to achieve a high accuracy.

• The proximity sensor was tested using many different obstacles such as those with rough, black and smooth surfaces and those which are large is size and vice versa. The test results are carefully observed plotted and measures have been taken to standardize those test results.

• 16F887 microcontroller PIC is used as the main component where it is programmed with the MPLAB IDE. Apart from the microcontroller, an Ultrasonic sensor and an IR sensor is used to detect the target object. Furthermore, a laser beam is used to make it easy for the sensors to align the target object. A buzzer indicates that the proximity meter has arrived at the specified distance.

• MPLAB is used to program the device as the IDE which contains C language. Further
Proteus 8.0 professional was used to simulate the circuits and the enclosure was initially designed using SolidWorks.

• The structure of the proximity sensor is a rectangular box with an LED screen, keypad, ultrasonic sensor, IR sensor, laser, a reset button and power indicate LED seen from outside the enclosure.

• There are two functionalities of the proximity meter. One is to measure the distance to a given object. The other is sensing a given distance. Both sensors will take n consecutive values and those readings with a large deviation to the previous value is omitted. The mean of the accurate readings is taken for processing.
