#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int input_A = 2;
int input_B = 3;

int mode_sel = 4;

int A_led = 8;
int B_led = 9;

int Output = 12;

bool A_in = false;
bool B_in = false;

int temp_sel = 0;
int user_sel = 0;


void setup() {
  pinMode(input_A, INPUT);
  pinMode(input_B, INPUT);

  pinMode(A_led, OUTPUT);
  pinMode(B_led, OUTPUT);
  
  pinMode(Output, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Logic Gate        ");
  lcd.setCursor(0,1);
  lcd.print("Kyr-min       ");
}

void AND() {
  if(A_in * B_in) {
    digitalWrite(Output, HIGH);
  } else{
    digitalWrite(Output, LOW);
  }
}

void NAND() {
  if(!(A_in * B_in)){
    digitalWrite(Output, HIGH);
  } else {
    digitalWrite(Output, LOW);
  }
}

void OR() {
  if(A_in + B_in) {
    digitalWrite(Output, HIGH);
  } else{
    digitalWrite(Output, LOW);
  }
}

void NOR(){
  if(!(A_in + B_in)) {
    digitalWrite(Output, HIGH);
  } else{
    digitalWrite(Output, LOW);
  }
}

void XOR() {
  if(!A_in * B_in + A_in * !B_in) {
    digitalWrite(Output, HIGH);
  } else{
    digitalWrite(Output, LOW);
  }
}

void XNOR() {
  if(!(!A_in * B_in + A_in * !B_in)){
    digitalWrite(Output, HIGH);
  } else {
    digitalWrite(Output, LOW);
  }
}

void NOT() {
  digitalWrite(Output, !A_in);
}

void loop() {
  
  A_in = digitalRead(input_A);
  B_in = digitalRead(input_B);
  
  
  
  
  
  temp_sel = digitalRead(mode_sel);
  if(temp_sel == 1){
    user_sel++;
    delay(1000);
    if(user_sel >=8){
      user_sel = 0;
    }
  }
  
  if(A_in == true){
    digitalWrite(A_led, HIGH);
  } else{
    digitalWrite(A_led, LOW);
  }
  
  if(B_in == true) {
    digitalWrite(B_led, HIGH);
  } else{
    digitalWrite(B_led, LOW);
  }
  
  switch(user_sel) {
    case 0:
      digitalWrite(Output, LOW);
      lcd.setCursor(0,0);
      lcd.print("Logic Gate       ");
      lcd.setCursor(0,1);
      lcd.print("Kyr-min        "); 
      break;
    case 1:
      lcd.setCursor(0,0);
      lcd.print("Now        ");
      lcd.setCursor(0,1);
      lcd.print(" - AND         ");
      AND();
      break;

    case 2:
      lcd.setCursor(0,0);
      lcd.print("Now        ");
      lcd.setCursor(0,1);
      lcd.print(" - NAND         ");
      NAND();
      break;
    case 3: 
      lcd.setCursor(0,1);
      lcd.print(" - OR         ");
      OR();
      break;
    case 4:
      lcd.setCursor(0,1);
      lcd.print(" - NOR        ");
      NOR();
      break;
    case 5:
      lcd.setCursor(0,1);
      lcd.print(" - XOR         ");
      XOR();
      break;

    case 6: 
      lcd.setCursor(0,0);
      lcd.print("Now         ");
      lcd.setCursor(0,1);
      lcd.print(" - XNOR         ");
      XNOR();
      break;

    case 7:
      digitalWrite(B_led, LOW);
      lcd.setCursor(0,0);
      lcd.print("Now (use A)        ");
      lcd.setCursor(0,1);
      lcd.print(" - NOT         ");
      NOT();
      break;
  }
}
