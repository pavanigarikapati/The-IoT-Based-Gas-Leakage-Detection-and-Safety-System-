#define BLYNK_TEMPLATE_ID   "Enter your template id"
#define BLYNK_TEMPLATE_NAME "Enter your template name"
#define BLYNK_AUTH_TOKEN    "enter your blynk auth token"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

char ssid[] = "enter your wifi name";
char pass[] = "enter your wifi password";

#define MQ2_PIN     A0
#define BUZZER_PIN  D5
#define RELAY_FAN   D6
#define RELAY_PUMP  D7

int gasLevel = 0;
int threshold = 300;

BlynkTimer timer;

void sendSensorData()
{
  gasLevel = analogRead(MQ2_PIN);

  Blynk.virtualWrite(V0, gasLevel);

  Serial.print("Gas Level: ");
  Serial.println(gasLevel);

  if (gasLevel > threshold)
  {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_FAN, LOW);
    digitalWrite(RELAY_PUMP, LOW);

    Blynk.virtualWrite(V1, 1);
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V3, 1);

    Blynk.logEvent("gas_alert", "⚠️ Gas leakage detected!");
  }
  else
  {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RELAY_FAN, HIGH);
    digitalWrite(RELAY_PUMP, HIGH);

    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("===== Gas Leakage Detection System Booting =====");

  pinMode(MQ2_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_PUMP, OUTPUT);

  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(RELAY_FAN, HIGH);
  digitalWrite(RELAY_PUMP, HIGH);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, sendSensorData);
}

void loop()
{
  Blynk.run();
  timer.run();
}