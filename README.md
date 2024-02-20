# CoalFurnaceController

This project utilizes an Arduino UNO R3 microcontroller as its base to control the pump and blower of a coal furnace. The repository includes all essential files and documents, detailing every step necessary for you to build it yourself.

#### Repository structure:
\PPT - This directory contains the presentation of the project in its initial, intermediate, and final stages. 

\SCH - This directory contains the complete project in Fusion 360 (along with its backup files) with all necessary libraries. It also contains PNG files with schematic and PCB layers.  

\SRC - This directory contains the source code, along with the necessary libraries required for compilation.  

\DOC\SPR - The directory contains all necessary documentation files for the project.  

## Other notes:

##### Hardware:  
Arduino UNO R3  
Breadboard 30  
USB B Cable  
Self-adhesive membrane keyboard 4x4 - 16 keys  
Temperature sensor DS18B20  
Diodes x 2  
Resistors 2x 330 Ohms, 1x 4.7 kOhms  
Pin Expander - Pcf8574 - I2C bus  
84x48 Nokia 5110 3310 display (pcd8544)  

##### Theory:
https://www.elektroda.pl/rtvforum/topic3668747.html   
https://forbot.pl/blog/kurs-elektroniki-prawa-ohma-i-kirchhoffa-id3986  

##### Schematic notes:
Project scanner I2C - checking ports ADDRESS 0x20  
(5-1.7) / 0.01 = 330 Ohms i.e., circuit power - V diode / diode operating range 0.005 to 0.02 = resistor value   
