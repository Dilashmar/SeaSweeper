

#include <Servo.h>
#include <DHT_Async.h>
#include <hcsr04.h>
#include <Arduino.h>

// Servo
Servo myservo;
const int servoPin = 9;

// DHT
#define DHT_SENSOR_TYPE DHT_TYPE_11 // Choose your sensor type
const int DHT_SENSOR_PIN = 2;
DHT_Async dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

// RGB LED
#define RED 6
#define GREEN 5
#define BLUE 3

// Ultrasonic Sensor
#define TRIG_PIN 12
#define ECHO_PIN 11
HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);

void setup() {
  // Servo setup
  myservo.attach(servoPin);
  
  // DHT setup
  Serial.begin(115200);

  // RGB LED setup
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  // Ultrasonic Sensor setup
  Serial.begin(9600);
}

void loop() {
  // Servo loop modified for faster movement
  for (int pos = 0; pos <= 180; pos += 30) { // Goes from 0 degrees to 180 degrees
    myservo.write(pos);                      // Tell servo to go to position in variable 'pos'
    delay(30);                               // Waits 30ms for the servo to reach the position
  }
  for (int pos = 180; pos >= 0; pos -= 30) { // Goes from 180 degrees back to 0 degrees
    myservo.write(pos);                      // Tell servo to go to position in variable 'pos'
    delay(30);                               // Waits 30ms for the servo to reach the position
  }

  // DHT loop
  float temperature;
  float humidity;
  if (measure_environment(&temperature, &humidity)) {
      Serial.print("T = ");
      Serial.print(temperature, 1);
      Serial.print(" deg. C, H = ");
      Serial.print(humidity, 1);
      Serial.println("%");
  }

  // RGB loop (simplified example, you might need to adjust this part)
  analogWrite(RED, 255);
  delay(500);
  analogWrite(GREEN, 255);
  delay(500);
  analogWrite(BLUE, 255);
  delay(500);

  // Ultrasonic Sensor loop
  Serial.println(hcsr04.distanceInMillimeters());
  delay(3050); // Adjust as needed for your project
}

bool measure_environment(float *temperature, float *humidity) {
  static unsigned long measurement_timestamp = millis();
  if (millis() - measurement_timestamp > 4000ul) {
      if (dht_sensor.measure(temperature, humidity)) {
          measurement_timestamp = millis();
          return true;
      }
  }
  return false;
}
