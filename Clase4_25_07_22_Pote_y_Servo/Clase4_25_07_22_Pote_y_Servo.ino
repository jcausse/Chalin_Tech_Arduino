#include <Servo.h>

#define POTE 0
#define SERVO 9
#define BAUDRATE 9600

Servo mi_servo;

void setup(){
  Serial.begin(BAUDRATE);
  mi_servo.attach(SERVO);
}

void loop(){
  int valor_pote = analogRead(POTE); //Leemos el pote
  int angulo = map(valor_pote, 0, 1023, 0, 180); //Convertimos con map los valores del pote de 0 a 1023 en los angulos
  //posibles que van de 0 a 180
  
  Serial.print("Valor del pote: "); //Usamos el monitor serie para ver la informacion
  Serial.print(valor_pote);
  Serial.print(" Angulo del servo: ");
  Serial.println(angulo);
  
  mi_servo.write(angulo); //Hacemos que el servo se coloque en el angulo indicado por el pote
}
