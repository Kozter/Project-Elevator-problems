#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

const char * networkName = "NetworkName";
const char * networkPswd = "NetworkPassword";
const char * hostDomain = "192.168.86.151";
const int hostPort = 4000;
const int LED_PIN = LED_BUILTIN;

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

const float X_THRESHOLD = 2.0;
const float Y_THRESHOLD = 2.0;
const float Z_THRESHOLD = 2.0;

void connectToWiFi(const char * ssid, const char * pwd)
{
  Serial.println("Connecting to WiFi network: " + String(ssid));
  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED) 
  {
    digitalWrite( LED_PIN, !digitalRead(LED_PIN) );
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void requestURL(const char * host, int port)
{
  Serial.println("Connecting to domain: " + String(host));

  WiFiClient client;
  if (!client.connect(host, port))
  {
    Serial.println("connection failed");
    return;
  }
  Serial.println("Connected!\n");

  String dataToSend = "elevator_id=1&x=" + String(lis.x) + "&y=" + String(lis.y) + "&z=" + String(lis.z);
  int dataStringLength = dataToSend.length();
  client.print((String)"POST /elevator-data HTTP/1.1\r\n" +
               "Host: " + String(host) + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: "+dataStringLength+"\r\n"+
               "Connection: close\r\n\r\n"+
               dataToSend);

  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    if (millis() - timeout > 5000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  while (client.available()) 
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println("closing connection");
  client.stop();
}

void setup()
{
  Serial.begin(115200);
  delay(5000);
  
  if (! lis.begin(0x18)) {
    Serial.println("Couldn't start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  lis.setDataRate(LIS3DH_DATARATE_50_HZ);

  connectToWiFi(networkName, networkPswd);
  delay(1000);
  requestURL(hostDomain, hostPort);
}

void loop()
{
  lis.read();

  Serial.print("X:  "); Serial.print(lis.x);
  Serial.print("  \tY:  "); Serial.print(lis.y);
  Serial.print("  \tZ:  "); Serial.println(lis.z);

  bool alert = false;
  if (abs(lis.x) > X_THRESHOLD || abs(lis.y) > Y_THRESHOLD || abs(lis.z) > Z_THRESHOLD) {
    alert = true;
  }
  delay(500);

  if (alert) {
    requestURL(hostDomain, hostPort);
  }
}
