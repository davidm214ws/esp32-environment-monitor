#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <PubSubClient.h>
#include "config.h"

static constexpr unsigned long PUBLISH_INTERVAL_MS = 10000;
static constexpr unsigned long RECONNECT_INTERVAL_MS = 5000;
static constexpr int I2C_SDA_PIN = 21;
static constexpr int I2C_SCL_PIN = 22;

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);
Adafruit_BME280 bme;
bool sensorReady = false;
unsigned long lastPublish = 0;
unsigned long lastReconnectAttempt = 0;

void connectWiFiIfNeeded() {
  if (WiFi.status() == WL_CONNECTED) return;
  if (WiFi.getMode() != WIFI_STA) WiFi.mode(WIFI_STA);
  static unsigned long lastWifiAttempt = 0;
  const unsigned long now = millis();
  if (lastWifiAttempt == 0 || now - lastWifiAttempt >= RECONNECT_INTERVAL_MS) {
    lastWifiAttempt = now;
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  }
}

void connectMQTTIfNeeded() {
  if (WiFi.status() != WL_CONNECTED || mqtt.connected()) return;
  const unsigned long now = millis();
  if (lastReconnectAttempt != 0 && now - lastReconnectAttempt < RECONNECT_INTERVAL_MS) return;
  lastReconnectAttempt = now;
  if (mqtt.connect(DEVICE_ID)) {
    Serial.println("Connected to MQTT broker");
  } else {
    Serial.printf("MQTT connection failed, state=%d\n", mqtt.state());
  }
}

void publishReading() {
  if (!sensorReady || !mqtt.connected()) return;
  const float temperature = bme.readTemperature();
  const float humidity = bme.readHumidity();
  const float pressure = bme.readPressure() / 100.0f;
  if (isnan(temperature) || isnan(humidity) || isnan(pressure)) {
    Serial.println("Sensor returned invalid values");
    return;
  }
  char payload[192];
  snprintf(payload, sizeof(payload),
           "{\"device_id\":\"%s\",\"temperature_c\":%.2f,\"humidity_pct\":%.2f,\"pressure_hpa\":%.2f}",
           DEVICE_ID, temperature, humidity, pressure);
  if (mqtt.publish(MQTT_TOPIC, payload)) Serial.println(payload);
  else Serial.println("MQTT publish failed");
}

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  sensorReady = bme.begin(0x76, &Wire) || bme.begin(0x77, &Wire);
  if (!sensorReady) Serial.println("BME280 missing: check wiring/address. Publishing disabled.");
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  connectWiFiIfNeeded();
}

void loop() {
  connectWiFiIfNeeded();
  connectMQTTIfNeeded();
  if (mqtt.connected()) mqtt.loop();
  const unsigned long now = millis();
  if (lastPublish == 0 || now - lastPublish >= PUBLISH_INTERVAL_MS) {
    lastPublish = now;
    publishReading();
  }
  delay(20);
}
