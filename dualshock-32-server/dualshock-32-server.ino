#include <Ps3Controller.h>
#include <WiFi.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <string>
#include <Preferences.h>
#include "ControllerState.h"

BLEServer* pServer = nullptr;
BLECharacteristic* pCharacteristic = nullptr;

Preferences preferences;

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        String value = pCharacteristic->getValue();
        if (value.length() > 0) {
            Serial.println("Received JWT:");
            Serial.println(value.c_str());
            preferences.begin("jwt", false);
            preferences.putString("token", value);
            preferences.end();
        }
    }
};

void loadConfig() {
  // Open file for reading
  File file = SPIFFS.open(CONFIG_FILE, FILE_READ);
  if (!file) {
    Serial.println("Failed to open config file for reading");
    return;
  }

  // Read file into a string
  String jsonString;
  while (file.available()) {
    jsonString += char(file.read());
  }
  file.close();

  // Create a JSON object
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, jsonString);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // Load button pins from the JSON object
  for (int i = 0; i < numberOfButtons; i++) {
    buttonPins[i] = doc["buttonPins"][i] | buttonPins[i];
  }
}

int batteryLevel = 0;
ControllerState controllerState;

void onCommandReceived() {
  controllerState.setButtonCross(Ps3.event.button_down.cross);
  if (Ps3.event.button_up.cross)
    controllerState.setButtonCross(false);

  controllerState.setButtonSquare(Ps3.event.button_down.square);
  if (Ps3.event.button_up.square)
    controllerState.setButtonSquare(false);

  controllerState.setButtonTriangle(Ps3.event.button_down.triangle);
  if (Ps3.event.button_up.triangle)
    controllerState.setButtonTriangle(false);

  controllerState.setButtonCircle(Ps3.event.button_down.circle);
  if (Ps3.event.button_up.circle)
    controllerState.setButtonCircle(false);

  controllerState.setButtonUp(Ps3.event.button_down.up);
  if (Ps3.event.button_up.up)
    controllerState.setButtonUp(false);

  controllerState.setButtonRight(Ps3.event.button_down.right);
  if (Ps3.event.button_up.right)
    controllerState.setButtonRight(false);

  controllerState.setButtonDown(Ps3.event.button_down.down);
  if (Ps3.event.button_up.down)
    controllerState.setButtonDown(false);

  controllerState.setButtonLeft(Ps3.event.button_down.left);
  if (Ps3.event.button_up.left)
    controllerState.setButtonLeft(false);

  controllerState.setButtonL1(Ps3.event.button_down.l1);
  if (Ps3.event.button_up.l1)
    controllerState.setButtonL1(false);

  controllerState.setButtonR1(Ps3.event.button_down.r1);
  if (Ps3.event.button_up.r1)
    controllerState.setButtonR1(false);

  controllerState.setButtonL2(Ps3.event.button_down.l2);
  if (Ps3.event.button_up.l2)
    controllerState.setButtonL2(false);

  controllerState.setButtonR2(Ps3.event.button_down.r2);
  if (Ps3.event.button_up.r2)
    controllerState.setButtonR2(false);

  controllerState.setButtonL3(Ps3.event.button_down.l3);
  if (Ps3.event.button_up.l3)
    controllerState.setButtonL3(false);

  controllerState.setButtonR3(Ps3.event.button_down.r3);
  if (Ps3.event.button_up.r3)
    controllerState.setButtonR3(false);

  controllerState.setButtonSelect(Ps3.event.button_down.select);
  if (Ps3.event.button_up.select)
    controllerState.setButtonSelect(false);

  controllerState.setButtonStart(Ps3.event.button_down.start);
  if (Ps3.event.button_up.start)
    controllerState.setButtonStart(false);

  controllerState.setButtonPs(Ps3.event.button_down.ps);
  if (Ps3.event.button_up.ps)
    controllerState.setButtonPs(false);

  // Analog sticks and buttons
  if (abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2) {
    controllerState.setAnalogLeftX(Ps3.data.analog.stick.lx);
    controllerState.setAnalogLeftY(Ps3.data.analog.stick.ly);
  }

  if (abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2) {
    controllerState.setAnalogRightX(Ps3.data.analog.stick.rx);
    controllerState.setAnalogRightY(Ps3.data.analog.stick.ry);
  }

  // Trigger analog buttons with pressure levels
  controllerState.setButtonTriangle(Ps3.data.analog.button.triangle);
  controllerState.setButtonCircle(Ps3.data.analog.button.circle);
  controllerState.setButtonCross(Ps3.data.analog.button.cross);
  controllerState.setButtonSquare(Ps3.data.analog.button.square);

  // Battery level changes
  if (batteryLevel != Ps3.data.status.battery) {
    batteryLevel = Ps3.data.status.battery;
    Serial.print("The controller battery is now ");
    switch (batteryLevel) {
      case ps3_status_battery_charging: Serial.println("charging"); break;
      case ps3_status_battery_full: Serial.println("FULL"); break;
      case ps3_status_battery_high: Serial.println("HIGH"); break;
      case ps3_status_battery_low: Serial.println("LOW"); break;
      case ps3_status_battery_dying: Serial.println("DYING"); break;
      case ps3_status_battery_shutdown: Serial.println("SHUTDOWN"); break;
      default: Serial.println("UNDEFINED");
    }
  }
}

void onConnect() {
  Serial.println("Connected.");
}

enum ButtonType {
  CROSS,
  CIRCLE,
  SQUARE,
  TRIANGLE,
  LEFT,
  UP,
  RIGHT,
  DOWN,
  R1,
  R2,
  R3,
  L1,
  L2,
  L3,
  OPTIONS,
  SHARE,
  PS_BUTTON,
  ANALOG_LEFT_X,
  ANALOG_LEFT_Y,
  ANALOG_RIGHT_X,
  ANALOG_RIGHT_Y,
};

void setup() {
    Serial.begin(115200);
    Ps3.begin("FC:B4:67:F6:1B:78");  // MAC address of ESP Server
    Ps3.attach(onCommandReceived);
    Ps3.attachOnConnect(onConnect);
    

    BLEDevice::init("ESP32");
    pServer = BLEDevice::createServer();
    
    BLEService *pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
                       CHARACTERISTIC_UUID,
                       BLECharacteristic::PROPERTY_WRITE
                     );
    
    pCharacteristic->setCallbacks(new MyCallbacks());
    pCharacteristic->addDescriptor(new BLE2902());

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    
    Serial.println("Waiting for a client connection to notify...");

    preferences.begin("jwt", false);
    String storedJWT = preferences.getString("token", "No JWT stored");
    preferences.end();
}

void loop() {
  if (!Ps3.isConnected()) {
    Serial.println("Waiting for controller connection...");
    delay(100);
    return;
  }
  delay(2000);
}