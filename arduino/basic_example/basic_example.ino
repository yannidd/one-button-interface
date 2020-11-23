#include <AceButton.h>

using namespace ace_button;

const int LED_PIN = LED_BUILTIN;
const int PB_OUT_PIN = 2;
const int PS_HOLD_PIN = 3;

AceButton button(PB_OUT_PIN);

void buttonEventHandler(AceButton*, uint8_t, uint8_t);

void setup() {
  // Initialise I/O.  
  pinMode(LED_PIN, OUTPUT);
  pinMode(PB_OUT_PIN, INPUT_PULLUP);
  pinMode(PS_HOLD_PIN, OUTPUT);

  // Set the power supply pin high to keep the device on.
  digitalWrite(PS_HOLD_PIN, HIGH);

  // Initialise serial communication. 
  Serial.begin(9600);
  Serial.println("Click: power on.");

  // Setup button functionality.
  ButtonConfig* buttonConfig = button.getButtonConfig();
  buttonConfig->setEventHandler(buttonEventHandler);
  buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureSuppressAll);  
  buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
}

void loop() {
  // Should be called every 20ms or faster for the default debouncing time of ~50ms.
  button.check();
  delay(10);
}

void buttonClicked() {
  Serial.println("Click: LED on.");
  digitalWrite(LED_PIN, HIGH);
}

void buttonDoubleClicked() {
  Serial.println("Double click: LED off.");
  digitalWrite(LED_PIN, LOW);
}

void buttonLongPressed() {
  Serial.println("Long press: power off.");
  // Set the power supply pin low to shut the device down.
  digitalWrite(PS_HOLD_PIN, HIGH);
}

// The event handler for the button.
void buttonEventHandler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {    
    case AceButton::kEventLongPressed:      
      buttonLongPressed();
      break;
    case AceButton::kEventDoubleClicked: 
      buttonDoubleClicked();
      break;    
    case AceButton::kEventClicked:
    case AceButton::kEventReleased:
      buttonClicked();
      break;
  }
}
