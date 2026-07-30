# ⚡ SmartGrid Monitor

> **A BLE-enabled multi-source energy monitoring system built with ESP32, INA219, TFT display, and I2C multiplexer support.**

---

## 📌 Overview

**SmartGrid Monitor** is a compact embedded system designed to measure and display voltage, current, and power from multiple energy sources in real time. It uses an **INA219 current sensor**, a **TCA9548A I2C multiplexer**, a **ST7789 TFT display**, and **Bluetooth Low Energy (BLE)** to show live energy data locally and broadcast it wirelessly.

The system cycles through multiple channels, reads power data from each source, and presents a clean dashboard showing:

* Source number
* Voltage
* Current
* Power
* Active / OFF status

This makes it useful for **smart energy monitoring**, **renewable source tracking**, **lab prototypes**, and **IoT-based power management systems**.

---

## ✨ Features

* Real-time voltage, current, and power monitoring
* Support for multiple INA219 channels through I2C multiplexer
* Live TFT dashboard with color-coded status
* BLE data broadcasting
* Compact and readable embedded UI
* Automatic channel switching
* Serial debug output for troubleshooting
* Low-cost modular energy monitoring setup

---

## 🛠 Hardware Used

| Component                | Purpose                                |
| ------------------------ | -------------------------------------- |
| ESP32 / compatible board | Main controller                        |
| INA219                   | Voltage and current sensing            |
| TCA9548A I2C multiplexer | Channel selection for multiple sensors |
| ST7789 TFT display       | Local visual output                    |
| Jumper wires             | Connections                            |
| Power sources            | Test inputs for monitoring             |

---

## 📁 Code Structure

```text
smartgrid/
├── main.ino        # Main firmware
├── README.md       # Project documentation
└── wiring.png      # Optional circuit diagram
```

---

## 🔌 Pin Connections

### TFT Display (ST7789)

| TFT Pin | ESP32 Pin |
| ------- | --------- |
| CS      | GPIO 10   |
| DC      | GPIO 2    |
| RST     | GPIO 3    |
| MOSI    | GPIO 7    |
| SCLK    | GPIO 6    |

### I2C Bus

| I2C Signal | ESP32 Pin |
| ---------- | --------- |
| SDA        | GPIO 4    |
| SCL        | GPIO 5    |

### TCA9548A

| Part            | Address |
| --------------- | ------- |
| I2C Multiplexer | `0x70`  |

### INA219

| Part           | Address |
| -------------- | ------- |
| Current Sensor | `0x40`  |

---

## 📚 Libraries Required

Install these libraries in Arduino IDE:

* `Wire`
* `SPI`
* `Adafruit_GFX`
* `Adafruit_ST7789`
* `Adafruit_INA219`
* `BLEDevice`
* `BLEServer`
* `BLEUtils`
* `BLE2902`

---

## 🚀 How It Works

1. The system selects an INA219 channel using the TCA9548A multiplexer.
2. It initializes the INA219 sensor on that channel.
3. Voltage and current are read from the selected source.
4. Power is calculated using:

```text
Power = Voltage × Current
```

5. The values are shown on the TFT display.
6. The same readings are sent over BLE as a text notification.
7. The system moves to the next channel and repeats.

---

## 📊 Display Output

Each screen shows:

* **SMART GRID** header
* Current source number
* Voltage in volts
* Current in milliamps
* Power in milliwatts
* Status box:

  * **ACTIVE** if voltage is present
  * **OFF** if voltage is low

---

## 📡 BLE Data Format

The BLE characteristic sends data in this format:

```text
CH:1,V:12.45,I:132.6
```

### Fields

* `CH` → Source channel number
* `V` → Voltage
* `I` → Current

This can be read by a mobile app, desktop app, or custom dashboard.

---

## ⚙️ Working Principle

```text
Energy Source
     ↓
INA219 Sensor
     ↓
TCA9548A I2C Multiplexer
     ↓
ESP32 Reads Data
     ↓
TFT Display + BLE Broadcast
```

---

## 🧪 Output Logic

* Voltage below `0.5V` is treated as `0`
* Current below `0.5 mA` is treated as `0`
* Source is marked **ACTIVE** if voltage is above `1.0V`
* Source is marked **OFF** otherwise

---

## 🧰 Setup Instructions

### 1. Open Arduino IDE

Install the required board package for ESP32.

### 2. Install libraries

Use Library Manager to install:

* Adafruit GFX
* Adafruit ST7789
* Adafruit INA219

### 3. Connect hardware

Wire the TFT, INA219, and TCA9548A as shown above.

### 4. Upload the code

Select the correct ESP32 board and COM port, then upload.

### 5. Open Serial Monitor

Set baud rate to:

```text
115200
```

---

## 🔧 Troubleshooting

| Problem                      | Possible Fix                                         |
| ---------------------------- | ---------------------------------------------------- |
| `INA FAIL` in serial monitor | Check wiring, channel selection, or sensor address   |
| Blank TFT screen             | Verify SPI pins and display wiring                   |
| BLE not visible              | Ensure BLE is enabled and device is powered          |
| Wrong readings               | Check calibration and source connection              |
| Data stuck on one channel    | Confirm TCA9548A channel wiring and sensor placement |

---

## 📈 Future Improvements

* Store readings to SD card
* Add WiFi dashboard support
* Show graphs on the display
* Send data to cloud platforms like ThingSpeak
* Add automatic alerts for low voltage
* Use better power calibration
* Add more source channels
* Create a mobile BLE app
* Add battery health estimation

---

## 🎯 Applications

* Renewable energy monitoring
* Smart grid prototype
* Solar and wind source tracking
* Laboratory testing
* Educational projects
* IoT power systems
* Embedded energy dashboards

---

## 👨‍💻 Author

**Arpan Biswas**

Student • Maker • Embedded Systems Developer

---

## 📄 License

This project is open for educational and personal use. Add your preferred license here if needed.

---

## ⭐ Final Note

**SmartGrid Monitor** is a practical embedded prototype for visualizing energy data in a clean and scalable way. It combines sensing, display, and wireless communication into one compact system.
