# A2000 Serotina Build Instructions

These instructions detail the build process step by step. 

### 1. Solder the Diodes

Solder Diodes D1 -> D105 to the front side of the PCB. Ensure that the polarity of the Diodes is correct. The black ring on the diode should match up to the marking on the PCB silk screen. 

![v1_1_withDiodes.JPG](v1_1_withDiodes.JPG)



### 2. Solder the Resistors

Solder the resistors R1 -> R12 to the front side of the PCB. Resistors R4 -> R6, R9 and R10 are for debug status LEDs, so you only need to populate these if you are planning to debug the keyboard.![v1_1_withResistors.JPG](v1_1_withResistors.JPG)



### 3. Solder the Right Angled Pin Header

Solder the Right Angled Pin Header ( J1) to the back side of the PCB. Snip the third pin from the right.

![v1_1_rightAngledPinHeader.JPG](v1_1_rightAngledPinHeader.JPG)

### 4. Solder the Pin Headers onto the Teensy++ 2.0

Solder the Pin headers onto the Teensy++ 2.0 Arduino MCU. Using the PCB holes as a guide makes this process easier. Solder the pin in each corner first, followed by all of the others. 

![v1_1_teensyPins.JPG](v1_1_teensyPins.JPG)



### 5. Flash the firmware onto the Teensy++ 2.0

See here for instructions.

### 6. Solder the Teensy++ 2.0 onto the PCB

Solder the Teensy++ 2.0 onto back side of the PCB.

![v1_1_teensyFitted.JPG](v1_1_teensyFitted.JPG)



### 7. Solder the LEDs to the PCB

Solder the LEDs to the front side of the PCB. LED1 -> 3, and LED6 -> 8 are only required for debugging. So you only need to populate these LEDs if you are planning to debug the keyboard. Remember, that the long leg on the LED is the positive one. There are two holes on the footprint for each LED. One hole is round and the other is square. The round hole is the positive hole, so you need to insert the longer of the two legs into the round hole. 

![v1_1_ledsFitted.JPG](v1_1_ledsFitted.JPG)

### 8. Test Using tweezers

You should now have a keyboard that is functional. You can now test that all of the keys are working as they should using tweezers. Start a keyboard tester. For example: 

[Keyboard Tester]: https://www.keyboardtester.com/

Plug your keyboard into a PC using a mini USB cable connecting directly to the Teensy++ 2.0

![v1_1_miniUSB.JPG](v1_1_miniUSB.JPG)

![v1_1_tweezers.JPG](v1_1_tweezers.JPG)

### 9. Fix Stabilizers to PCB

Construct 6 x 2u stabilizers and 1 x 6.25u Stabilizers. Insert into the holes. The stabilizer end with the metal bar should go into the big hole. The screw should go into the small hole remember to put the washer between the screw and the back side of the PCB. This will help to minimize noise. 

![v1_1_stabilizersFront.JPG](v1_1_stabilizersFront.JPG)

![v1_1_stabilizersBack.JPG](v1_1_stabilizersBack.JPG)

### 10. Place the Cherry MX Switches

Push the Cherry MX Switches onto the PCB. The Mounting pins on the Switch should be enough to hold the switch into place. 

![](v1_1_withSwitches.JPG)

### 11. Solder the Cherry MX Switches

Solder the Cherry MX Switches onto the PCB. Note that the footprints on the PCB are for both MX and Alps switches. This means that there are two holes for the right switch contact. You don't need to solder both holes, just the hole with the contact in it. However, you can solder both holes if you would prefer. Either is fine. 

![](v1_1_switchesSoldered.JPG)

### 12. Solder the in-swtich LEDs

Some keys have an LED mounted inside them. For example, Caps Lock. Put the LED in from the top of the switch and through the holes in the PCB. Once again, the longer leg must go through the round hole. 

Use White Tack / Blu Tack to hold the LED in place whilst you solder it from the other side. 

![v1_1_whiteTack.JPG](v1_1_whiteTack.JPG)

Switches which require LEDs are:

- Caps Lock
- Left Control
- Left Amiga
- Right Amiga

NB - Left Control, Left Amiga and Right Amiga light up when pressed because these are the three reset keys. If you don't want these keys to light up, then don't put an LED into these keys. You will certainly want an LED in the Caps Lock Key though. 

