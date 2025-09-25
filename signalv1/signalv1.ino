// Traffic Light System - Minimal & Clean
// Lane 1: LED1=Red, LED2=Amber, LED3=Green
// Lane 2: LED4=Red, LED5=Amber, LED6=Green
// Pedestrian: LED7/8=Lane1, LED9/10=Lane2

// Lane 1 Signals
const int LED1 = 13; // Red
const int LED2 = 12; // Amber  
const int LED3 = 9;  // Green

// Lane 2 Signals
const int LED4 = 8;  // Red
const int LED5 = 7;  // Amber
const int LED6 = 6;  // Green

// Pedestrian Signals
const int LED7 = 5;  // Lane1 Red
const int LED8 = 4;  // Lane1 Green
const int LED9 = 3;  // Lane2 Red  
const int LED10 = 2; // Lane2 Green

// Buttons
const int buttonA = A0; // Lane1 Pedestrian
const int buttonB = A1; // Lane2 Pedestrian

bool lane1Active = true;
unsigned long previousMillis = 0;
const long interval = 5000; // 5 seconds

void setup() {
  // Initialize all pins
  int leds[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10};
  for (int i = 0; i < 10; i++) pinMode(leds[i], OUTPUT);
  
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  
  // Initial LED test
  for (int i = 0; i < 10; i++) digitalWrite(leds[i], HIGH);
  delay(1000);
  for (int i = 0; i < 10; i++) digitalWrite(leds[i], LOW);
  
  // Start with Lane 1 Green, Lane 2 Red
  setLane1Green();
  setLane2Red();
  setPedestrianSignals();
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Check for pedestrian button presses
  if (digitalRead(buttonA) == LOW) {
    handlePedestrianLane1();
  }
  if (digitalRead(buttonB) == LOW) {
    handlePedestrianLane2();
  }
  
  // Normal traffic light sequence every 5 seconds
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    if (lane1Active) {
      // Lane 1: Green → Amber → Red
      digitalWrite(LED3, LOW);  // Green off
      delay(1000);
      digitalWrite(LED2, HIGH); // Amber on
      delay(1000);
      digitalWrite(LED2, LOW);  // Amber off
      digitalWrite(LED1, HIGH); // Red on
      
      // Lane 2: Red → Amber → Green
      delay(1000);
      digitalWrite(LED5, HIGH); // Amber on
      delay(1000);
      digitalWrite(LED5, LOW);  // Amber off
      digitalWrite(LED4, LOW);  // Red off
      digitalWrite(LED6, HIGH); // Green on
      
      lane1Active = false;
    } else {
      // Lane 2: Green → Amber → Red
      digitalWrite(LED6, LOW);  // Green off
      delay(1000);
      digitalWrite(LED5, HIGH); // Amber on
      delay(1000);
      digitalWrite(LED5, LOW);  // Amber off
      digitalWrite(LED4, HIGH); // Red on
      
      // Lane 1: Red → Amber → Green
      delay(1000);
      digitalWrite(LED2, HIGH); // Amber on
      delay(1000);
      digitalWrite(LED2, LOW);  // Amber off
      digitalWrite(LED1, LOW);  // Red off
      digitalWrite(LED3, HIGH); // Green on
      
      lane1Active = true;
    }
    
    setPedestrianSignals();
  }
}

void handlePedestrianLane1() {
  // Stop Lane 1, keep Lane 2 working
  setLane1Red();
  setPedestrianLane1Green();
  delay(5000); // Pedestrian crossing time
  setPedestrianSignals();
  delay(3000); // 3 second delay before returning
}

void handlePedestrianLane2() {
  // Stop Lane 2, keep Lane 1 working
  setLane2Red();
  setPedestrianLane2Green();
  delay(5000); // Pedestrian crossing time
  setPedestrianSignals();
  delay(3000); // 3 second delay before returning
}

void setLane1Red() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

void setLane1Green() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
}

void setLane2Red() {
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
}

void setLane2Green() {
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, HIGH);
}

void setPedestrianSignals() {
  // Set pedestrian signals based on current lane activity
  if (lane1Active) {
    // Lane 1 Green: Lane1 pedestrian Red, Lane2 pedestrian Green
    digitalWrite(LED7, HIGH);  // Lane1 Red
    digitalWrite(LED8, LOW);   // Lane1 Green off
    digitalWrite(LED9, LOW);   // Lane2 Red off
    digitalWrite(LED10, HIGH); // Lane2 Green
  } else {
    // Lane 2 Green: Lane1 pedestrian Green, Lane2 pedestrian Red
    digitalWrite(LED7, LOW);   // Lane1 Red off
    digitalWrite(LED8, HIGH);  // Lane1 Green
    digitalWrite(LED9, HIGH);  // Lane2 Red
    digitalWrite(LED10, LOW);  // Lane2 Green off
  }
}

void setPedestrianLane1Green() {
  digitalWrite(LED7, LOW);   // Lane1 Red off
  digitalWrite(LED8, HIGH);  // Lane1 Green on
}

void setPedestrianLane2Green() {
  digitalWrite(LED9, LOW);   // Lane2 Red off
  digitalWrite(LED10, HIGH); // Lane2 Green on
}