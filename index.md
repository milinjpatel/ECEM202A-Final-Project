## Time Synchronization over Bluetooth Low Energy - ECE M202A Final Project

### Project Goals

Bluetooth Low Energy (BLE) is a popular wireless technology used in many consumer devices. It provides a low bandwidth, low power solution that allows devices to communicate with each other wirelessly and cheaply. Due to this, it has gained massive popularity among enthusiasts, as well as consumers. Time synchronization is the notion of different nodes in a system being aligned to the same reference of time. This allows for systems to provide timestamps for events that they see and correlating those timestamps across different nodes in an accurate way. Wirelessly time synchronizing nodes currently requires special hardware like 2.4GHz radios. From a consumer and enthusiast point of view, these technologies for time synchronization are not feasable. In order to provide a method for synchronizing time over BLE, we analyze software solutions. This solution would allow many BLE nodes to be time synchronized to any common central device, such as a smartphone.

### Approach

Nordic microcontrollers use a wireless stack called SoftDevice. SoftDevice is provided as a precompiled binary that is flashed onto the microcontroller's memory and provides an API for interacting with wireless radios like BLE. One of the APIs offered is called the Radio Timeslot API (timeslot API). The timeslot API provides uninterrupted access to the radio hardware for anywhere between 100us to 128 seconds. By using the timeslot API, we can precisely know the time at which a packet was transmitted by the BLE radio.

Nordic microcontrollers also provide another useful feature called Programmable Peripheral Interconnect (PPI). PPI allows peripherals to autonomously interact with each other to complete certain tasks. By using PPI, the radio peripherals could interact with other peripherals, such as the timer peripheral. This allows for fast response to packet reception.

By using the timeslot API and PPI together, both master and slave devices would have precise timing information about when synchronization packets were transmitted and received.

### Implementation and Analysis

### Prior Works

### Conclusion and Future Work

### Contributions by Team Member

### Presentation Slides

### References

* https://devzone.nordicsemi.com/nordic/short-range-guides/b/bluetooth-low-energy/posts/wireless-timer-synchronization-among-nrf5-devices
* https://cps.iisc.ac.in/wp-content/uploads/2017/10/07378439.pdf
* https://dl.acm.org/doi/pdf/10.1145/3123878.3132007
