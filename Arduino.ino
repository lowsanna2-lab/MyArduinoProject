#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal.h>

LiquidCrystal My_LCD(13,12,14,27,26,25);

const char* ssid = "Phone";
const char* password = "duck@47$";

WebServer server(80);

String receivedMessage = "Waiting for message...";

void handleRoot() {
server.send(200, "text/plain", receivedMessage);
}

void handleMessage() {
if (server.hasArg("plain")) {
receivedMessage = server.arg("plain");


    Serial.println("Received message:");
    Serial.println(receivedMessage);

    server.send(200, "text/plain", "Message received");
} else {
    server.send(400, "text/plain", "Missing message");
}


}

void setup() {
Serial.begin(115200);
My_LCD.begin(16,2);
My_LCD.clear();
My_LCD.print("We Can Do It >o<");

WiFi.begin(ssid, password);

Serial.print("Connecting to Wi-Fi");

while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}

Serial.println();
Serial.println("Connected!");

Serial.print("ESP32 IP: ");
Serial.println(WiFi.localIP());

server.on("/", HTTP_GET, handleRoot);
server.on("/message", HTTP_POST, handleMessage);

server.begin();


}

void loop() {
server.handleClient();
}
