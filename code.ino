#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#define SENSORPIN1 7 //Sensor 1 is on the right
#define SENSORPIN2 8 //Sensor 2 is on the left

// Initiate LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

long end_time; // When Sensor 2 is triggered
long start_time; // When Sensor 1 is triggered
long elapsed_time; // End time minus start time

float kph; // Speed calculated

int trigger1 = 0; // Sensor 1
int trigger2 = 0; // Sensor 2
int sensor1State; // Sensor 1 status
int sensor2State; // Sensor 2 status

void setup() {
  pinMode(SENSORPIN1, INPUT); // Sensor 1 as input
  digitalWrite(SENSORPIN1, HIGH); // Turn on the pullup
  pinMode(SENSORPIN2, INPUT); // Sensor 2 s input
  digitalWrite(SENSORPIN2, HIGH); // Turn on the pullup
  Serial.begin(9600);
  lcd.begin(16, 2); 
}

// Function to determine speed
void speed()
{
  // subtract end time from start time to get total time
  elapsed_time = ((end_time - start_time));

  // convert mm/s to kph
  kph = ((750000000 / elapsed_time) * 0.00036);
  lcd.print(kph);
  lcd.print("Km/h");
  lcd.setCursor(0, 1);
  lcd.print(elapsed_time);
  lcd.print(" us");
  //μs is the short for microseconds 
  Serial.print(kph);
  Serial.println("km/h");
  Serial.print(elapsed_time);
  Serial.println(" us");
  delay(5000);
  lcd.clear();
  lcd.print("Ready");
  delay(500);
  lcd.clear();
}


void loop() {
  // Read the state of the IR sensor 1:
  sensor1State = digitalRead(SENSORPIN1);

  // See if IR beam of sensor 1 has been broken
  if (sensor1State == LOW) {

    // Check to make sure both sensors have not triggered
    if (trigger1 == 0 && trigger2 == 0) {

      // Save time when sensor 1 was triggered
      start_time = micros();

      // Prevent sensor 1 from triggering again
      trigger1 = 1;
    }
  }

  // Read the state of the IR sensor 2:
  sensor2State = digitalRead(SENSORPIN2);

  // See if IR beam of sensor 2 has been broken
  if (sensor2State == LOW) {

    // Check to make sure sensor 1 has triggered but not sensor2
    if (trigger2 == 0 && trigger1 == 1) {

      // Save time when sensor 2 was triggered
      end_time = micros();

      // Run speed function
      speed();

      // Prevent sensor 2 from triggering again
      trigger2 = 1;
    }
    delay(1000);

    // Reset both sensors
    trigger1 = 0;
    trigger2 = 0;
  }
}
