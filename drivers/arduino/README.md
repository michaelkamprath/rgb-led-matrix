# Ardunio Driver for RGB LED Matrix

To use this driver in the Arduino IDE, add the folder `rgd-led-matrix-lib` as a library as described in [this document](https://www.arduino.cc/en/Guide/Libraries). 

This driver (now) uses SPI to transfer bits to the shift registers. The default wiring for connecting the RGB LED Matrix to an Arduino is:

| LED Matrix Connection | Arduino Pin | Notes |
|:-:|:-:|---|
| +5V | 5V | |
| GND | GND | |
| SER | 11 | SPI MOSI Pin |
| CLK | 13 | SPI SCK Pin |
| LATCH | 10 | SPI SS Pin. Technically, the SS pin is used to control whether an SPI slave is active or not. But, the board isn't strictly implemented and a SPI slave and the logic level sequence is the same as what we'd need for a latch, so using as that. |
| SER' | _unused_ | Used to chain multiple boards together. Would connect to the SER of the next board.|

Note that the SPI MISO pin is unused.