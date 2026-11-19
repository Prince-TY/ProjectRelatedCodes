
const int buttonPin = 21;
const int ledPin = 23;

int ledState = LOW;
int buttonState;
int lastButtonState = HIGH;
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, ledState);
}

void loop() {
  buttonState = digitalRead(buttonPin);


  if (buttonState == LOW && lastButtonState == HIGH) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    delay(50); 
  }

  lastButtonState = buttonState;
}
