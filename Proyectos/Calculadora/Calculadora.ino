#include <Keypad.h>
#include <LiquidCrystal.h>
#include "NumBuilder.hpp"

#define ROWS 4                                                                //Numero de filas del teclado matricial
#define COLS 4                                                                //Numero de columnas del teclado matricial

/*CONFIGURACION DEL TECLADO*/
char keys[ROWS][COLS] = {                                                     //Mapeo de teclas del teclado matricial
  {'1','2','3','+'},
  {'4','5','6','-' },
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3};                                        //Pines de filas (para escritura)
byte colPins[COLS] = {9, 8, 7, 6};                                            //Pines de columnas (para lectura)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );     //Creacion de objeto teclado

/*CONFIGURACION DEL DISPLAY*/
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;                   //Definicion de pines del display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                                    //Creacion de objeto display

/*DECLARACION DE FUNCIONES*/
void keyHandler(char key);                                                    //Decide que hacer cuando se presiona una tecla
void setOperation(char key);                                                  //Decide que hacer cuando se presiona una tecla de operacion
void digit(char key);                                                         //Decide que hacer cuando se presiona una tecla numerica
void calcClear();                                                             //Reinicia la calculadora cuando se presiona la tecla C (clear)
void result();                                                                //Muestra el resultado
void syntaxError();                                                           //Muestra que hubo un error de sintaxis
void mathError();                                                             //Muestra que hubo un error matematico (division por cero)

/*Variables de estado de la calculadora*/
char operation = 0;                                                           //Aqui guardaremos la operacion que se va a realizar
NumBuilder* num1 = new NumBuilder();                                          //Aqui guardaremos los digitos de los operandos mientras se van ingresando
NumBuilder* num2 = new NumBuilder();

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Calculadora");
  lcd.setCursor(0, 1);
  lcd.print("Chalin Tech");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop(){
  char key = 0;
  while((key = keypad.getKey()) == NO_KEY);
  keyHandler(key);
}

void keyHandler(char key){
  Serial.println(key);
  
  switch(key){
    case 'C':
      calcClear();
      break;
    case '=':
      result();
      break;
    case '+':
    case '*':
    case '/':
      setOperation(key);
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      digit(key);
      break;
    case '-':
      if (operation == 0 && num1->isEmpty()){
        digit(key);
      }
      else if (operation != 0 && num2->isEmpty()){
        digit(key);
      }
      else{
        setOperation(key);
      }
      break;
    default: //No se deberia caer aqui nunca
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Error");
      delay(5000);
      calcClear();
      break;
  }
}

void setOperation(char key){
  if(operation != 0 || num1->isEmpty()){
    syntaxError();
    return;
  }
  operation = key;
  lcd.print(' ');
  lcd.print(key);
  lcd.setCursor(0, 1);
}

void digit(char key){
  int ret;
  if (operation == 0){
    ret = num1->addDigit(key);
  }
  else{
    ret = num2->addDigit(key);
  }
  if(ret == -2){
    return;
  }
  else if (ret == -1){
    syntaxError();
  }
  else{
    lcd.print(key);
  }
}

void calcClear(){
  lcd.clear();
  lcd.setCursor(0, 0);
  num1->reset();
  num2->reset();
  operation = 0;
}

void result(){
  if (num1->isEmpty() || num2->isEmpty() || operation == 0){
    syntaxError();
    return;
  }
  double res;
  long n1 = num1->getNumber();
  long n2 = num2->getNumber();
  switch (operation){
    case '+':
      res = n1 + n2;
      break;
    case '-':
      res = n1 - n2;
      break;
    case '*':
      res = n1 * n2;
      break;
    case '/':
      if (n2 == 0){
        mathError();
        return;
      }
      res = (double) n1 / (double) n2;
      break;
  }
  
  Serial.print(n1);
  Serial.print(" ");
  Serial.print(operation);
  Serial.print(" ");
  Serial.print(n2);
  Serial.print(" = ");
  Serial.println(res);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(res);
  while(keypad.getKey() != 'C');
  calcClear();
}

void syntaxError() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error: Sintaxis");
  lcd.setCursor(0, 1);
  lcd.print("incorrecta.");
  while(keypad.getKey() != 'C');
  calcClear();

  Serial.println("Error: Sintaxis incorrecta");
}

void mathError() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error: Division");
  lcd.setCursor(0, 1);
  lcd.print("por cero.");
  while(keypad.getKey() != 'C');
  calcClear();

  Serial.println("Error: Division por cero");
}
