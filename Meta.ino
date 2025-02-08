#define BLYNK_TEMPLATE_NAME "META PROJECT"
#define BLYNK_AUTH_TOKEN "KK4JFjsIIeyK18Kl9kpyyxTKXn8eV1rk"
#define BLYNK_TEMPLATE_ID "TMPL325FlznL-"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

WebServer server(80);
const char* ssid = "Maulik's Pixel";
const char* password = "dave2705";

const int LDR_PIN = 27;
const int BLUE_LED_PIN = 23;
const int RELAY_PIN = 32;
const int SOIL_MOISTURE_PIN = 16;

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  timer.setInterval(1000L, checkSensors); // Check sensors every 1 second
}

void loop() {
  Blynk.run();
  timer.run();
  digitalWrite(RELAY_PIN,HIGH);
  delay(1000);
  digitalWrite(RELAY_PIN,LOW);
  delay(1000);
}

void checkSensors() {


  int lightValue = digitalRead(LDR_PIN); // Read digital value from LDR
  int moisture = analogRead(SOIL_MOISTURE_PIN); // Read digital value from soil moisture sensor

 Serial.print("Light intensity: ");
  Serial.println(lightValue);
  Serial.print("Moisture: ");
  Serial.println(moisture);

  // Control LED based on light intensity
  if (lightValue == 1) { // Adjust condition as per your requirement
    digitalWrite(BLUE_LED_PIN, HIGH);
    Blynk.virtualWrite(V0, HIGH);
    digitalWrite(RELAY_PIN,HIGH);
  } else {
    digitalWrite(BLUE_LED_PIN, LOW);
    Blynk.virtualWrite(V0, LOW);
    digitalWrite(RELAY_PIN,LOW);
  }

  // Control relay based on moisture level
  
}

//void pumpon(){digitalWrite(RELAY_PIN, HIGH);}
//void pumpoff(){digitalWrite(RELAY_PIN, LOW);}