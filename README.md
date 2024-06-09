# 9 DoF Head Tracker

Arduino project that uses the reading from the IMU and sends it to [OpenTrack](https://github.com/opentrack/opentrack) for head tracking.
Project is able to read yaw, roll and pitch.


## 🛠 Assembly
Parts needed:

✔ Arduino board (I used micro pro)

✔ GY-85

Connect pins:
| Arduino  | GY-85 |
| ------------- | ------------- |
| 5V (VCC on mirco pro)  | VCC_IN  |
| GND  | GND  |
|SCL (pin 3 on micro pro)|SCL|
|SDA (pin 2 on micro pro)|SDA|


## 🤔 How to program Arduino?

There are 2 ways to program Arduino with provided code.

#### Using PlatformIO addon for Visual Studio Code:

Import project into [PlatformIO](https://platformio.org/), set up arduino board and communication port and finally upload.

#### Using ArduinoIDE:

Copy and paste contents of [main code](https://github.com/jelo-git/9DoFHeadTracker/blob/main/src/main.cpp), import library from
[lib/GY-85](https://github.com/jelo-git/9DoFHeadTracker/tree/main/lib/GY-85), set up arduino board and communication port and finally upload.

## 🗨 How to recieve serial readings from arduino on PC?

I've provided [python code](https://github.com/jelo-git/9DoFHeadTracker/blob/main/software/source.py) that recieves sensor readings from Arduino throught serial communication protocol and sends them to OpenTrack using "UDP over network" method.

To run code type into terminal: `python source.py`

To exit from script press `Ctrl+C`

  
