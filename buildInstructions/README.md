# A2000 Serotina Build Instructions

These instructions detail the build process step by step. Please note, there is an interative BOM html file located in bom/a2000Serotina.html. You can download this file and open it in your file browser. This will tell you the locations of each of the components. However, it's pretty easy to work out where everything needs to go to be honest. The only slight gotcha is that J1 ( right angled pin header ) needs to be soldered to the under / back side of the PCB - see step 3. 

### 1. Drill The Keyboard Case

You will need to enlarge the hole in the keyboard case slightly, so that you can feed the 5 Pin Din connector into the hole. Using a 5 mm Wood Drill bit, drill down, using the cable gutter as a guide. 

![](drilling.JPG)

When you are done, the hole should look like this: 

![enlargedHole.JPG](enlargedHole.JPG)

Cut the 5 Pin Din cable to the size that you want. You can now feed in the cable. There should still be some resistance. This is good, because it will provide some strain relief. 

![cableInserted.JPG](cableInserted.JPG)

You want approx. 20cm of cable to go inside the case.

![cableInCase.JPG](cableInCase.JPG)

### 2. Remove the Outer Insulation 

Cut off approx 25mm of insulation off the end of the cable using a craft knife. Careful not to cut too deep. If you do cut too deep, then you will cut through the shielding, which is used to carry one of the signals. 

![endCut.JPG](endCut.JPG)

Gather the copper insulation and twist into a wire. Remove the foil insulation. 

![twisted.JPG](twisted.JPG)

Put heat shrink over the new wire and use a lighter or hot air to shrink. Also strip the top 3mm off all the other wires. 

![shrunk.JPG](shrunk.JPG)

**NB** - I had to use black heat shrink. It's the only one I have that is the correct size. That's not ideal, because there is already a black wire. I can still tell them apart because the heat shrink is thicker. However, if possible, choose a heat shrink colour which is different from the four other wires. I chose yellow in Din plug pin out diagram in step 16. 

### 3. Crimp Dupont connectors

Use a Dupont Crimping tool to put female connectors onto each wire. 

![crimped.JPG](crimped.JPG)

### 4. Insert the wires into a DuPont Plug

Insert the wires into a Six hole DuPont Plug, leaving the third hole empty. 

| DuPont Plug | 5 Pin Din | Signal   | Colour / Description* |
| ----------- | --------- | -------- | --------------------- |
| 1           | 5         | Ground   | Green                 |
| 2           | 4         | VCC      | White                 |
| 3           |           |          | Leave Empty           |
| 4           | 1         | Not Used | Red                   |
| 5           | 3         | KCLK     | Black                 |
| 6           | 2         | KDAT     | Shielding             |

NB - I chose to use this configuration for the DuPont Plug, because it matches the DuPont plug on the original A2000 Cherry keyboard. 

\* It's possible that you are using a different 5 Pin Din cable, in which case the colours will be different. 

**Additionally, I have also found the colours differ on two different cables from the same manufacturer. The second configuration was a mirror image of the second. This means that white and green need to be swapped and red and black also need to be swapped. **

Also note, that the numbering on the 5 pin Din is probably not what you would expect. It's numbered as follows: 

![fivePinDinCorrectColours.JPG](fivePinDinCorrectColours.JPG)

![dupontPlug.JPG](dupontPlug.JPG)

**You can make another cable with the other end of the 5 pin Din cable. This is handy for testing without putting the PCB into the case. **



### 5. Solder the diodes

Solder Diodes D1 -> D105 to the PCB. Ensure that the polarity of the Diodes is correct. The black ring on the diode should match up to the white marking on the PCB silk screen. 

![v1_5_withDiodes.JPG](v1_5_withDiodes.JPG)



### 6. Solder the Resistors

Solder the resistors R1, R2, R3, R4, R5, R6, R9, R10 and R11. 

![v1_5_withResistors.JPG](v1_5_withResistors.JPG)



### 7. Solder the Right Angled Pin Header

Solder the Right Angled Pin Header ( J1) to the **under side** of the PCB. Snip the third pin from the right.

![v1_5_rightAngledPinHeader.JPG](v1_5_rightAngledPinHeader.JPG)

### 8. Solder the Pin Headers onto the Teensy++ 2.0

Snip the 40 pin pin header in half, giving 2 x 20 pin headers

![v1_4_snipping.JPG](v1_4_snipping.JPG)

![](v1_4_snipped.JPG)

Solder the Pin headers onto the Teensy++ 2.0 Arduino MCU. Using the PCB holes as a guide makes this process easier. Solder the pin in each corner first, followed by all of the others. 

