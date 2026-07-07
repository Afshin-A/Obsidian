#### RAM Controller
Modern computers integrate **the RAM controller** block directly on the CPU for faster access. So memory access flows like this:
```
CPU → Integrated Memory Controller → RAM
```


The RAM controller is a block on the CPU. A block is another term for a functional module.
Chips (including the CPU) are consisted of many **functional modules** working together. These are tested pieces guaranteed to work. 
A functional module is a bundle of code written in hardware languages (Verilog) that do one specific job. This code then gets transformed to a blueprint for a layout of transistors and logical gates. Engineers put hundreds of these blueprints together to create a chip. It's then printed on semiconductor boards. 
Internally, the CPU may have multiple memory-controller blocks. But as far as the software layer is concerned, there is one memory controller. 

#### Memory bus
Think of the **memory bus** has a highway that transmits data from the CPU to the memory and back. 
The memory bus is the physical wires on the motherboard that transmit data (from the CPU to the RAM. We can think of the wires as lanes in a highway. The more lanes there are, the higher the *bandwidth*, as we can send more data simultaneously. 
The standard memory bus for desktops is 64 bits. GPU buses can go up to 384 bits. 
The *bus speed/frequency* is how many times per second the bus can send data (MHz). The total data sent is $\text{bandwidth} \times \text{frequency}$
There are 3 separate highways (subsystems). 
- Address bus—carries the memory address data needs to be sent to or read from
- Data bus—carries the actual data 
- Control bus—sends flag signals (like read or write)
##### Some questions answered:
Q: How can a 64-bit CPU handle a wider bus? 
A: A 64-bit CPU refers to the size of its registers, and the external bandwidth is how much data at once can be transferred at once across the motherboard. They're two separate concepts. 
Q: If the largest memory address a 64 bit CPU can process is 64 bits long, then what would be the point of having a greater bandwidth (number of lanes)?
A: Having a greater bandwidth just means we can transfer data faster, which increases the CPU's throughput (utilization). CPU's clock speed is in the gigahertz, while the bus's speed is in the megahertz. So the CPU can process and produce data much faster than it can be transferred. Therefore, more bandwidth = more utilization. 

#### Memory Channel
If the memory bus is the physical highway (the copper traces on the motherboard), a **memory channel** is an independent instance of that highway system, completely separate from any other.
In hardware terms, a memory channel is a dedicated pairing of **one specific Memory Controller block** on the CPU, **one independent 64-bit memory bus**, and the **specific RAM slots** wired to that bus.
servers commonly have 8 memory channels.
#### Architecture of Multi-Channel Memory
When engineers want to increase memory bandwidth, they hit a physical limit with a single bus. Widening a single bus from 64 lanes to 128 lanes on a motherboard creates massive electrical interference (crosstalk) and requires too many pins on the CPU socket.
To solve this, chip designers use modularity. Instead of making one highway wider, they stamp out a second, identical copy of the entire functional module on the silicon.
- **Single-Channel System:** The CPU activates only one Memory Controller block. It handles a single 64-bit highway. If you have two sticks of RAM plugged into this single channel, they must take turns sharing those 64 lanes.
- **Dual-Channel System:** The CPU activates two separate Memory Controller blocks simultaneously. Controller Block A gets its own dedicated 64-bit highway to RAM Slot A. Controller Block B gets its own completely separate 64-bit highway to RAM Slot B.

#### Relationship to the Memory Bus
The relationship between a channel and a bus comes down to **concurrency and independence**:
- **They do not share wires:** Channel 1's data, address, and control buses are physically isolated on the motherboard from Channel 2's data, address, and control buses.
- **True Parallelism:** Because the underlying functional blocks on the CPU are independent, the CPU can execute a "Read" command on Channel 1's control bus at the exact same clock cycle that it executes a "Write" command on Channel 2's control bus.