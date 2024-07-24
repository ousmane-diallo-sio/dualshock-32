#include <Arduino.h>
#include <BleGamepad.h>

BleGamepad bleGamepad("Dualshock 32", "Lemonware", 100);

void processReceivedData(String data) {
  data.trim();

  if (data.startsWith("PRESS ")) {
    int buttonId = data.substring(6).toInt();
    if (buttonId >= 1 && buttonId <= 17) {
      bleGamepad.press(buttonId);
      Serial.print("Pressed button: ");
      Serial.println(buttonId);
    }
  } else if (data.startsWith("RELEASE ")) {
    int buttonId = data.substring(8).toInt();
    if (buttonId >= 1 && buttonId <= 17) {
      bleGamepad.release(buttonId);
      Serial.print("Released button: ");
      Serial.println(buttonId);
    }
  } else if (data.startsWith("MOVE Left Stick X ")) {
    int xStartIndex = data.indexOf("X: ") + 3;
    int xEndIndex = data.indexOf(" Y: ");
    int yStartIndex = xEndIndex + 4;

    int leftX = data.substring(xStartIndex, xEndIndex).toInt();
    int leftY = data.substring(yStartIndex).toInt();

    bleGamepad.setLeftThumb(leftX, leftY);
    Serial.print("Moved left stick to (");
    Serial.print(leftX);
    Serial.print(", ");
    Serial.print(leftY);
    Serial.println(")");
  } else if (data.startsWith("MOVE Right Stick Y ")) {
    int xStartIndex = data.indexOf("X: ") + 3;
    int xEndIndex = data.indexOf(" Y: ");
    int yStartIndex = xEndIndex + 4;

    int rightX = data.substring(xStartIndex, xEndIndex).toInt();
    int rightY = data.substring(yStartIndex).toInt();

    bleGamepad.setRightThumb(rightX, rightY);
    Serial.print("Moved right stick to (");
    Serial.print(rightX);
    Serial.print(", ");
    Serial.print(rightY);
    Serial.println(")");
  } else {
    Serial.println("Unknown command");
  }

  bleGamepad.sendReport();
}


void setup() {
  Serial.begin(115200);
  Serial.println("Waiting for data reception...");

  BleGamepadConfiguration bleGamepadConfig;
  bleGamepadConfig.setAutoReport(false);
  bleGamepadConfig.setButtonCount(17);
  bleGamepad.begin(&bleGamepadConfig);

  while (!bleGamepad.isConnected()) {
    Serial.println("Waiting for Bluetooth connection...");
    delay(500);
  }
  Serial.println("Bluetooth Gamepad connected");
}

void loop() {
  if (Serial.available() > 0) {
    String receivedData = Serial.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(receivedData);
    processReceivedData(receivedData);
  }
  delay(10);
}
