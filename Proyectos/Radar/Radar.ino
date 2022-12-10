
#include <Servo.h>

#define SERVO_PIN 8
#define BUZZ_PIN 12
#define ECHO_PIN 3
#define TRIG_PIN 2
#define POT_PIN A0

#define POT_MIN 0
#define POT_MAX 1024

#define ANGLE_MIN 89
#define ANGLE_MAX 150

Servo servo = Servo();

void setup() {
  Serial.begin(9600);
  
  servo.attach(SERVO_PIN);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  servo.write(map(analogRead(POT_PIN), POT_MIN, POT_MAX, ANGLE_MAX, ANGLE_MIN));
  Serial.println(measure());
  delay(100);
}

double measure(){
   digitalWrite(TRIG_PIN, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN, LOW);
   long duration = pulseIn(ECHO_PIN, HIGH);
   return duration * (0.034 / 2);
}
