/*  USO DE LA CAJA FUERTE:
 *  1. Ingrese una contraseña de entre 4 y 16 digitos (numeros, * y #)
 *  2. Presione A para guardar la contraseña
 *  3. Cierre la puerta y presione A para bloquear la caja
 *  4. Cuando quiera abrirla, ingrese su contraseña y luego presione A
 *  5. Al dejar de utilizarla, retire sus pertenencias y presione D para restablecer la contraseña
 */

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define ROWS 4                                                                //Numero de filas del teclado matricial
#define COLS 4                                                                //Numero de columnas del teclado matricial

#define MIN 4
#define MAX 16

#define OPEN() servo.write(180);
#define CLOSE() servo.write(0);
#define SERVO_PIN A0

char keys[ROWS][COLS] = {                                                     //Mapeo de teclas del teclado matricial
  {'1','2','3','A'},
  {'4','5','6','B' },
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {0, 1, 2, 3};                                            //Pines de filas (para escritura)
byte colPins[COLS] = {4, 5, 6, 7};                                            //Pines de columnas (para lectura)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );     //Creacion de objeto teclado

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;                 //Definicion de pines del display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                                    //Creacion de objeto display

Servo servo = Servo();

bool pwd_set = false, locked = false, visible = false;
char pwd[MAX + 1];
char input_buffer[MAX + 1];
int index, pwd_len;
char* last_msg;
int last_col, last_row;
bool last_show_alert;

void safe_reset();
void input(char input_char);
void enter_handler();
void show_input();
void show_msg(char* msg, int col, int row, bool remember, bool show_alert);
bool check_pwd();

static int my_strlen(char* str);

void setup(){
  servo.attach(SERVO_PIN);
  OPEN();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Caja Fuerte");
  lcd.setCursor(0, 1);
  lcd.print("Chalin Tech");
  delay(2000);
  safe_reset();
}

void loop(){
  char key = 0;
  while((key = keypad.getKey()) == NO_KEY);
  switch(key){
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
    case '*':
    case '#': 
      input(key);
      break;
    case 'A':
      enter_handler();
      break;
    case 'B':
      visible = !visible;
      show_msg(last_msg, last_col, last_row, false, last_show_alert);
      show_input();
      break;
    case 'C':
      index = 0;
      lcd.clear();
      show_msg(last_msg, last_col, last_row, false, last_show_alert);
      break;
    case 'D':
      if (!locked){
        lcd.clear();
        show_msg("Reiniciando...", 0, 0, false, false);
        delay(2000);
        safe_reset();
      }
      else{
        lcd.clear();
        show_msg("Desbloquear para", 0, 0, false, false);
        show_msg("reiniciar", 0, 1, false, false);
        delay(2000);
        lcd.clear();
        show_msg(last_msg, last_col, last_row, false, last_show_alert);
        show_input();
      }
      break;
    default: //No se deberia caer aqui nunca
      lcd.clear();
      show_msg("Error", 0, 0, false, false);
      delay(5000);
      safe_reset();
      break;
  }
}

void safe_reset(){
  lcd.clear();
  lcd.setCursor(0, 0);
  pwd_set = false;
  locked = false;
  visible = false;
  index = 0;
  unsigned int i;
  for (i = 0; i <= MAX; i++){
    pwd[i] = 0;
    input_buffer[i] = 0;
  }
  show_msg("Definir pin:", 0, 0, true, true);
}

void input(char input_char){
  if (index >= MAX){
    lcd.clear();
    show_msg("Maximo ", 0, 0, false, false);
    lcd.print(MAX);
    show_msg("caracteres!", 0, 1, false, false);
    delay(2000);
    lcd.clear();
    show_msg(last_msg, last_col, last_row, false, last_show_alert);
    show_input();
    return;
  }
  input_buffer[index++] = input_char;
  show_input();
}

void enter_handler(){
  if (!pwd_set){
    if (index < 4){
      lcd.clear();
      show_msg("Minimo ", 0, 0, false, false);
      lcd.print(MIN);
      show_msg("caracteres!", 0, 1, false, false);
      delay(2000);
      lcd.clear();
      show_msg(last_msg, last_col, last_row, false, last_show_alert);
      show_input();
      return;
    }
    unsigned int i;
    pwd_len = index;
    for (i = 0; i < index; i++){
      pwd[i] = input_buffer[i];
    }
    lcd.clear();
    show_msg("Pin definido", 0, 0, true, false);
    show_msg("A -> Cerrar", 0, 1, true, false);
    pwd_set = true;
  }
  else if (locked){
    lcd.clear();
    if (check_pwd()){
      OPEN();
      locked = false;
      show_msg("A -> Cerrar", 0, 0, true, false);
      show_msg("D -> Reiniciar", 0, 1, true, false);
    }
    else{
      show_msg("Pin incorrecto", 0, 0, false, false);
      delay(2000);
      lcd.clear();
      show_msg(last_msg, last_col, last_row, false, last_show_alert);
    }
  }
  else {
    CLOSE();
    locked = true;
    lcd.clear();
    show_msg("Ingresar pin:", 0, 0, true, true);
  }
  index = 0;
}

void show_input(){
  if (locked || !pwd_set){
    lcd.setCursor(0, 1);
    unsigned int i;
    if (visible){
      for (i = 0; i < index; i++){
        lcd.print(input_buffer[i]);
      }
    }
    else{
      for (i = 0; i < index; i++){
        lcd.print("-");
      }  
    }
  }
}

void show_msg(char* msg, int col, int row, bool remember, bool show_alert){
  lcd.setCursor(col, row);
  if(remember){
    last_msg = msg;
    last_col = col;
    last_row = row;
    last_show_alert = show_alert;
  }
  lcd.print(msg);
  if (show_alert && row == 0 && my_strlen(msg) < 15){
    lcd.setCursor(15, 0);
    if (visible){
      lcd.print("!");
    }
    else{
      lcd.print("-");
    }
  }
}

bool check_pwd(){
  if (pwd_len != index){
    return false;
  }
  unsigned int i;
  for (i = 0; i < pwd_len; i++){
    if (pwd[i] != input_buffer[i]){
      return false;
    }
  }
  return true;
}

static int my_strlen(char* str){
  int i = 0;
  char c;
  while ((c = str[i]) != '\0'){
    i++;
  }
  return i;
}
