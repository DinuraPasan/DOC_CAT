# DOC_CAT API

## Description
This repository contains many optimized arduino library. Scroll down for more details.
  * HC74595 Arduino Library
  * DS3231 Arduino Library
  * DotMatrix Arduino Library
  * LP503X Arduino Library

The goal is to improve the efficiency of more accurate end user applications while saving the time and money spent on developing embedded systems.

### HC74595 Arduino Library
* Controlling 74HC595 IC using Arduino
  * The purpose of this library is to facilitate the control of 74HC595 from the Arduino programming environment. This library gives the user the ability to directly control the 8 output terminals in the 74HC595 IC separately and directly. Only one byte is used to store the output data in one IC. Therefore, the library allows the microcontroller to control a large output number using a very small amount of RAM. Check the example_Folder for more information on the library.

### DS3231 Arduino Library

* Controlling DS3231 RTC IC using Arduino
  *  The purpose of this library is to facilitate communication from the Arduino programming environment with the DS3231, the most common RTC IC. Using the DS3231 internal register memory, this library enables the user to activate all DS3231 features and perform date and time calculations. Check the example_folder for more information about the library.

### DotMatrix Arduino Library

* Controlling the LED Dot Matrix from within the Arduino environment.
  *  Dot Metrix performs the back data processing process required for LED Display, that is, the data (image) required to be displayed in the Display is set up and stored in the memory(RAM). The data is loaded to the LED of the Display collection according to the function(fx) given by the user. Therefore, it can be easily connected with a wider range of LED Drivers(like as 74HC595).

### LP503X Arduino Library
* Controlling LP5030/LP5036 Constant Current RGB LED Driver ICs with Arduino
  *  The LP503X Arduino Library, offers seamless integration and control for the LP5030 and LP5036 constant current RGB LED driver ICs within the Arduino environment. This library provides comprehensive functionality to manipulate color-mixing levels, adjust intensity, manage LED banks, and control various configurations of individual LED outputs. Through simple yet powerful functions, developers can easily customize LED behavior, implement light dimming curves, enable power-saving modes, and more, offering a versatile and efficient solution for controlling RGB LED modules.

## Getting Started

Examples are provided for all the functions in the library. Check the example folder for more details.

### Dependencies

* Supports Arduino IDE 1.5.0 or latest Arduino IDE versions.

## Help

Feel free to report any issues you may have regarding the library.

## Authors

Dinura Pasan

* Contact with me

  * [LinkedIn](https://www.linkedin.com/in/dinurapasan/)
  * [Skype](https://join.skype.com/invite/uLRTig6P7dg0)
  * [Instagram](https://instagram.com/pasandinura?igshid=OGQ5ZDc2ODK2ZA==)

## Version History

* 1.0.0
    * Initial Release
* 1.1.0
    * Adding the new Dot Matrix library.
* 1.2.0
    * Adding the new LP503X library.

## License

This library is open source!

This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/DinuraPasan/DOC_CAT/blob/main/LICENSE.md) file for details

Use, reuse, and modify these files as you see fit. no warranty is given.
