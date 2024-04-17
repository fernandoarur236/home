# Introduction

#### This Repo contains various projects and applications based on the ATmega32 microcontroller and their corresponding web applications.
Smart Home Project using ATmega32 drivers and web application. In addition to implementing various experiments such as Logic Analyzer & Oscilloscope, ... **further details and the code are in the below links**
#### [Smart Home](https://github.com/ItzEnigma/avr-projects/tree/main/Smart%20Home)
#### [AVR Experiments](https://github.com/ItzEnigma/avr-projects/tree/main/Experiments)
---
# 1-Smart Home project

A GUI-based smart home that enables the user to monitor and control his home remotely using a web application and only one microcontroller _(ATmega32)_.
The smart home implemented has various features for both automatic and manual control (remotely).

# 2-Computer Interface Experiments

Implementing various experiments with ATmega32 microcontroller and using a web application for visualization and control.

- SW Debugger
- Wave Generator
- Logic Analyzer
- Oscilloscope
---
# Smart Home project

A GUI-based smart home that enables the user to monitor and control his home remotely using a web application and only one microcontroller _(ATmega32)_.

## Features

### 1- Web-Application Features
__a)__ User can monitor indoor temperature

__b)__ User can monitor and control Door lock

__c)__ User can monitor and control Fan status

__d)__ User can change Door lock password

__e)__ User can change light intensity of the home

__f)__ User can control his electrical devices

__g)__ User can see the current weather status

__h)__ User can use voice commands to control the house _(as a form of smart assistance)_

### 2- Embedded System Features
__a)__ Communication is wirelessly using HC-12 _(Half-Duplex Wireless 433.4-473.0 MHz RF module)_

__b)__ User can enter the door lock password using a keypad

__c)__ User can interact using LCD 2*16

__d)__ Fan can be manually controlled or automatically controlled using the indoor temperature of the LM35 sensor. Speed is set using the PWM of the timer

__e)__ Light can be manually controlled or automatically controlled using the indoor light intensity of the LDR 

__f)__ Electrical devices control is done by using a relay, which are controlled remotely from the application.

__g)__ Password is saved on the internal EEPROM of the microcontroller

__h)__ Door can be locked/unlocked remotely using servo motor _(simulating door lock)_

#### Interfacing With:
|   LCD  	| Keypad 	|  Servo Motor 	|
|:------:	|:------:	|:------------:	|
|  **LM35**  	|   **LDR**  	|   **DC Motor**   	|
| **Buzzer** 	|  **HC12**  	| **Relay & Lamp** 	|

#### Peripherals:
|  DIO 	| Timers 	| EEPROM 	| ADC 	|
|:----:	|:------:	|:------:	|:---:	|
| **EXTI** 	|  **UART**  	|   **WDT**  	|     	|




## Screenshots

### 1- GUI
![Screenshot_20230326_102951](https://user-images.githubusercontent.com/90916721/227803348-cfa38e69-b38f-4496-aa45-bde57c126f24.png)

### 2- Schematic diagram
![Screenshot_20230326_102838](https://user-images.githubusercontent.com/90916721/227803383-a1126fff-0a53-490a-b329-66f7b30b2c2a.png)


## Documentation
[Documentation](https://docs.google.com/presentation/d/1y7YP8cR5dZD1iHyLEIp0PuPn0EHgvfvw/edit?usp=sharing&ouid=106048475929010470109&rtpof=true&sd=true)
[ESP-MQTT](https://drive.google.com/file/d/1Jz3RcwnsaoxRRQLXRM3B1wdH4i3xsEWM/view?usp=sharing)

