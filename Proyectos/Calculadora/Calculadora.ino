#include <Keypad.h>
#include <LiquidCrystal.h>

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
void operation(char key);                                                     //Decide que hacer cuando se presiona una tecla de operacion
void digit(char key);                                                         //Decide que hacer cuando se presiona una tecla numerica
void calcClear();                                                             //Reinicia la calculadora cuando se presiona la tecla C (clear)

/*Variables de estado de la calculadora*/
char operation = 0;                                                           //Aqui guardaremos la operacion que se va a realizar
char firstOperand[MAX_DIGITS] = {0};                                          //Aqui guardaremos los digitos de los operandos mientras se van ingresando
char secondOperand[MAX_DIGITS] = {0};
long firstOperandNumber = 0, secondOperandNumber = 0;                         //Aqui guardaremos los operandos una vez

void setup(){
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

void loop(){
  char key = 0;
  while((key = keypad.getKey()) == NO_KEY);
  keyHandler(key);
}

void keyHandler(char key){
  switch(key){
    case 'C':
      calcClear();
      break;
    case '+':
    case '-':
    case '*':
    case '/':
      operation(key);
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
    default:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Error");
      delay(5000);
      calcClear();
      break;
  }
}

void operation(char key){
  
}

void digit(char key){
  
}

void calcClear(){
  
}
