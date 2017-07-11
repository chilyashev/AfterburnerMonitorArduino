# AfterburnerMonitorArduino

This is to accompany the [AfterburnerMonitor](https://github.com/chilyashev/AfterburnerMonitor) project.

## Prerequisites
* Arduino Nano (or any other, but connections might differ)
* SPI OLED display
* [u8g2](https://github.com/olikraus/u8g2) library to drive the display
* Some wires to connect the parts


## Hardware connections

The used OLED display is connected as follows: 

* Arduino -> Display
* 3V3 -> VCC
* GND -> GND 
* D13 -> D0
* D11 -> D1
* D10 -> CS
* D9  -> DC
* D8  -> RST

## Building

I used the [Visual Micro](http://www.visualmicro.com/) plugin for Visual Studio. If you have it, download this repository and just open the sln file in Visual Studio.

If you want to use the Arduino IDE, download the OLED1.ino and main.h files and open them in Arduino IDE. 