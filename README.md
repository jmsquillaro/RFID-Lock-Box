https://user-images.githubusercontent.com/34187061/170554745-96279dba-d920-4b44-b4a3-46d40cd4bfe2.mp4

# RFID Lock Box
 A Feather-connected lock box that uses RFID technology and real-time internet connectivity to verify access.

### Inspiration

Every day at Penn we use our PennCard to provide access to locations on campus, whether that be classroom buildings or even our own dorm rooms. Using this as inspiration, our group wanted to leverage this technology to make a project that secures our belongings and out of this, the RFID Lock Box was created!

![The RFID Lock Box](https://user-images.githubusercontent.com/34187061/170554861-13ebddab-50ed-4fec-a662-8f813a866d41.jpg)
|:--:|
| <b>The RFID Lock Box</b>|


### What it does

The RFID Lock Box uses an RFID sensor to detect authorized RFID cards, providing a user access to the contents within the secured box. When an authorized card is tapped, the lock will open. Tap it again, and the lock will close. It is that simple! If you wanted to add or remove a card ID, that can be done, too, all on one's computer as the RFID Lock Box is real-time internet connected. Keeping your belongings safe has never been more high tech!

### How we built it

We built this project using a Feather HUZZAH32 board, an RC522 RFID sensor, a buzzer, and a servo motor. We also used a laser-cut acrylic box for the actual structure and used necessary auxiliary components such as a breadboard and jumper cables.

![View of Wiring](https://user-images.githubusercontent.com/34187061/170554980-c586c17e-7e5c-4e17-b043-33c41dcbb0bd.jpg)
|:--:|
| <b>View of Wiring</b>|


### Challenges we ran into

One challenge we ran into was converting some schematics for this project from an Arduino Uno to a Feather HUZZAH32. Because the pinout configuration is different, I had to manually map out each corresponding pin. While tedious, I did end up getting it to work. Another challenge existed on the code side and the relative limitations of the C-derived Arduino language. Given this project received new information over WIFI, it was important to append new RFID card UIDs to the total list of approved identifiers. However, because the language does not permit such appending, I could not create a mutable array thus limiting the collection to two approved UIDs at a time. In time, we hope to fix this issue with a workaround.

![Original Arduino Wiring Schematics](https://user-images.githubusercontent.com/34187061/170555034-69608c00-e1ad-4974-b7d8-1e296707358a.jpg)
|:--:|
| <b>Original Arduino Wiring Schematics</b>|


![New Wiring Schematics](https://user-images.githubusercontent.com/34187061/170555050-654ba31c-dcd3-479d-b1f9-13fec413a48f.jpg)
|:--:|
| <b>New Wiring Schematics</b>|


### Accomplishments that we're proud of

We are extremely proud that we were able to get the device to successfully interface with the internet and receive new data from Adafruit IO. Working with pushing data is always tricky and to get this to work flawlessly was a big accomplishment. Also, just being able to translate Arduino Uno schematics to the Feather HUZZAH32 was an accomplishment, as we learned a great deal of what each pin does and its significance.

### What we learned

We learned that interfacing with hardware does not always happen so easily. Between board differences, part malfunctions and complicated schematics, interfacing with hardware takes patience. However, when time is invested in the project, some impressive things can be made, like the RFID Lock Box!

### What's next for RFID Lock Box

The RFID Lock Box has great potential to further the proof-of-concept it is designed to be: to demonstrate key card access around the University's campus. Future improvements can be on the box design where the interior is bigger and the door is fully controlled by a servo, making it so that the locking action also closes the door. On the code side, as mentioned in the "Challenges" section, I'd hope to improve the code so that the array of approved UIDs can be appended (or a workaround devised to get this desired outcome) with new approved UIDs from the internet.

### Built With

adafruitio, arduino, feather, rfid

### Link to DEVPOST
https://devpost.com/software/rfid-lock-box
