#define POTE 0

#define BAUDRATE 9600

void setup(){
  Serial.begin(BAUDRATE);
}

void loop(){
  Serial.print("Valor del pote: ");
  Serial.println(analogRead(POTE)); //Lee el pote y envia su valor al monitor serie
}
