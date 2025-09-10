
| Nibble     | 4 bits                                                                                                                                 |
| ---------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| Byte       | 8 bits                                                                                                                                 |
| RIMS       | Riverside-Irvine Microcontroller Simulator. 1 byte input, 1 byte output. Software we use to simulate embedded system input and output. |
| Hex Syntax | `char c = xAF;`<br>`char c = 0xAF;`  are correct                                                                                       |
| `inline`   |                                                                                                                                        |

# Bit Access Functions
```c
inline unsigned char SetBit(unsigned char x,unsigned char k, unsigned char b) {
   return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
}

inline unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}
```

# Finding the Sampling Period
Suppose we want a button to be pressed for at least 500ms before it is registered. Then the sampling rate (ticking period) needs to be less than 500ms to guarantee no button press (i.e. change in signal) can be missed.
Now suppose we press a button for 500ms, let go for 300ms, then press it again for another 500ms. In order to detect the second button press, we need to set the sampling rate to be less than 300ms. This is called determining the __minimum interevent separation time__ of the system.
In practice, a system's clock (with a 500ms period, for example) does not perfectly tick at each 500ms. One tick could be at 499ms, the next at 1001ms, and so on. To be safe, it is good practice to set the period to be 10% (or higher) less. So, maybe 450ms instead of 500.

## Utilization
A system's **utilization** is the percentage of the time it is executing tasks. More utilization, more power consumption.
Faster sampling period, more utilization. 

## Latency
Also known as **lag**, it is the time between input and output of a system. More tasks, more latency. Bigger period, more lag. And vice versa is true.

As a system designer, we need to make a trade off and find the sweet spot between latency and utilization.

## Button bouncing
Buttons are mechanical switches that may bounce back and forth and send a signal multiple times. Therefore, the system period needs to be greater than the button bouncing duration so the system does not incorrectly read a single button press as multiple.

## Input conditioning
It is the process of refining input values from a sensor, button, etc..
Electromagnetic interference from other electric devices may cause spikes in the signal. These are called **glitches** so we need to avoid those as well. We can't completely avoid them because glitches can occur at any time due to outside factors. However, we can minimize their detection by requiring multiple consecutive samples, and setting the sampling period to be higher than the max glitch duration. This is called **filtering.**
We can also insulate sensors and add capacitors to the system to counter outside EMI.

## Output conditioning
While we're reading bits of input A, we don't out our output B to fluctuate. So, we update the value of B after we're done reading A.

```c
#include "RIMS.h"

unsigned char 
GetBit(unsigned char x, int k) {
   return ((x & (0x01 << k)) != 0);
}

void main() {
   unsigned char cnt; //avoid glitches on B
   unsigned char i;
   B = 0; // initialize output
   while (1) {
      cnt=0;
      // Reading bits of binary input
      for (i=0; i<8; i++) {
	     // Returns value of 
         if (GetBit(A, i)) {
            cnt++;
            // B++; Do not directly update B
         }                
      }
      // Set value of output only after done reading input
      B = cnt; 
   } 
}
```

# Buffer IC and Load Resistor

<iframe width="560" height="315" src="https://www.youtube.com/embed/Z1_Ag3dxH34?si=Ad-z1P_1ei_E9WxK" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
I didn't understand. Must study circuits before jumping here. ZyBooks is shit.
	Careful attention to I/O electrical characteristics specified in a microcontroller's datasheet and basic electronics knowledge are necessary to properly connect microcontrollers with other physical components.



### Time-multiplexed output with registers


## Peripheral devices
These are external input and output devices for capturing and displaying data. Examples are:
- Keyboard
- Sensor
- Button
- LED light
Peripherals can connect to an embedded system via several different hardware interfaces, including:
- GPIO (General-Purpose Input/Output)
- I2C
- SPI
- UART
- USB.


