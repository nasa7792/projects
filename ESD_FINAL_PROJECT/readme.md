# WIRELESS SENSOR COMMUNICATION SYSTEM

This project focuses on building a wireless sensor communincation system using the nrf24L01 module
and the stm32f411VE as the mcu.

This project was developed as the final project for ECEN 5613 Fall 2024.

## Overview block diagram
![Nalin Saxena (1)](https://github.com/user-attachments/assets/9db003a1-02ad-494f-95d6-9cb68086b814)

## List of hardware components
- Stm32F411VE Discovery
- NRF24L01
- MAX30102 heart rate sensor
- Neo 6M GPS module
- LCD display module
- SD card module

## Technologies
- I2C
- SPI
- USART

## Code structure

The code structure is divided into 2 main modules one for the transmitter node and one for the receiver node

The transmitter code is built as a state machine summarized by the below diagram

![Nalin Saxena (2)](https://github.com/user-attachments/assets/1275015e-9338-41a2-950e-3bb10a8016e4)

The receiver code is as summarized below

![reci](https://github.com/user-attachments/assets/a7b72f74-91eb-45dd-a891-a89208b7f592)

  