**NB** - solder so that the plastic collars are at the top and therefore so that the Teensy MCU is resting on top of the plastic collars. The small metal posts above the collars should be poking through by approx 1.25 mm. 

![v1_1_teensyPins.JPG](v1_1_teensyPins.JPG)



### 9. Flash the firmware onto the Teensy++ 2.0

See here for instructions:

https://github.com/grahamshaw1972/a2000Serotina/tree/main/flashingFirmware

### 10. Solder the Teensy++ 2.0 onto the PCB

Solder the Teensy++ 2.0 onto the PCB.

![v1_5_teensyFitted.JPG](v1_5_teensyFitted.JPG)



### 11. Solder the Caps Lock LED to the PCB

Solder the Caps Lock LED ( LED6 ) to the PCB. **LEDs 1 -> 3 ( labelled STA1 -> 3 also ) are only required for debugging. Do not populate  these unless you are planning to debug the keyboard. **

Remember, that the long leg on the LED is the positive one. There are two holes on the footprint for each LED. One hole is round and the other is square. The round hole is the positive hole, so you need to insert the longer of the two legs into the round hole. 



![v1_5_ledsFitted.JPG](v1_5_ledsFitted.JPG)



### 12. Test with tweezers ( Optional )

From an electrical standpoint, your keyboard should be functional. So you can test. You have no switches of course, but you can insert a pair of metal tweezers into the switch holes. See **21** + **22** below. Check for shorts first and then plug into an Amiga and run Amiga Test Kit. If you made an extra cable earlier, then you can use this for testing.

### 13. Cut off PCB Switch Mounting Lugs ( if necessary )

If you have got PCB mount switches, they have plastic mounting lugs on either side of the large central plastic post. 

![cutLugsBefore.JPG](cutLugsBefore.JPG)

This keyboard is a plate mount project, so the switches are clipped into the metal plate. The PCB mounting lugs are not required. What's more, there are no holes in the PCB for these to go into. So if you have PCB mount switches, you will need to clip of the mounting lugs with a side cutter. If you have plate mount switches, then this step is not required. 

![cutLugs.JPG](cutLugs.JPG)

When you have removed both PCB mounting lugs, the switch will look like this: 

![cutLugsAfter.JPG](cutLugsAfter.JPG)

NB - you will need to cut the mounting lugs off every switch. 

### 14. Line up Plate with PCB

Line up the PCB with the mounting plate and place switches in each of the corners. 

![v1_5_lineUp.JPG](v1_5_lineUp.JPG)



### 15. Solder the first switches

Solder the switches inserted above. These will keep the PCB and the plate lined up whilst soldering the rest of the switches. 

![v1_5_firstSwitchesSoldered.JPG](v1_5_firstSwitchesSoldered.JPG)



### 16. Place the Cherry MX Switches

Push the MX switches into the holes in the mounting plate. Check that  both contacts of the switch are poking through the holes in the PCB. If they are not, then the switch will not work. You can fix by removing the switch, unbending the contacts and inserting again. 

### 17. Solder the Cherry MX Switches

Solder the Cherry MX Switches onto the PCB working in from the corners. Note that the footprints on the PCB are for both MX and Alps switches. This means that there are two holes for the right switch contact. You don't need to solder both holes, just the hole with the contact in it. However, you can solder both holes if you would prefer. Either is fine. 

![v1_5_switchesSoldered.JPG](v1_5_switchesSoldered.JPG)

### 18. Solder the in-swtich LEDs

Some keys have an LED mounted inside them. For example, Caps Lock. Put the LED in from the top of the switch and through the holes in the PCB. Once again, the longer leg must go through the round hole. 

Use White Tack / Blu Tack to hold the LED in place whilst you solder it from the other side. 

![v1_1_whiteTack.JPG](v1_1_whiteTack.JPG)

Switches which require LEDs are:

- Caps Lock
- Left Control
- Left Amiga
- Right Amiga
- Right Control

NB - Left Control, Right Control, Left Amiga and Right Amiga light up when pressed because these are the reset keys. If you don't want these keys to light up, then don't put an LED into these keys. You will certainly want an LED in the Caps Lock Key though. 

![v1_4_withInSwitchLEDs.JPG](v1_4_withInSwitchLEDs.JPG)



### 19. Connect the PCB to the DuPont Plug

Turn the keyboard PCB upside down and connect your DuPont Plug to the PCB.

![V1_4_connected.JPG](V1_4_connected.JPG)



### 20. Screw into bottom case

Drop the mounting plate / PCB into the bottom of the case. It should drop straight in and there should not be much room for misalignment. Screw the ( only ) large black metal screw supplied in the WASD keyboard kit into the case, through the hole in the mounting plate. 

![v1_5_screwed.JPG](v1_5_screwed.JPG)

