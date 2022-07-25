#define LED_G 2//Pin 1 del display
#define LED_F 3//2
#define LED_A 4//4
#define LED_B 5//5
#define LED_E 6//6
#define LED_D 7//7
#define LED_C 8//9
#define LED_DP 9//10

#define LED_VERDE 11

#define POTE 0

int valor;
int numero;
int intensidad;

void setup(){
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_D, OUTPUT);
  pinMode(LED_E, OUTPUT);
  pinMode(LED_F, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_DP, OUTPUT);
  digitalWrite(LED_DP, HIGH);
  Serial.begin(9600); //LO VEMOS LA CLASE QUE VIENE
}

void loop(){
  valor = analogRead(POTE);
  numero = map(valor, 0, 1023, 0, 9);
  mostrarNumero(numero);
  intensidad = map(valor, 0, 1023, 0, 255);
  analogWrite(LED_VERDE, intensidad);
}

void mostrarNumero(int n){
  if(n < 0 || n > 9){
    return;
  }
  Serial.print("NUMERO: "); //LO VEMOS LA CLASE QUE VIENE
  Serial.println(n); //LO VEMOS LA CLASE QUE VIENE
  digitalWrite(LED_A, HIGH);
  digitalWrite(LED_B, HIGH); 
  digitalWrite(LED_C, HIGH); 
  digitalWrite(LED_D, HIGH); 
  digitalWrite(LED_E, HIGH); 
  digitalWrite(LED_F, HIGH); 
  digitalWrite(LED_G, HIGH);
  switch(n){
   case 0:
     digitalWrite(LED_A, LOW);
     digitalWrite(LED_B, LOW);
     digitalWrite(LED_C, LOW);
     digitalWrite(LED_D, LOW);
     digitalWrite(LED_E, LOW);
     digitalWrite(LED_F, LOW);
     break;
   case 1:
     digitalWrite(LED_B, LOW);
     digitalWrite(LED_C, LOW);
     break;
   case 2:
     digitalWrite(LED_A, LOW);
     digitalWrite(LED_B, LOW);
     digitalWrite(LED_D, LOW);
     digitalWrite(LED_E, LOW);
     digitalWrite(LED_G, LOW);
     break;
   case 3:
     digitalWrite(LED_A, LOW);
     digitalWrite(LED_B, LOW);
     digitalWrite(LED_C, LOW);
     digitalWrite(LED_D, LOW);
     digitalWrite(LED_G, LOW);
     break;
   case 4:
     digitalWrite(LED_B, LOW);
     digitalWrite(LED_C, LOW);;
     digitalWrite(LED_F, LOW);
     digitalWrite(LED_G, LOW);
     break;
   case 5:
     digitalWrite(LED_A, LOW);
     digitalWrite(LED_C, LOW);
     digitalWrite(LED_D, LOW);
     digitalWrite(LED_F, LOW);
     digitalWrite(LED_G, LOW);
     break;
   case 6:
     digitalWrite(LED_A, LOW);
     digitalWrite(LED_C, LOW);
     digitalWrite(LED_D, LOW);
     digitalWrite(LED_E, LOW);
     digitalWrite(LED_F, LOW);
     digitalWrite(LED_G, LOW);
     break;
   case 7:
     digitalWrite(LED_A, LOW);
     digitalWrite(LED_B, LOW);
     digitalWrite(LED_C, LOW);
     break;
   case 8:
     digitalWrite(LED_A, LOW);
     digitalWrite(LED_B, LOW);
     digitalWrite(LED_C, LOW);
     digitalWrite(LED_D, LOW);
     digitalWrite(LED_E, LOW);
     digitalWrite(LED_F, LOW);
     digitalWrite(LED_G, LOW);
     break;
   case 9:
     digitalWrite(LED_A, LOW);
     digitalWrite(LED_B, LOW);
     digitalWrite(LED_C, LOW);
     digitalWrite(LED_F, LOW);
     digitalWrite(LED_G, LOW);
     break;
  } 
}
