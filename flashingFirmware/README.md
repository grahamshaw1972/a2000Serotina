# Flashing Firmware How To Guide

This page details the process that you need to follow to flash firmware onto the A2000 Serotina keyboard. 

### Firmware location

The firmware can be downloaded from the Github page 

https://github.com/grahamshaw1972/a2000Serotina/tree/main/qmk_firmware



### Choosing the correct file

There are currently three firmware files to choose from

| File Name                                                    | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| https://github.com/grahamshaw1972/a2000Serotina/blob/main/qmk_firmware/a2000Serotina_pc_testing_uk.hex | a2000Serotina_pc_testing_uk.hex: Use this firmware for testing if you want to test the keyboard connected to a PC via USB. This firmware is no good for an Amiga. |
| https://github.com/grahamshaw1972/a2000Serotina/blob/main/qmk_firmware/a2000Serotina_us_uk.hex | a2000Serotina_us_uk.hex: Use this firmware for both the US and UK keyboard layouts |
| https://github.com/grahamshaw1972/a2000Serotina/blob/main/qmk_firmware/a2000Serotina_international.hex | a2000Serotina_international.hex: Use this firmware for all other keyboard layouts |

### Install Teensy Loader

You need to use a program called Teensy Loader in order to transfer the firmware .hex file onto the Teensy 2++ MCU. The Microcontroller is made by a company called PJRC. They also provide the Teensy Loader application. There are versions of Teensy Loader for Mac, Linux and Windows. You can find instructions for installing Teensy Loader 

[Install Teensy Loader PJRC]: https://www.pjrc.com/teensy/loader.html	"Install Teensy Loader PJRC"



### Use Teensy Loader to install the firmware

The PJRC website also contains instructions on how to use Teensy Loader to load .hex files onto the Teensy 2++. It's a simple procedure so I won't duplicate the instructions here. 



#### Windows: 

https://www.pjrc.com/teensy/loader_win10.html

### Linux:

https://www.pjrc.com/teensy/loader_linux.html

### Mac:

https://www.pjrc.com/teensy/loader_mac.html



**NB** - you will need a Mini USB cable. 



#### Warning: Never plug the keyboard into a PC ( via mini USB ) and an Amiga ( via 5 Pin Din ) at the same time. This would connect the 5V rails of the PC to the Amiga. That would not be good. 
