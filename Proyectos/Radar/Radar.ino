#include <Servo.h>

#define SERVO_PIN 4
#define POT_PIN A0
#define POT_MIN 0
#define POT_MAX 1024
#define ANGLE_MIN 88
#define ANGLE_MAX 142

#define BUZZ_PIN 12
#define ECHO_PIN 3
#define TRIG_PIN 2

#define LED1 11
#define LED2 10
#define LED3 9
#define LED4 8
#define LED5 7

int leds[5] = {LED1, LED2, LED3, LED4, LED5};

Servo servo = Servo();

int beep_delay;
long last_beep_timestamp;

void setup(){
  servo.attach(SERVO_PIN);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  greeting();
  
  pinMode(BUZZ_PIN, OUTPUT);
  last_beep_timestamp = millis();
}

void loop(){
  servo.write(map(analogRead(POT_PIN), POT_MIN, POT_MAX, ANGLE_MAX, ANGLE_MIN));
  double distance = measure();
  beep_delay = 4 * distance;
  if (distance < 90.0 && distance > 7.0){
    beep();
    if (distance < 24.0){
      led_ctrl(5);
    }
    else if (distance < 41.0){
      led_ctrl(4);
    }
    else if (distance < 58.0){
      led_ctrl(3);
    }
    else if (distance < 75.0){
      led_ctrl(2);
    }
    else{
      led_ctrl(1);
    }
  }
  else{
    led_ctrl(0);
  }
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

void beep(){
  if(millis() - last_beep_timestamp < beep_delay){
    return;
  }
  last_beep_timestamp = millis();
  digitalWrite(BUZZ_PIN, HIGH);
  delay(15);
  digitalWrite(BUZZ_PIN, LOW);
}

void greeting(){
  unsigned int i, j;
  for (j = 0; j < 3; j++){
    for (i = 0; i < 5; i++){
      digitalWrite(leds[i], HIGH);
      delay(90);
      digitalWrite(leds[i], LOW);
    }
  }
}

void led_ctrl(int n){
  unsigned int i;
  for (i = 0; i < n; i++){
    digitalWrite(leds[i], HIGH);
  }
  for (i = n; i < 5; i++){
    digitalWrite(leds[i], LOW);
  }
}
