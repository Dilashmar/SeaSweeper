#define BLUE 3
#define GREEN 5
#define RED 6

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT); // Corrected to OUTPUT
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW); // Added missing semicolon
}


int redValue;
int greenValue;
int blueValue;

void loop() {
  // Smoothly increase red, while decreasing blue
  for (redValue = 0; redValue <= 255; redValue += 5) {
    blueValue = 255 - redValue;
    analogWrite(RED, redValue);
    analogWrite(BLUE, blueValue);
    delay(30);
  }

  // Smoothly increase green, while decreasing red
  for (greenValue = 0; greenValue <= 255; greenValue += 5) {
    redValue = 255 - greenValue;
    analogWrite(GREEN, greenValue);
    analogWrite(RED, redValue);
    delay(30);
  }

  // Smoothly increase blue, while decreasing green
  for (blueValue = 0; blueValue <= 255; blueValue += 5) {
    greenValue = 255 - blueValue;
    analogWrite(BLUE, blueValue);
    analogWrite(GREEN, greenValue);
    delay(30);
  }
}

