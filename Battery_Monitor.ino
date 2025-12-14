#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// --- USER CONFIGURATION (EDIT THIS) ---
const float BATTERY_CAPACITY_AH = 100.0; // Battery size
const float ZERO_OFFSET = 2.525;         // CALIBRATION NUMBER
const float VOLT_R1 = 33000.0;           // 33k Resistor
const float VOLT_R2 = 11000.0;           // 11k Resistor

// --- SENSOR SETTINGS ---
const float FULL_CHARGE_VOLTAGE = 14.2;  // Reset % at this voltage
const float ACS_SENSITIVITY = 0.066;     // 66mV/A for ACS712-30A

// --- PINS ---
#define VOLT_PIN A0
#define CURR_PIN A1
#define TEMP_PIN 2
#define LED_PIN 13

// --- OBJECTS ---
Adafruit_SSD1306 display(128, 64, &Wire, -1);
OneWire oneWire(TEMP_PIN);
DallasTemperature sensors(&oneWire);

// --- VARIABLES ---
float voltage = 0.0;
float amps = 0.0;
float tempC = 0.0;
float currentCapacity = BATTERY_CAPACITY_AH; 
unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  
  pinMode(LED_PIN, OUTPUT);
  
  // Try to start screen. If fails, loop forever.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Screen failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  lastTime = millis();
}

void loop() {
  // 1. READ VOLTAGE (Using 33k/11k Divider)
  float vRaw = analogRead(VOLT_PIN) * (5.0 / 1024.0);
  voltage = vRaw / (VOLT_R2 / (VOLT_R1 + VOLT_R2));

  // 2. READ CURRENT (Amps) with Reversed Polarity Fix
  float acsVoltage = (analogRead(CURR_PIN) * 5.0) / 1024.0;
  amps = -((acsVoltage - ZERO_OFFSET) / ACS_SENSITIVITY);
  
  // Noise Gate: If amps are tiny (< 0.2A), show 0
  if (abs(amps) < 0.20) amps = 0; 

  // 3. READ TEMPERATURE
  sensors.requestTemperatures(); 
  tempC = sensors.getTempCByIndex(0);

  // 4. COULOMB COUNTING (Battery %)
  unsigned long currentTime = millis();
  // Calculate hours passed since last loop
  float hoursElapsed = (currentTime - lastTime) / 3600000.0;
  
  // Subtract/Add energy
  currentCapacity += (amps * hoursElapsed);
  
  // Solar Auto-Sync
  if (voltage >= FULL_CHARGE_VOLTAGE) currentCapacity = BATTERY_CAPACITY_AH;
  
  // Safety Clamps
  if (currentCapacity < 0) currentCapacity = 0;
  if (currentCapacity > BATTERY_CAPACITY_AH) currentCapacity = BATTERY_CAPACITY_AH;
  
  int percent = (currentCapacity / BATTERY_CAPACITY_AH) * 100;

  // 5. UPDATE SCREEN
  display.clearDisplay();
  
  // Row 1: Voltage & Temp
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print(voltage, 1); display.print("V");
  display.setCursor(80,0);
  display.print(tempC, 0); display.print("C");

  // Row 2: Amps
  display.setCursor(0, 16);
  display.print("Flow: "); display.print(amps, 1); display.print("A");

  // Row 3: BIG Percentage
  display.setTextSize(2);
  display.setCursor(0, 35);
  display.print(percent); display.print("%");
  
  // Capacity Ah
  display.setTextSize(1);
  display.setCursor(60, 42);
  display.print(currentCapacity, 0); display.print("Ah");

  display.display();
  
  // --- SERIAL PRINTING ---
  Serial.print("V: "); Serial.print(voltage);
  Serial.print(" | A: "); Serial.print(amps);
  Serial.print(" | Cap: "); Serial.print(currentCapacity);
  Serial.print("Ah | "); Serial.print(percent); Serial.println("%");

  lastTime = currentTime;

  // HEARTBEAT BLINK
  digitalWrite(LED_PIN, HIGH); 
  delay(100);                  
  digitalWrite(LED_PIN, LOW);  
  delay(900);                  
}