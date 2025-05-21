#include <SPI.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Pin definitions
const int csPin = 15;      // Chip Select for MCP4251
const int pulsePin = 2;    // PWM pulse output

// Pulse parameters
const unsigned long pulseInterval = 500;       // Interval between pulses (ms)
const unsigned int pulseWidthMicrosec = 1000000000;  // Pulse duration (µs)

// Digital Potentiometer initial setting (0-255)
byte potValue = 62; // Mid-range value

BLECharacteristic *pCharacteristic;

void setPotValue(byte pot, byte value);

class MyBLECallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) override {
    String tempStr = pCharacteristic->getValue();
    std::string rxValue(tempStr.c_str());
    if (rxValue.length() > 0) {
      byte newVal = (byte)tempStr.charAt(0);
      potValue = newVal;
      setPotValue(0, potValue);
      Serial.print("Potentiometer updated to: ");
      Serial.println(potValue);
    }
  }
};


void setup() {
  Serial.begin(115200);
  while (!Serial) { }

  // Setup pulse output pin
  pinMode(pulsePin, OUTPUT);
  digitalWrite(pulsePin, LOW);
  
  // Setup SPI for MCP4251
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);
  SPI.begin();
  
  // Initialize the potentiometer with the starting value
  setPotValue(0, potValue);
  Serial.println("System Initialized. Awaiting BLE commands...");

  // Initialize BLE
  BLEDevice::init("ESP32_MENS");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  
  // Create BLE characteristic with write property
  pCharacteristic = pService->createCharacteristic(
                       CHARACTERISTIC_UUID,
                       BLECharacteristic::PROPERTY_WRITE
                     );
  pCharacteristic->setCallbacks(new MyBLECallbacks());
  pCharacteristic->addDescriptor(new BLE2902());
  
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();
  Serial.println("BLE Advertising started...");
}

void loop() {
  // Pulse generation remains the same
  Serial.println("Pulse ON");
  digitalWrite(pulsePin, HIGH);
  delayMicroseconds(pulseWidthMicrosec);
  digitalWrite(pulsePin, LOW);
  Serial.println("Pulse OFF");
  delay(pulseInterval);
}

void setPotValue(byte pot, byte value) {
  byte command;
  if (pot == 0) {
    command = 0x00;
  } else if (pot == 1) {
    command = 0x10;
  } else {
    return;
  }
  
  digitalWrite(csPin, LOW);
  SPI.transfer(command);
  SPI.transfer(value);
  digitalWrite(csPin, HIGH);
  delayMicroseconds(10);
}
