🔁 SPI Communication Between ESP32-S3 and Arduino Uno (String Exchange)
--------------------------------------------------------------------------
This project demonstrates full-duplex SPI communication between an ESP32-S3 (running Zephyr RTOS) and an Arduino Uno. The goal is to send one full string from the master (ESP32-S3) and receive one full string back from the slave (Arduino Uno) during a sequence of SPI byte transfers.

--------------------------------------------------------------------------
🚀 Project Overview
--------------------------------------------------------------------------
ESP32-S3 acts as SPI Master using either SPI2 or SPI3 based on user configuration.

Arduino Uno acts as SPI Slave using standard SPI pins.

The master sends a predefined string (e.g., "ESP32S3 says hi\n").

The slave responds with another predefined string (e.g., "Arduino replies\n"), one byte at a time.

Both devices print the sent and received strings on their respective serial monitors.

Project is modular, using separate source files (spi.c, spi.h) and configuration headers.

Manual chip-select control is used to maintain compatibility with Arduino's software SPI behavior.

---------------------------------------------------------------------------------
📦 Components Used
---------------------------------------------------------------------------------
ESP32-S3 DevKitC

Arduino Uno

Jumper wires

Shared GND

Optional: Logic level shifter (for 5V Arduino to 3.3V ESP32-S3 on MISO)

--------------------------------------------------------------------------------------
📡 SPI Pin Connections
--------------------------------------------------------------------------------------
| **Signal** | **ESP32-S3 Pin** | **Arduino Uno Pin** | **Direction**   | **Description**                 |
| ---------- | ---------------- | ------------------- | --------------- | ------------------------------- |
| **MOSI**   | GPIO11           | D11                 | ESP32 → Arduino | Master Out, Slave In            |
| **MISO**   | GPIO13           | D12                 | Arduino → ESP32 | Master In, Slave Out            |
| **SCLK**   | GPIO12           | D13                 | ESP32 → Arduino | SPI Clock                       |
| **CS**     | GPIO10           | D10                 | ESP32 → Arduino | Manual Chip Select (active low) |
| **GND**    | GND              | GND                 | Shared Ground   | Required for voltage reference  |


---------------------------------------------------------------------------------------
🧠 Key Features
---------------------------------------------------------------------------------------
Full-Duplex String Exchange: Master sends a full string, and simultaneously receives a string from the slave.

Manual CS Control: The master manually asserts and de-asserts chip select for precise control.

Modular Codebase: Implementation is separated into main.c, spi_comm.c, and spi_comm.h for clarity and reusability.

SPI Bus Selection: Users can choose between SPI2 or SPI3 by setting a macro in main.c.

Zephyr RTOS Integration: Uses Zephyr logging, configuration, and device APIs.

-----------------------------------------------------------------------------------
📈 How It Works
-----------------------------------------------------------------------------------
ESP32-S3 initializes the selected SPI peripheral (SPI2 or SPI3) and CS GPIO.

In each loop:

It sends a full string to the Arduino, byte by byte.

For each byte sent, it simultaneously receives a byte from Arduino.

It collects the response until a newline character is received.

It prints both the sent and received strings to the serial console.

The transaction repeats every 2 seconds.

----------------------------------------------------------------------------------------
