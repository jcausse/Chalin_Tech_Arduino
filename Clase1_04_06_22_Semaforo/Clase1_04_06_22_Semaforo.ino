#define ROJO 9 //El LED rojo va conectado al pin 9
#define AMARILLO 10 //El LED amarillo va conectado al pin 10
#define VERDE 11 //El LED verde va conectado al pin 11

#define TIEMPO_ROJO_Y_VERDE 2000 //Tiempo que dura una luz roja o verde
#define TIEMPO_AMARILLO 500 //Tiempo que dura una luz amarilla

void setup() {  //El código del setup se ejecuta una sola vez
  pinMode(ROJO, OUTPUT); //Definimos que los pines a los que se conectan los LEDs son salidas
  pinMode(AMARILLO, OUTPUT);
  pinMode(VERDE, OUTPUT);
}

void loop() { //El código del loop se ejecuta una vez tras otra, infinitamente
  digitalWrite(ROJO, HIGH); //Encendemos la luz roja
  delay(TIEMPO_ROJO_Y_VERDE); //Esperamos
  digitalWrite(ROJO, LOW);  //Apagamos la roja
  digitalWrite(AMARILLO, HIGH); //Encendemos la amarilla
  delay(TIEMPO_AMARILLO); //Esperamos
  digitalWrite(AMARILLO, LOW);  //Apagamos la amarilla
  digitalWrite(VERDE, HIGH); //Encendemos la verde
  delay(TIEMPO_ROJO_Y_VERDE); //Esperamos
  digitalWrite(VERDE, LOW); //Apagamos la verde. Inmediatamente después se vuelve a empezar desde el principio del loop, haciendo que el semáforo funcione "infinitamente"
  digitalWrite(AMARILLO, HIGH);
  delay(TIEMPO_AMARILLO);
  digitalWrite(AMARILLO, LOW);
}
