// Define pins for components
#define LDR_PIN A0          // Photoresistor (LDR) pin
#define TEMP_SENSOR_PIN A1  // TMP36 temperature sensor pin
#define BUTTON_PIN 7        // Pushbutton pin for door lock
#define LIGHT_PIN 3         // LED to simulate light control
#define FAN_PIN 9           // DC Motor pin to simulate fan control
#define DOOR_LOCK_PIN 4     // LED to simulate door lock status

// Threshold values
int lightThreshold = 500;   // LDR threshold for light control
int tempThreshold = 25;     // Temperature threshold for fan control (in Celsius)

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set pins as outputs/inputs
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(DOOR_LOCK_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  // Turn off outputs initially
  digitalWrite(LIGHT_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(DOOR_LOCK_PIN, LOW);
}

void loop() {
  // AUTOMATIC LIGHTING CONTROL
  int lightValue = analogRead(LDR_PIN); // Read the LDR value
  Serial.print("Light Level: ");
  Serial.println(lightValue);

  if (lightValue < lightThreshold) {  // If it's dark
    digitalWrite(LIGHT_PIN, HIGH);    // Turn on the light (LED)
    Serial.println("Light ON");
  } else {
    digitalWrite(LIGHT_PIN, LOW);     // Turn off the light
    Serial.println("Light OFF");
  }

  // TEMPERATURE MONITORING AND FAN CONTROL
  int tempValue = analogRead(TEMP_SENSOR_PIN);  // Read TMP36 value
  float voltage = tempValue * (5.0 / 1023.0);   // Convert to voltage
  float temperatureC = (voltage - 0.5) * 100;   // Convert to Celsius
  
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println("°C");

  if (temperatureC > tempThreshold) {   // If temperature is higher than threshold
    digitalWrite(FAN_PIN, HIGH);        // Turn on the fan (motor)
    Serial.println("Fan ON");
  } else {
    digitalWrite(FAN_PIN, LOW);         // Turn off the fan
    Serial.println("Fan OFF");
  }

  // DOOR LOCK SYSTEM
  int buttonState = digitalRead(BUTTON_PIN);  // Read the pushbutton state
  if (buttonState == HIGH) {   // If button is pressed
    digitalWrite(DOOR_LOCK_PIN, HIGH);  // Unlock the door (turn on LED)
    Serial.println("Door Unlocked");
  } else {
    digitalWrite(DOOR_LOCK_PIN, LOW);   // Lock the door
    Serial.println("Door Locked");
  }

  delay(1000);  // Delay for 1 second before next reading
}
