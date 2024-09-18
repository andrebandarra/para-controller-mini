To customize the name of your Arduino-based joystick so that it's recognized with a custom name by Unity (or any operating system), you need to modify the USB descriptors on the Arduino. Since you are using an Arduino Micro, which is based on the ATmega32U4, it has native USB capabilities, and you can adjust the name via its firmware.

* In the Arduino IDE, go to the installation folder and find the boards.txt file:
C:\Program Files (x86)\Arduino\hardware\arduino\avr

* Open your text editor in Admin mode.

* Change the usb_product line to the name you want your device to show up as. It will look something like this:
micro.build.usb_product="ParaController Mini"

* Reflash the Arduino

Keep in mind that if the Arduino IDE or core libraries are updated, your changes might get overwritten, so you may want to back up these changes or use a custom boards file.
