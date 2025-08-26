#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>
char ssid[] = "IBN-B";   
char pass[] = "CUPunjab";

const char broker[] = "broker.emqx.io";
int port = 1883;
const char topic[] = "SIT210/wave";
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const int ledPin = 4;

void blinkWave() {
  
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(300);
    digitalWrite(ledPin, LOW);
    delay(300);
  }
}

void blinkPat() {
  
  for (int i = 0; i < 2; i++) {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
  }
}
void handleIncomingMessages() {
  mqttClient.poll(); 
  while (mqttClient.available()) {
   
    String message = "";
    while (mqttClient.available()) {
      message += (char)mqttClient.read();
    }
    Serial.print("Message: ");
    Serial.println(message);

    if (message.indexOf("Tisha waved") != -1) {
      blinkWave();
    } else if (message.indexOf("Tisha Patted ") != -1) {
      blinkPat();
    }

   
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
WiFi.begin(ssid, pass);
   
  

  mqttClient.connect(broker, port);
    
  mqttClient.subscribe(topic);
  
}

void loop() {
  
  handleIncomingMessages();
}
