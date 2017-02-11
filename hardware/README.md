# RGB LED Matrix Hardware
The design approach to  these RGB LED matrices is intended to be simple, leveraging low cost components like the 74HC595 shift register. 
## Design Approach
The general hardware design of the matrix is to use shift registers to drive the matrix. Here, we use 4 pin RGB LEDs with a common anode. The RGB LED anodes are connected into rows, and the cathodes are connected into columns aligned with the colors of each LED. To light any particular LED color, its row should be powered and the column sinked. If common cathode LEDs were used instead, this would be swapped with the rows becoming sinks and the columns being power source. The shift registers are connected in serial such that the most significant bit (MSB) being the first LED column and the least significant bit (LSB) being the first row.


Consider the following 4x4 RGB matrix:
```
                 Serial Bit Stream
    					  |
 RGB--RGB--RGB--RGB- R1  LSB
 |||  |||  |||  |||       | 
 RGB--RGB--RGB--RGB- R2   |
 |||  |||  |||  |||       |
 RGB--RGB--RGB--RGB- R3   |
 |||  |||  |||  |||       |
 RGB--RGB--RGB--RGB- R4   |
 |||  |||  |||  |||       |
 CCC  CCC  CCC  CCC       |
 000  000  000  111       |
 123  456  789  012       |
 						  |
 MSB <--------------------+
```

Since there are 16 bits needed to control the rows and columns, two 74HC595 shift registers will be used. The first one, U1, will contain the MSB, which will be the first bit shifted out. Give that, U1 should be a downstream slave to U2 and the MSB ultimately will reside in the Q7 pin of U1. U1's SER pin will need to be connected to the SER' (aka Q7') pin on U2. The input serial stream flows into U2, so the LSB will be on Q0 of U2.

In this case, Q7 of the first 74HC595 (U1) would be attached to C01, Q6 to C02, and so on. Since there are 12 column and 4 rows, two 8-bit shift registers are needed. So the second 74HC595 (U2) would have its Q0 through Q3 attached to R1 through R4, and its Q4 through Q7 attached to C12 down through C09. In this configuration, the first bit shifted out in an update cycle is for C01, and the last bit shifted out is for R1.

In this common anode set up, the rows would be "on" when the proper 74HC595 pin is in the `high` state and the column would "on" when its respective pin is in the `low` state. Basically, the shift register is sinking the columns and powering the rows. This would be inversed if you are using a common cathode RGB LED. 

There are two challenges with this design:

1. You cannot light only (R1,C01) and (R2, C02) simultaneously as (R1,C02) and (R2, C01) will also be lit.
2. Individual pins of the 74HC595 have a max current draw of 70 mA, but it's best to keep less than 20 mA. For LEDs that have a 20 mA draw, this means that the 74HC595 can't directly power an entire row of LEDs.

### Multiplexing

To solve the first problem, we will multiplex the LED display. What this means in practice is that we light only one row at a time, but cycle through each row fast enough that the human eye cannot see the blinking. 

### Switching Transistor
If every LED in a row were lit, we'd exceed the  74 HC595 max current. However, we want to be able to light every LED in a row. So instead of powering the row directly, the 74HC595 will instead drive a transistor for each row, and the transistor will switch on or off the current powering the row. Since the design is using a common anode LEDs, the switching transistor will be PNP. If we were using a common cathode LED, the switching transistor would be NPN. 

There is one small issue with using the switching transistor: the transistor does not turn off instantly. As we scan through the rows, the prior row's switching transistor will still provide a small amount of current to its row for a short period of time. This will cause a slight, but detectable glow in the LEDs of the prior row that are in the same columns as the LEDs int eh current row that are turned on. The best way to deal with this is to wait a very small amount of time (~5 micro seconds) after turning off a row before turning on the next row. Note that with using a PNP transistor to drive a row, the shift register's setting to turn it on now becomes `low` as a PNP transistor needs a negative voltage between the emitter and base to be turned on, which will allows positive current to flow into the row. 