#include <Ps3Controller.h>
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  Ps3.attach(onCommandReceived);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("FC:B4:67:F6:1B:78"); // MAC address of ESP Server

  Serial.println("Dualshock 32 Server is ready.");
}

void loop() {
  if (!Ps3.isConnected()) {
    Serial.println("Waiting for controller connection...");
    delay(100);
    return; 
  }
  delay(2000);
}

void onCommandReceived() {
  if (Ps3.event.button_down.cross) {
    Serial.println("Cross pressed");
  }
  if (Ps3.event.button_up.cross) {
    Serial.println("Cross released");
  }

  if (Ps3.event.button_down.triangle) {
    Serial.println("Triangle presssed");
  }

  if (Ps3.event.button_down.square) {
    Serial.println("Square pressed");
  }

  if (Ps3.event.button_down.circle) {
    Serial.println("Circle pressed");
  }
}

void onConnect() {
  Serial.println("Connected.");
}