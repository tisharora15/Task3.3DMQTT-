#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>

char ssid[] = "IBN-B";   
char pass[] = "CUPunjab";

const char broker[] = "broker.emqx.io";
int port = 1883;
const char topic[] = "SIT210/wave";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);


const int trigPin = 2;
const int echoPin = 4;

long duration;
int distance;

int readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void publishMessage(String message) {
  
    mqttClient.connect(broker, port);
  
  mqttClient.beginMessage(topic);
  mqttClient.print(message);
  mqttClient.endMessage();
  Serial.print("Published: ");
  Serial.println(message);
}

void setup() { 
  Serial.begin(9600); 
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); WiFi.begin(ssid, pass) ;
 mqttClient.connect(broker, port); }

void loop() {
  mqttClient.poll(); 

  int dist = readDistance();
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");

  if (dist > 0 && dist < 15) {
    publishMessage("Tisha waved ");
    delay(2000);
  } else if (dist >= 15 && dist < 30) {
    publishMessage("Tisha patted ");
    delay(2000);
  }

  delay(500);
}
