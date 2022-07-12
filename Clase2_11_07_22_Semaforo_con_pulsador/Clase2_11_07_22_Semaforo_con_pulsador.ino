#define ROJO 9 //PINES
#define AMARILLO 10
#define VERDE 11
#define PULSADOR 7

/*Vamos a hacer que cuando led_prendido valga 0 se prenda el rojo
cuando vale 1, el amarillo
cuando vale 2, el verde*/
int led_prendido = 0;//int viene de INTEGER (en ingles, "numero entero")

void setup(){
  pinMode(ROJO, OUTPUT);
  pinMode(AMARILLO, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(PULSADOR, INPUT);
}

void loop(){
  if(digitalRead(PULSADOR) == HIGH){
    led_prendido++;
    if(led_prendido == 3){
      led_prendido = 0;
    }
    delay(150);
  }
  if(led_prendido == 0){
    digitalWrite(ROJO, HIGH);
    digitalWrite(AMARILLO, LOW);
    digitalWrite(VERDE, LOW);
  }
  if(led_prendido == 1){
    digitalWrite(ROJO, LOW);
    digitalWrite(AMARILLO, HIGH);
    digitalWrite(VERDE, LOW);
  }
  if(led_prendido == 2){
    digitalWrite(ROJO, LOW);
    digitalWrite(AMARILLO, LOW);
    digitalWrite(VERDE, HIGH);
  }
}
