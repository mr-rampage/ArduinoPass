# ArduinoPass

A hardware based password manager.

- The hardware is an AdaFruit 32u4 Feather Data Logger with the OLED Feather Wing. This device will be responsible for pushing passwords to the computer.
- The software portion is an F# console application used to unlock the device and add passwords to it.

Requirements:

- Contents on the Arduino must be encrypted
- Users must authenticate with the Arduino in order to use the device
- Users can add authentication details or encrypted notes via the console application
