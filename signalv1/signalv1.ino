// Traffic Signal System - Fixed Version
// Lane 1: LED1=Red, LED2=Amber, LED3=Green
// Lane 2: LED4=Red, LED5=Amber, LED6=Green
// Pedestrian Lane1: LED7=Red, LED8=Green
// Pedestrian Lane2: LED9=Red, LED10=Green

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

// System states
enum SystemState { NORMAL_OPERATION, PEDESTRIAN_LANE1, PEDESTRIAN_LANE2 };
SystemState currentState = NORMAL_OPERATION;

unsigned long lastStateChange = 0;
const unsigned long LANE_DURATION = 5000;    // 5 seconds per lane
const unsigned long AMBER_DURATION = 1000;   // 1 second amber
const unsigned long PEDESTRIAN_DURATION = 5000; // 5 seconds pedestrian

bool lane1Active = true; // Start with Lane1 green

void setup() {
  // Initialize all LED pins
  int allLEDs[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10};
  for (int i = 0; i < 10; i++) {
    pinMode(allLEDs[i], OUTPUT);
  }
  
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  
  // Initial LED test
  allLEDsOn();
  delay(1000);
  allLEDsOff();
  
  Serial.begin(9600);
  Serial.println("Traffic System Started - Normal Operation");
}

void loop() {
  unsigned long currentTime = millis();
  
  // Check for button presses (with debouncing)
  if (digitalRead(buttonA) == LOW && currentState == NORMAL_OPERATION) {
    delay(50);
    if (digitalRead(buttonA) == LOW) {
      currentState = PEDESTRIAN_LANE1;
      lastStateChange = currentTime;
      Serial.println("Button A Pressed - Lane1 Pedestrian Activated");
    }
  }
  
  if (digitalRead(buttonB) == LOW && currentState == NORMAL_OPERATION) {
    delay(50);
    if (digitalRead(buttonB) == LOW) {
      currentState = PEDESTRIAN_LANE2;
      lastStateChange = currentTime;
      Serial.println("Button B Pressed - Lane2 Pedestrian Activated");
    }
  }
  
  // State machine
  switch (currentState) {
    case NORMAL_OPERATION:
      handleNormalOperation(currentTime);
      break;
      
    case PEDESTRIAN_LANE1:
      handlePedestrianLane1(currentTime);
      break;
      
    case PEDESTRIAN_LANE2:
      handlePedestrianLane2(currentTime);
      break;
  }
}

void handleNormalOperation(unsigned long currentTime) {
  if (lane1Active) {
    // Lane 1 Green, Lane 2 Red
    setLane1Green();
    setLane2Red();
    setPedestrianSignals(false, true); // Lane1 ped Red, Lane2 ped Green
    
    if (currentTime - lastStateChange >= LANE_DURATION) {
      // Transition to Amber
      setLane1Amber();
      lastStateChange = currentTime;
    }
    
    if (currentTime - lastStateChange >= AMBER_DURATION && 
        currentTime - lastStateChange < AMBER_DURATION + 100) {
      // Switch to Lane 2
      lane1Active = false;
      lastStateChange = currentTime;
      Serial.println("Switching to Lane 2");
    }
  } else {
    // Lane 2 Green, Lane 1 Red  
    setLane2Green();
    setLane1Red();
    setPedestrianSignals(true, false); // Lane1 ped Green, Lane2 ped Red
    
    if (currentTime - lastStateChange >= LANE_DURATION) {
      // Transition to Amber
      setLane2Amber();
      lastStateChange = currentTime;
    }
    
    if (currentTime - lastStateChange >= AMBER_DURATION && 
        currentTime - lastStateChange < AMBER_DURATION + 100) {
      // Switch to Lane 1
      lane1Active = true;
      lastStateChange = currentTime;
      Serial.println("Switching to Lane 1");
    }
  }
}

void handlePedestrianLane1(unsigned long currentTime) {
  // Lane 1 Red, Lane 2 can work
  setLane1Red();
  setLane2Green(); // Lane 2 continues working
  setPedestrianSignals(true, false); // Lane1 ped Green, Lane2 ped Red
  
  if (currentTime - lastStateChange >= PEDESTRIAN_DURATION) {
    // Return to normal operation after 3 second delay
    delay(3000);
    currentState = NORMAL_OPERATION;
    lastStateChange = currentTime;
    Serial.println("Returning to Normal Operation");
  }
}

void handlePedestrianLane2(unsigned long currentTime) {
  // Lane 2 Red, Lane 1 can work
  setLane2Red();
  setLane1Green(); // Lane 1 continues working
  setPedestrianSignals(false, true); // Lane1 ped Red, Lane2 ped Green
  
  if (currentTime - lastStateChange >= PEDESTRIAN_DURATION) {
    // Return to normal operation after 3 second delay
    delay(3000);
    currentState = NORMAL_OPERATION;
    lastStateChange = currentTime;
    Serial.println("Returning to Normal Operation");
  }
}

// LED control functions
void setLane1Red() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

void setLane1Amber() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
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

void setLane2Amber() {
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, LOW);
}

void setLane2Green() {
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, HIGH);
}

void setPedestrianSignals(bool lane1Green, bool lane2Green) {
  digitalWrite(LED7, !lane1Green);  // Red is inverse of Green
  digitalWrite(LED8, lane1Green);
  digitalWrite(LED9, !lane2Green);
  digitalWrite(LED10, lane2Green);
}

void allLEDsOn() {
  for (int i = 2; i <= 13; i++) {
    digitalWrite(i, HIGH);
  }
}

void allLEDsOff() {
  for (int i = 2; i <= 13; i++) {
    digitalWrite(i, LOW);
  }
}