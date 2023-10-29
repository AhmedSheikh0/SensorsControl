# SensorsControl

This system is used to control 3 different sensors (Temperature sensor, light sensor and Potentiometer) using ADC asynchronous conversion to check the readings of each sensor and return its value, then displaying the values on LCD with the help of interrupt.

## Components
  - ATmega32 AVR Microcontroller.
  - LM35 Temperature sensor.
  - LDR Light sensor.
  - Potentiometer.
  - LCD 4x20.
  - LED.

## Features
This system allows the user to read and display temperature sensor, LDR sensor and Potentiometer sensor values when reaches a certain value, then triggering an intrrupt to display the range values on the LCD screen and turns on the LED as a sign of warning for the user.
