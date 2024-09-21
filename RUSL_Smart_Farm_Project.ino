//© Real-Time Farm Monitoring System - 2024 RUSL

#include <DHT.h>
#include <FirebaseESP32.h>
#include <Wire.h>

// Network credentials (replace with your own)
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"

// Firebase project details (replace with your own)
#define API_KEY "your_firebase_api_key"
#define DATABASE_URL "your_database_url"

// Pin configuration
#define DHT_PIN 2        // DHT11 sensor pin (temperature & humidity)
#define SOIL_PIN1 34     // Soil moisture sensor 1 pin
#define SOIL_PIN2 35     // Soil moisture sensor 2 pin

#define RELAY_1_PIN 12   // Relay 1 pin (water pump)
#define RELAY_2_PIN 13   // Relay 2 pin (humidity controller)
#define RELAY_3_PIN 14   // Relay 3 pin (temperature controller)

#define DHT_TYPE DHT11   // DHT sensor type

DHT dht(DHT_PIN, DHT_TYPE);  
FirebaseData firebaseData;  

// Thresholds
int SET_MOISTURE = 3500;  // Threshold for soil moisture (0 = wet, 4000 = dry)
int SET_HUMIDITY = 75;    // Threshold for humidity (%)
int SET_TEMP = 30;        // Threshold for temperature (Celsius)

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Connect to Firebase
  Firebase.begin(DATABASE_URL, API_KEY, &firebaseData);

  // Initialize DHT sensor
  dht.begin();

  // Set relay pins as outputs
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
  pinMode(RELAY_3_PIN, OUTPUT);

  // Set LED indicators as outputs
  pinMode(19, OUTPUT);  // Water level - low
  pinMode(18, OUTPUT);  // Water level - normal
  pinMode(5, OUTPUT);   // Humidity - high
  pinMode(4, OUTPUT);   // Humidity - low
  pinMode(22, OUTPUT);  // Temperature - high
  pinMode(15, OUTPUT);  // Temperature - low
}

void loop() {
  // Read sensor data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int SOIL_READ1 = analogRead(SOIL_PIN1);
  int SOIL_READ2 = analogRead(SOIL_PIN2);
  int soilMoisture = (SOIL_READ1 + SOIL_READ2) / 2;

  // Upload data to Firebase
  Firebase.setFloat(firebaseData, "temperature", temperature);
  Firebase.setFloat(firebaseData, "humidity", humidity);
  Firebase.setInt(firebaseData, "soilMoisture", soilMoisture);

  // Print data to Serial Monitor
  Serial.print("TEMPERATURE: ");
  Serial.println(temperature);
  Serial.print("HUMIDITY: ");
  Serial.println(humidity);
  Serial.print("MOISTURE: ");
  Serial.println(soilMoisture);
  Serial.println("_________________________");

  // Control Relay 1 (water pump) based on soil moisture
  if (soilMoisture > SET_MOISTURE) {
    digitalWrite(RELAY_1_PIN, HIGH);
    digitalWrite(19, HIGH);  // Water level - low indicator
    digitalWrite(18, LOW);   // Water level - normal indicator
  } else {
    digitalWrite(RELAY_1_PIN, LOW);
    digitalWrite(19, LOW);
    digitalWrite(18, HIGH);
  }

  // Control Relay 2 (humidity controller) based on humidity
  if (humidity > SET_HUMIDITY) {
    digitalWrite(RELAY_2_PIN, HIGH);
    digitalWrite(5, HIGH);  // Humidity - high indicator
    digitalWrite(4, LOW);   // Humidity - low indicator
  } else {
    digitalWrite(RELAY_2_PIN, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
  }

  // Control Relay 3 (temperature controller) based on temperature
  if (temperature > SET_TEMP) {
    digitalWrite(RELAY_3_PIN, HIGH);
    digitalWrite(22, HIGH);  // Temperature - high indicator
    digitalWrite(15, LOW);   // Temperature - low indicator
  } else {
    digitalWrite(RELAY_3_PIN, LOW);
    digitalWrite(22, LOW);
    digitalWrite(15, HIGH);
  }

  delay(1000);  // Delay between loops
}
