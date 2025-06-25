# 🧠 PIC18F877A Drivers and Utilities

A small collection of C libraries for 8-bit PIC microcontrollers, built during high school projects.  
This repo includes basic drivers for I²C communication, interrupts, LCD displays, PWM generation, and the MPU6050 IMU — all developed for the **PIC18F877A**.

---

## 📌 About the PIC18F877A

The **PIC18F877A** is a popular 8-bit microcontroller from Microchip, widely used in educational and hobbyist projects. It features:

- 40 pins with multiple I/O ports
- Built-in USART, I²C, SPI modules
- PWM outputs
- 8-channel 10-bit ADC
- Rich interrupt system

It’s ideal for learning embedded systems programming and interfacing with basic sensors and peripherals.

---

## 📂 Included Drivers

Each module comes with `.c` and `.h` files and simple usage examples (where available):

| Module      | Description                              |
|-------------|------------------------------------------|
| `i2c`       | Basic master-mode I²C implementation     |
| `interrupt` | Setup and handlers for external/internal interrupts |
| `lcd`       | 16x2 character LCD control (4-bit mode)  |
| `pwm`       | PWM setup for controlling servos or motors |
| `mpu6050`   | Communication with the MPU6050 IMU sensor |

---

## 🛠️ Toolchain

- **Compiler:** MPLAB XC8
- **IDE:** MPLAB X IDE
- **Target MCU:** PIC18F877A

---

## 🚀 Getting Started

1. Clone the repo  
   ```bash
   git clone https://github.com/yourusername/pic18f877a-drivers
