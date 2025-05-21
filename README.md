# Microcurrent Therapy with Arduino ESP32 & MCP4251

This project demonstrates how to use an Arduino ESP32 microcontroller and the MCP4251 digital potentiometer to create a microcurrent therapy device.

## Hardware Used

- **ESP32 Development Board**
- **MCP4251 Digital Potentiometer**
- Electrodes for therapy application
- Supporting components (resistors, wires, breadboard, etc.)

## Features

- Adjustable microcurrent output via MCP4251
- Control and monitoring through ESP32
- Potential for Bluetooth or Wi-Fi control (expandable)

## Wiring Diagram

```
[ESP32] ---- [MCP4251] ---- [Electrodes]
```

- Connect MCP4251 via SPI to ESP32.
- Output from MCP4251 goes to electrodes.

## Getting Started

1. **Clone this repository**
2. **Install Arduino IDE** and ESP32 board support
3. **Connect hardware** as per the wiring diagram
4. **Upload the code** to your ESP32

## Safety Notice

**This project is for educational purposes only. Consult a medical professional before using any therapy device.**

## Disclaimer

The creator of this project is not responsible for any injury, damage, or adverse effects resulting from the use or misuse of this device. Use at your own risk.

## License

MIT License