The keyboard should look like this by now. 

![V1_5_inBottomCase.JPG](V1_5_inBottomCase.JPG)

### 21. Check for shorts

Now that the keyboard is connected to the cable, you need to check for shorts. If the 5V signal is shorted to GND for example, that would be very bad news for your Amiga. The best way to check for shorts is to use a multi-meter in continuity mode. Put one probe on a pin of the 5 Pin Din Plug and the put the other probe onto each of the other pins one at a time. Work through each of the pins doing the same thing. You are expecting that none of the pins are connected. If you hear any beeps, then you have a short. You need to fix the short before connecting the keyboard to your Amiga. 

### 22. Connect to an Amiga and Test

It's now ready to connect to an Amiga and test it. I would recommend using Amiga Test Kit:

https://github.com/keirf/Amiga-Stuff/releases

Download and transfer the most recent version onto your Amiga. Press F2 to get to the Keyboard Test. Test each key by pressing it. You should be aiming for the following test result for the us_uk layout:

![amigaTestKit.jpg](amigaTestKit.jpg)

**NB** - for the International Layout, you would expect to see all keys as green, including the key to the right of left shift and also the key cut out from the Return key. 

If you see any keys that aren't working, check

* Diode for that key is in the correct orientation
* Both switch contacts are poking through the holes
* Both switch contacts are soldered

### 23. Remove unwanted LED light guides

The case has light guides for three LEDs. The Amiga doesn't have a Num Lock or a Scroll lock LEDs, so these LEDs are also not required. What's more, due to the positioning of the Teensy 2.0++ MCU, these light guides will prevent the case from being closed. It's necessary to remove the light guides from the case. Use your side cutters to cut the light guides into quarters and then eighths. Then use a pair of pliers to gently waggle the plastic until it comes off. The plastic is quite soft and will come away easily after a few waggles, without the need for force or pulling. 

![v1_4_removeLightGuides.JPG](v1_4_removeLightGuides.JPG)

![v1_4_lightGuidesGone.JPG](v1_4_lightGuidesGone.JPG)

Make sure you remove the correct two. You need to leave the one on the left as the case is upside down for guiding the Caps Lock LED. Look at where the LED is on the PCB if you are unsure. 

### 24. Attach the Stabilizers

Attach the stabilizer clips and then bars to the plate:

![v1_5_withStabilizers.JPG](v1_5_withStabilizers.JPG)

### 25. Fit Keycaps for Stabilized keys

There is a knack to fitting Costar stabilizers. Fit both the inserts into the key first. The longer part of the insert should be pointing towards the top of the keyboard for horizontal switches and the left of the keyboard for vertical switches. 

![v1_4_inserts.JPG](v1_4_inserts.JPG)

You can test by putting the keycap onto the switch and pushing down. If the keycap fits onto the switch stem and moves down okay, then you have the inserts fitted correctly. In order to fit onto the Stabilizer wire, put one side on as you move the keycap down and then push slightly to get the wire on the other side to clip into the insert. You can see a YouTube video about how to fit Costar stabilizers here: 

https://www.youtube.com/watch?v=oWgrnQGBBn4&amp;ab_channel=iluvbeanz

![v1_5_withStabilizedKeys.JPG](v1_5_withStabilizedKeys.JPG)

### 26. Put on the Top Case

First rest the top case onto the bottom case. There are three plastic posts that go into holes in the Mounting plate. Press the posts down first. Next, close all the clips, working from the top, down the sides and lastly the bottom, i.e. where the Space row is located. You should not need to press too hard. The plastic clips are quite fragile. If you press too hard, you might break them. 

![v1_5_withTopCaseOn.JPG](v1_5_withTopCaseOn.JPG)

### 27. Put the feet on the bottom

Stick the six rubber feet onto the bottom of the case

![v1_5_withFeet.JPG](v1_5_withFeet.JPG)

### 28. Screw the case closed

Insert the three silver metal screws from the WASD keyboard kit into the three holes as shown and screw them tight. 

![v1_5_withScrewsInBottomCase.JPG](v1_5_withScrewsInBottomCase.JPG)

### 29. Fit Feet to bottom of case

Fit the feet from the WASD keyboard kit to the bottom of the case. They just clip in, with a bit of encouragement. 

![v1_5_withFeet2.JPG](v1_5_withFeet2.JPG)

### 30. Put on the rest of the Keycaps

You are all done now, just need to put the rest of the keycaps on. 

![v1_5_complete.JPG](v1_5_complete.JPG)

### 31. Final Test

And last thing is a final test. 

![v1_5_finalTest.JPG](v1_5_finalTest.JPG)

### 32. Enjoy :-)
