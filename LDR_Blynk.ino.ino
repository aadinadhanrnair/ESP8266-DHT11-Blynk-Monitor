#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

#define LDR_PIN A0

BlynkTimer timer;

void sendData()
{
  int ldrValue = analogRead(LDR_PIN);

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Send value to Gauge Widget (V0)
  Blynk.virtualWrite(V0, ldrValue);

  // DARK -> LED ON
  // BRIGHT -> LED OFF
  if (ldrValue < 500)
  {
    Blynk.virtualWrite(V2, 255);
  }
  else
  {
    Blynk.virtualWrite(V2, 0);
  }
}

void setup()
{
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Send LDR data every 1 second
  timer.setInterval(1000L, sendData);
}

void loop()
{
  Blynk.run();
  timer.run();
}