![](v1_1_withInSwitchLEDs.JPG)

### 13. Drill The Keyboard Case

You will need to enlarge the hole in the keyboard case slightly, so that you can feed the 5 Pin Din connector into the hole. Using a 4.5mm Wood Drill bit, drill down, using the cable gutter as a guide. 

![](drilling.JPG)

When you are done, the hole should look like this: 

![enlargedHole.JPG](enlargedHole.JPG)

You can now feed in the cable. There should still be some resistance. This is good, because it will provide some strain relief. 

![cableInserted.JPG](cableInserted.JPG)

You want approx 20cm of cable to go inside the case.

![cableInCase.JPG](cableInCase.JPG)

### 14. Remove the Outer Insulation 

Cut off approx 25mm of insulation off the end of the cable using a craft knife. Careful not to cut too deep. If you do cut too deep, then you will cut through the shielding, which is used to carry one of the signals. 

![endCut.JPG](endCut.JPG)

Gather the copper insulation and twist into a wire. Remove the foil insulation. 

![twisted.JPG](twisted.JPG)

Put heat shrink over the newly wire and use a lighter or hot air to shrink. Also strip the top 3mm off all the other wires. 

![shrunk.JPG](shrunk.JPG)

NB - I had to use black heat shrink. It's the only one I have that is the correct size. That's not ideal, because there is already a black wire. I can still tell them apart because the heat shrink is thicker. However, if possible, choose a heat shrink colour which is different from the four other wires. 

### 15. Crimp Dupont connectors

Use a Dupont Crimping tool to put female connectors onto each wire. 

![crimped.JPG](crimped.JPG)

### 16. Insert the wires into a DuPont Plug

Insert the wires into a Six hole DuPont Plug, leaving the third hole empty. 

| DuPont Plug | 5 Pin Din | Signal   | Colour / Description |
| ----------- | --------- | -------- | -------------------- |
| 1           | 5         | Ground   | Green                |
| 2           | 4         | VCC      | White                |
| 3           |           |          | Leave Empty          |
| 4           | 1         | Not Used | Red                  |
| 5           | 3         | KCLK     | Black                |
| 6           | 2         | KDAT     | Insulation           |

NB - I chose to use this configuration for the DuPont Plug, because it matches the DuPont plug on the original A2000 Cherry keyboard. 

Also note, that the numbering on the 5 pin Din is probably not what you would expect. It's numbered as follows: 

![fivePinDinCorrectColours.JPG](fivePinDinCorrectColours.JPG)

![dupontPlug.JPG](dupontPlug.JPG)

### 17. Connect the PCB to the DuPont Plug

Turn the keyboard PCB upside down and connect your DuPont Plug to the PCB.

![connected.JPG](connected.JPG)

### 18. Connect to an Amiga and Test

The keyboard should look like this by now. 

![inBottomCase.JPG](inBottomCase.JPG)

It's now ready to connect to an Amiga and test it. I would recommend using Amiga Test Kit:

https://github.com/keirf/Amiga-Stuff/releases

Download and transfer the most recent version onto your Amiga. Press F2 to get to the Keyboard Test. Test each key by pressing it. You should be aiming for the following test result for the us_uk layout:

![amigaTestKit.jpg](amigaTestKit.jpg)

NB - for the International Layout, you would expect to see all keys as green, including the key to the right of left shift and also the key cut out from the Return key. 

### 19. Screw the Keyboard into the case

Screw the keyboard into the bottom case, using the four M3 * 6 self tapping screws. 

![screwed.JPG](screwed.JPG)

### 20. Put the Top case on

Put the top case on. Be careful to line up properly. Once everything is lined up, push the three plastic mounting posts into the large holes. They should click on. Then close the plastic clips around the top edge. Finally close the plastic clips around the bottom edge. 

![topCase.JPG](topCase.JPG)

### 21. Attach Keycaps

Attach the keycaps to the switches. 

![v1_2_withKeyCaps.JPG](v1_2_withKeyCaps.JPG)

Your keyboard is now complete. Time for one last test with Amiga Test Kit. 

![](v1_1_complete.JPG)



ENJOY. 

:-)
