void setup() {
    Serial.begin(115200);
    Serial.println("Waiting for data reception...");
}

void loop() {
    if (Serial.available() > 0) {
        String receivedData = Serial.readStringUntil('\n');
        Serial.print("Received: ");
        Serial.println(receivedData);
    }
}
