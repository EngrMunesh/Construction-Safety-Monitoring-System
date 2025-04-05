#include <DHT.h>

// Pin configurations
const int redPin = 12;         // Red pin of the RGB module
const int greenPin = 4;        // Green pin of the RGB module
const int bluePin = 11;        // Blue pin of the RGB module
const int buzzerPin = 8;       // Buzzer pin
const int laserEmitterPin = 1; // Laser emitter pin
const int photoresistorPin = A0; // Photoresistor pin
const int flamePin = 13;       // Flame sensor pin
const int buttonPin = 3;       // Button pin
const int DHTPin = 10;         // DHT11 data pin

const int DHTType = DHT11;      // DHT11 sensor type
DHT dht(DHTPin, DHTType);

// Variables to store button state
int buttonState = HIGH;   // current state of the button
int lastButtonState = HIGH;  // previous state of the button
unsigned long lastDebounceTime = 0;  // last time the button state changed
unsigned long debounceDelay = 50;    // debounce time; increase if the output flickers

// Flags to control the alarm state
bool alarmActive = true;  // Alarm is active by default

// Function prototypes
void blinkRedLight();
void blinkBlueLight();
void triggerContinuousBuzzer();
void turnOnGreenLight();
bool isLaserBlocked();
void displayRGBColors(int redValue, int greenValue, int blueValue);
void checkButton();

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(laserEmitterPin, OUTPUT);
  pinMode(photoresistorPin, INPUT);
  pinMode(flamePin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Internal pull-up resistor for the button

  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);  // 2 seconds delay between readings

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Check button press to toggle the alarm state
  checkButton();

  // Check conditions for blinking red light, triggering the continuous buzzer sound,
  // and monitoring the laser beam
  if (alarmActive) {
    if (humidity > 70 || temperature > 30) {
      blinkRedLight();
      triggerContinuousBuzzer();
    } else {
      // If conditions are no longer met, turn off the buzzer
      digitalWrite(buzzerPin, LOW);
    }

    // Check if the laser beam is blocked
    if (isLaserBlocked()) {
      blinkBlueLight();
      triggerContinuousBuzzer();
    }

    // Check if flame is detected
    if (digitalRead(flamePin) == HIGH) {
      turnOnGreenLight();
    } else {
      // If flame is not detected, turn off the green light
      digitalWrite(greenPin, LOW);
    }

    // Determine the number of hazards present
    int hazardCount = 0;
    if (humidity > 50 || temperature > 35) {
      hazardCount++;
    }
    if (isLaserBlocked()) {
      hazardCount++;
    }
    if (digitalRead(flamePin) == HIGH) {
      hazardCount++;
    }

    // Display RGB colors based on the number of hazards
    switch (hazardCount) {
      case 0:
        displayRGBColors(0, 0, 0); // No hazards, turn off RGB
        break;
      case 1:
        displayRGBColors(255, 0, 0); // One hazard, red color
        break;
      case 2:
        displayRGBColors(0, 255, 0); // Two hazards, green color
        break;
      case 3:
        displayRGBColors(0, 0, 255); // Three hazards, blue color
        break;
    }
  } else {
    // If the alarm is not active, turn off all components
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
}

void blinkRedLight() {
  // Blink the red light by turning it on and off
  for (int i = 0; i < 5; ++i) {
    digitalWrite(redPin, HIGH);
    delay(500);  // Wait for 0.5 seconds
    digitalWrite(redPin, LOW);
    delay(500);  // Wait for 0.5 seconds
  }
}

void blinkBlueLight() {
  // Blink the blue light by turning it on and off
  for (int i = 0; i < 5; ++i) {
    digitalWrite(bluePin, HIGH);
    delay(500);  // Wait for 0.5 seconds
    digitalWrite(bluePin, LOW);
    delay(500);  // Wait for 0.5 seconds
  }
}

void triggerContinuousBuzzer() {
  // Activate the buzzer for a continuous sound only if the alarm is active
  if (alarmActive) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
}

void turnOnGreenLight() {
  // Turn on the green light
  digitalWrite(greenPin, HIGH);
}

bool isLaserBlocked() {
  // Activate the laser emitter
  digitalWrite(laserEmitterPin, HIGH);
  delay(50);  // Allow time for the laser to stabilize

  // Read the value from the photoresistor
  int photoresistorValue = analogRead(photoresistorPin);

  // Deactivate the laser emitter
  digitalWrite(laserEmitterPin, LOW);

  delay(50);  // Allow time for the laser to turn off (adjust this delay as needed)

  // Check if the laser beam is blocked
  return (photoresistorValue > 100);
}

void displayRGBColors(int redValue, int greenValue, int blueValue) {
  // Display RGB colors on the RGB module
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void checkButton() {
  // Read the state of the button
  int reading = digitalRead(buttonPin);

  // Check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // reset the debouncing timer
  }

  // Check if a significant amount of time has passed since the last button state change
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed, update the variable
    if (reading != buttonState) {
      buttonState = reading;

      // If the button is pressed, toggle the alarm state
      if (buttonState == LOW) {
        alarmActive = !alarmActive;
        delay(500);  // Delay to avoid multiple toggles on a single press
      }
    }
  }

  // Save the current button state for comparison in the next iteration
  lastButtonState = reading;
}
