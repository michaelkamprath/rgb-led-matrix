# Ardunio Driver for RGB LED Matrix

To use this driver in the Arduino IDE, add the folder `rgd-led-matrix-lib` as a library as described in [this document](https://www.arduino.cc/en/Guide/Libraries). 

This driver (now) uses SPI to transfer bits to the shift registers. The default wiring for connecting the RGB LED Matrix to an Arduino is:

| LED Matrix Connection | Arduino Pin |
|:-:|:-:|
| +5V | 5V |
| GND | GND |
| SER | 11 |
| CLK | 13 |
| LATCH | 5 |
| SER' | _unused_ |

