# Projectweek Arduino Water

## links

* Node red dashboard: https://ucll-team1.eu-gb.mybluemix.net/ui/#!/0
* explanation about the [phmeter:](phmeter.md)
* explanation and setting up the IoT platform: [IoT platform](iot%20platform%20manual.md)

## Arduino IDE Setup

1. Download Arduino IDE
2. Copy esp32 board manager link
(https://dl.espressif.com/dl/package_esp32_index.json) in File > Preferences >
Additional board manager links
3. Select "DOIT ESP32 DEVKIT V1" under Tools
4. Import these libraries under Tools > Manage libraries :
	* PubSubClient by Nick O'Leary
	* ArduinoJson by Benoit Blanchon
5. Clone this repo and open the
project (one of the .ino files) in the arduino IDE
6. Always make sure the correct serial port is selected under Tools and the
correct baud rate (115200) is selected in the Serial monitor (found under Tools)
7. Fill in the correct wifi credentials and server urls at the top of
WifiClientMQTT.ino
8. Compile & Upload, then watch output in the Serial Monitor
