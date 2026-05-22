// 
// GAS LEAKAGE DETECTION SYSTEM 
// Components: MQ-2 Sensor, Buzzer, Fan, Pump (two 1-channel relay modules) 
// 
#define MQ2_PIN A0 // MQ-2 sensor analog pin 
#define BUZZER_PIN 8  // Buzzer control pin 
#define RELAY_FAN 9   // Fan relay IN pin 
#define RELAY_PUMP 10  // Pump relay IN pin 
 
int gasLevel = 0; 
int threshold = 30; // Adjust after calibration 
 
 
void setup() { 
Serial.begin(9600); 
 
pinMode(MQ2_PIN, INPUT); 
pinMode(BUZZER_PIN, OUTPUT); 
pinMode(RELAY_FAN, OUTPUT); 
pinMode(RELAY_PUMP, OUTPUT); 
 
// For active-HIGH relay modules: HIGH = ON, LOW = OFF 
digitalWrite(BUZZER_PIN, LOW); // Buzzer OFF 
digitalWrite(RELAY_FAN, LOW);  // Fan OFF 
digitalWrite(RELAY_PUMP, LOW);  // Pump OFF 
 
Serial.println("Gas Leakage Detection System Initialized..."); 
}
void loop() { 
gasLevel = analogRead(MQ2_PIN); // Read gas sensor value 
Serial.print("Gas Level: "); 
Serial.println(gasLevel); 
 
 
if (gasLevel > threshold) { 
// Gas detected — turn ON safety actions 
Serial.println("⚠️ Gas Detected! Activating Fan, Pump & Buzzer..."); 
digitalWrite(BUZZER_PIN, HIGH); // Buzzer ON 
digitalWrite(RELAY_FAN, HIGH); // Fan ON 
digitalWrite(RELAY_PUMP, HIGH); // Pump ON 
} 
else { 
// Safe condition — turn OFF everything 
Serial.println("✅ Safe Environment."); 
digitalWrite(BUZZER_PIN, LOW); // Buzzer OFF 
digitalWrite(RELAY_FAN, LOW);  // Fan OFF 
digitalWrite(RELAY_PUMP, LOW);  // Pump OFF 
} 
delay(1000); // Update every second 
}