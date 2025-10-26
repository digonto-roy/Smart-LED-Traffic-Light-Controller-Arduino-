// --- PIN DEFINITIONS ---
const int RED_PIN = 13;
const int YELLOW_PIN = 12;
const int GREEN_PIN = 11;
const int BUTTON_PIN = 2; // Pedestrian Request Button

// --- TIMING CONSTANTS (in milliseconds) ---
const int GREEN_TIME = 5000;  // 5 seconds
const int YELLOW_TIME = 2000; // 2 seconds
const int RED_TIME = 7000;    // 7 seconds
const int CROSS_TIME = 5000;  // 5 seconds for pedestrian crossing

void setup() {
  // Initialize LED pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  // Initialize button pin as input (using the pull-down resistor in the circuit)
  pinMode(BUTTON_PIN, INPUT); 

  Serial.begin(9600);
  Serial.println("Traffic Light Controller Initialized.");
}

void loop() {
  // Start with Green
  changeLights(GREEN_PIN, GREEN_TIME, "GREEN");

  // Green to Red Transition (Yellow phase)
  changeLights(YELLOW_PIN, YELLOW_TIME, "YELLOW");

  // Red
  changeLights(RED_PIN, RED_TIME, "RED");

  // Check for pedestrian request while RED is ON
  if (digitalRead(BUTTON_PIN) == HIGH) {
    pedestrianCrossing();
  }

  // Red to Green Transition (Red + Yellow phase)
  digitalWrite(RED_PIN, HIGH);
  changeLights(YELLOW_PIN, 1000, "RED-YELLOW"); // Both on for 1 second
}

// Helper function to handle light changes and timing
void changeLights(int lightPin, int duration, const char* label) {
  // Turn off all lights first
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);

  // Turn on the specified light
  digitalWrite(lightPin, HIGH);
  Serial.print("Current State: ");
  Serial.println(label);
  
  delay(duration);
}

// Function to handle the pedestrian crossing sequence
void pedestrianCrossing() {
  Serial.println("--- PEDESTRIAN REQUEST RECEIVED ---");

  // Ensure all traffic lights are RED for crossing time
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  Serial.println("Traffic Lights: ALL RED (Pedestrian Walk)");
  
  delay(CROSS_TIME);
  
  Serial.println("Pedestrian Walk Time Over. Resuming cycle.");
}