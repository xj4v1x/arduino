#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
byte A_Button = 5;
byte B_Button = 6;
byte lcd_backlight = 2;
bool light = true;
byte menuIndex = 0;
bool menuCursor = 0;
const int menuMax = 4;
const char menuItems[menuMax][15] = {
    "Set Date/Time",
    "Set Alarm",
    "Config",
    "Exit"
  };

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(lcd_backlight, OUTPUT);
  pinMode(A_Button, INPUT);
  pinMode(B_Button, INPUT);
  digitalWrite (lcd_backlight, HIGH);
  lcd.setCursor(1,0);
  lcd.print("ALARM");
  lcd.setCursor(10,1);
  lcd.print("CLOCK");
  delay(200);
  light = false;
  screen();
}

void loop() {
  checkButtons();
}

void screen(){
 lights();
 menu_draw();
}

void lights(){
 if (light == true){
  digitalWrite (lcd_backlight, HIGH);
 } else {
  digitalWrite (lcd_backlight, LOW);
 } 
}

void menu_draw(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print(menuItems[menuIndex]);
  lcd.setCursor(2,1);
  lcd.print(menuItems[menuIndex+1]);
  lcd.setCursor(0,menuCursor);
  lcd.print("-");
}

void checkButtons(){
  if (digitalRead(A_Button)==HIGH){
    delay(200);
    if (menuCursor==1){
      menuIndex = menuIndex + 2;
      if (menuIndex>=menuMax){
        menuIndex = 0;
      }
    }
    menuCursor = !menuCursor;
    menu_draw();
  }
  if (digitalRead(B_Button)==HIGH){
    delay(200);
    switch (menuCursor + menuIndex){
      case 0:
        Serial.println("Date/Time");
      break;
      case 1:
        Serial.println("Alarm");
      break;
      case 2:
        Serial.println("Config");
      break;
      case 3:
        Serial.println("Exit");
      break;
    }
  }
}

