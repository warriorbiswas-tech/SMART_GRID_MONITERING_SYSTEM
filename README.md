# ⚡ SmartGrid Monitoring System

<div align="center">

### **Real-Time Multi-Source Energy Monitoring using ESP32, INA219 & BLE**

*Measure • Visualize • Transmit*

![Platform](https://img.shields.io/badge/Platform-ESP32-blue?style=for-the-badge&logo=espressif)
![Display](https://img.shields.io/badge/Display-ST7789-orange?style=for-the-badge)
![BLE](https://img.shields.io/badge/Bluetooth-Low%20Energy-0082FC?style=for-the-badge&logo=bluetooth)
![Sensor](https://img.shields.io/badge/Sensor-INA219-success?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

# 📖 Overview

**SmartGrid Monitoring System** is an ESP32-based IoT project designed to monitor multiple power sources using a single INA219 current and voltage sensor connected through a **TCA9548A I²C Multiplexer**.

The system cycles through **seven independent power sources**, displaying real-time electrical parameters on a **2.8" ST7789 TFT display** while simultaneously broadcasting the measurements via **Bluetooth Low Energy (BLE)**.

The project provides a compact, scalable solution for monitoring renewable energy systems, battery banks, microgrids, educational laboratories, and research prototypes.

---

# ✨ Features

- ⚡ Real-time Voltage Measurement
- 🔋 Current Monitoring
- 📊 Instantaneous Power Calculation
- 🖥 Interactive TFT Dashboard
- 📡 Bluetooth Low Energy (BLE) Data Broadcasting
- 🔀 Multi-channel Monitoring (7 Sources)
- 📈 Live Status Indication (Active / Off)
- 🔄 Automatic Channel Scanning
- ⚙ Modular Hardware Design
- 🚀 Low-Cost IoT Architecture

---

# 🎯 Applications

- Renewable Energy Monitoring
- Smart Grid Demonstrations
- Solar Panel Testing
- Battery Management Systems
- Energy Research
- Engineering Laboratories
- Educational Projects
- IoT Demonstrations
- Embedded Systems Learning

---

# 🛠 Hardware Components

| Component | Purpose |
|------------|----------|
| ESP32 Development Board | Main Controller |
| INA219 Current Sensor | Voltage & Current Measurement |
| TCA9548A I²C Multiplexer | Multi-channel Sensor Switching |
| ST7789 TFT Display (240×320) | Real-time Dashboard |
| Power Sources (×7) | Measurement Inputs |
| Jumper Wires | Connections |
| Breadboard / PCB | Prototype Assembly |

---

# 💻 Software Stack

- Arduino IDE
- ESP32 Arduino Core
- C++
- Bluetooth Low Energy (BLE)
- Wire (I²C)
- SPI
- Adafruit GFX Library
- Adafruit ST7789 Library
- Adafruit INA219 Library

---

# 📂 Project Structure

```text
SmartGrid/
│
├── SmartGrid.ino
├── README.md
├── images/
│   ├── prototype.jpg
│   ├── dashboard.png
│   ├── wiring.png
│   └── ble_app.png
│
├── docs/
│   ├── Circuit.pdf
│   └── Report.pdf
│
└── LICENSE
```

---

# 🧠 System Architecture

```text
             Power Source 1
                    │
             Power Source 2
                    │
             Power Source 3
                    │
             Power Source 4
                    │
             Power Source 5
                    │
             Power Source 6
                    │
             Power Source 7
                    │
                    ▼
          TCA9548A I²C Multiplexer
                    │
                    ▼
             INA219 Sensor Module
                    │
                    ▼
             ESP32 Controller
            ┌──────────────┐
            │              │
            ▼              ▼
      ST7789 TFT      BLE Broadcast
            │              │
            ▼              ▼
     Local Display   Mobile / PC Client
```

---

# ⚙ Working Principle

1. The ESP32 selects one channel on the **TCA9548A** multiplexer.
2. The INA219 sensor measures the voltage and current of the selected source.
3. Instantaneous power is calculated using:

```text
Power = Voltage × Current
```

4. The measured values are displayed on the TFT screen.
5. A BLE notification containing the measurements is transmitted.
6. The controller switches to the next source.
7. The process repeats continuously for all seven channels.

---

# 📊 Parameters Measured

| Parameter | Unit |
|------------|------|
| Voltage | Volts (V) |
| Current | Milliamperes (mA) |
| Power | Milliwatts (mW) |
| Source Status | Active / Off |

---

# 📱 TFT Dashboard

The display provides:

- SmartGrid title
- Current source number
- Voltage
- Current
- Calculated power
- Color-coded status indicator
- Active/Off detection

### Status Colors

🟢 **Green** → Active Source

🔴 **Red** → No Voltage / Source Off

---

# 📡 Bluetooth Low Energy

The ESP32 advertises itself as:

```text
SmartGrid
```

Each notification contains:

```text
CH:1,V:12.45,I:135.7
```

Example:

```
CH:3
Voltage : 5.02 V
Current : 148.4 mA
Power   : 744.9 mW
```

BLE can be received using:

- nRF Connect
- LightBlue
- Custom Android App
- Custom Python Client
- Desktop BLE Applications

---

# 🔌 Wiring

## ST7789 Display

| Display Pin | ESP32 Pin |
|--------------|-----------|
| MOSI | GPIO 7 |
| SCLK | GPIO 6 |
| CS | GPIO 10 |
| DC | GPIO 2 |
| RESET | GPIO 3 |

---

## I²C

| Device | ESP32 |
|---------|--------|
| SDA | GPIO 4 |
| SCL | GPIO 5 |

---

## Multiplexer

```
ESP32
   │
TCA9548A
   │
INA219
```

Each channel connects to an independent power source.

---

# 📂 Libraries Used

```text
Wire
SPI
Adafruit_GFX
Adafruit_ST7789
Adafruit_INA219
BLEDevice
BLEServer
BLEUtils
BLE2902
```

Install using Arduino Library Manager.

---

# 🚀 Getting Started

### Clone Repository

```bash
git clone https://github.com/yourusername/SmartGrid.git
```

---

### Open

```text
SmartGrid.ino
```

---

### Install Libraries

- Adafruit GFX
- Adafruit ST7789
- Adafruit INA219
- ESP32 BLE Arduino

---

### Select Board

```
ESP32 Dev Module
```

Upload and power the board.

---

# 📈 Future Improvements

- 📊 Historical Data Logging
- ☁ MQTT / Cloud Integration
- 📡 Wi-Fi Dashboard
- 🌐 Web Server Interface
- 📱 Android Monitoring App
- 🔋 Battery State-of-Charge Estimation
- ⚠ Overcurrent Alerts
- 📉 Graphical Trend Charts
- 🌞 Renewable Energy Analytics
- ⚡ Smart Load Management

---

# 📸 Gallery

Add project images here.

```text
images/prototype.jpg
images/dashboard.png
images/wiring.png
images/ble_app.png
```

---

# 🛣 Roadmap

- [x] Multi-channel monitoring
- [x] TFT interface
- [x] BLE communication
- [x] Automatic channel switching
- [ ] Wi-Fi dashboard
- [ ] Cloud analytics
- [ ] Mobile application
- [ ] Data logging (SD Card)
- [ ] MQTT support
- [ ] OTA firmware updates

---

# 📄 License

Licensed under the **MIT License**.

---

# 👨‍💻 Author

## **Arpan Biswas**

Student Researcher • Embedded Systems Developer • IoT Enthusiast

Interested in smart energy systems, robotics, IoT, embedded electronics, and sustainable technologies.

---

# 🙏 Acknowledgements

Special thanks to:

- Espressif Systems
- Adafruit Industries
- Arduino Community
- Open-source Embedded Systems Community

---

<div align="center">

## ⭐ If you found this project useful, consider giving it a star!

**"Measure every watt. Understand every source."**

</div>
