#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_INA219.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// ---------- TFT ----------
#define TFT_CS   10
#define TFT_DC   2
#define TFT_RST  3
#define TFT_MOSI 7
#define TFT_SCLK 6

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// ---------- I2C ----------
#define SDA_PIN 4
#define SCL_PIN 5
#define TCA_ADDR 0x70

Adafruit_INA219 ina(0x40);

// ---------- BLE ----------
BLECharacteristic *pCharacteristic;

#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcd1234-5678-1234-5678-abcdef123456"

// ---------- VARIABLES ----------
int currentChannel = 0;

// ---------- SELECT CHANNEL ----------
void selectChannel(uint8_t ch) {
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << ch);
  Wire.endTransmission();
}

// ---------- BLE SETUP ----------
void setupBLE() {

  BLEDevice::init("SmartGrid");

  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEDevice::getAdvertising()->start();
}

// ---------- DRAW SCREEN ----------
void drawScreen(float voltage, float current, int ch) {

  tft.fillScreen(ST77XX_BLACK);

  float power = voltage * current;
  uint16_t color = (voltage > 1.0) ? ST77XX_GREEN : ST77XX_RED;

  // HEADER
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_CYAN);
  tft.setCursor(30, 5);
  tft.print("SMART GRID");

  tft.drawLine(20, 25, 220, 25, ST77XX_CYAN);

  // SOURCE
  tft.setTextSize(3);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setCursor(60, 35);
  tft.print("SRC ");
  tft.print(ch + 1);

  // VOLTAGE
  tft.setTextSize(2);
  tft.setCursor(20, 80);
  tft.print("Voltage");

  tft.setTextSize(3);
  tft.setTextColor(color);
  tft.setCursor(20, 100);
  tft.print(voltage, 2);
  tft.print("V");

  // CURRENT
  tft.setTextSize(2);
  tft.setCursor(20, 140);
  tft.setTextColor(ST77XX_WHITE);
  tft.print("Current");

  tft.setTextSize(3);
  tft.setCursor(20, 160);
  tft.print(current, 1);
  tft.print("mA");

  // POWER
  tft.setTextSize(2);
  tft.setCursor(20, 200);
  tft.print("Power");

  tft.setTextSize(3);
  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(120, 195);
  tft.print(power, 1);
  tft.print("mW");

  // STATUS
  tft.drawRect(50, 225, 140, 30, color);

  tft.setTextSize(2);
  tft.setTextColor(color);
  tft.setCursor(75, 232);

  if (voltage > 1.0) {
    tft.print("ACTIVE");
  } else {
    tft.print("OFF");
  }
}

// ---------- SETUP ----------
void setup() {

  Serial.begin(115200);

  // I2C
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000);

  // SPI
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);

  // TFT
  tft.init(240, 320);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  // BLE
  setupBLE();
}

// ---------- LOOP ----------
void loop() {

  selectChannel(currentChannel);
  delay(5);

  if (!ina.begin()) {
    Serial.println("INA FAIL");
    currentChannel++;
    if (currentChannel > 6) currentChannel = 0;
    return;
  }

  ina.setCalibration_32V_2A();
  delay(2);

  float voltage = ina.getBusVoltage_V();
  float current = ina.getCurrent_mA();

  if (voltage < 0.5) voltage = 0;
  if (abs(current) < 0.5) current = 0;

  Serial.print("CH ");
  Serial.print(currentChannel);
  Serial.print(" V=");
  Serial.print(voltage);
  Serial.print(" I=");
  Serial.println(current);

  drawScreen(voltage, current, currentChannel);

  String data = "CH:" + String(currentChannel + 1) +
                ",V:" + String(voltage, 2) +
                ",I:" + String(current, 1);

  pCharacteristic->setValue(data.c_str());
  pCharacteristic->notify();

  currentChannel++;
  if (currentChannel > 6) currentChannel = 0;

  delay(1500);
}
