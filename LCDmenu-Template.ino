/*
 Template to setup multiple page in a menu with 16x2 LCD display.
 Include a function to set the value displayed.
 Use 2 buttons right/left to navigate
 and 2 buttons up/down to set the value displayed

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor: 
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * 
 * up button to digital pin 8
 * down button to digital pin 9 
 * right button to digital pin 10
 * left button to digital pin 13

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi
 template added 28 March 2020 
 by L.M. Caron

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Pushbutton.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Pushbutton up(8);
Pushbutton down(9);
Pushbutton right(10);
Pushbutton left(13);

byte plein[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

int selected_menu = 1;
int nb_menus = 3;
int parameter1 = 20;
int parameter2 = 15;
int parameter3 = 30;
int actualValue = 4;
int now = 0;
int before = 0;

// function to DISPLAYS the selected menu (page)
void menu(int no_menu)
{
  switch(no_menu){
    case 1:
      lcd.clear();
      lcd.print("Parameter1:");
      lcd.print(parameter1);
      //example to display real-time value
      lcd.setCursor(0,1);
      lcd.print("ActualValue");
      for(int i = 0; i < actualValue; i++){
        lcd.write(byte(0));
      }
      //example end
      delay(150);
      break;  
    case 2:
      lcd.clear();
      lcd.print("Parameter2:");
      lcd.print(parameter2);
      delay(150);
      break;
     case 3:
      lcd.clear();
      lcd.print("Parameter3:");
      lcd.print(parameter3);
      delay(150);
      break;
  }
}

// function to NAVIGATE from page to page in the menu
// 1:to page at the right, 0:to page at the left
void changeMenu(int orientation)
{ 
  if(orientation == 1){selected_menu++;}
  if(orientation == 0){selected_menu--;}
  selected_menu = constrain(selected_menu, 1, nb_menus); 
  menu(selected_menu);
}

// function to SET the value of the current menu
// 1:increase the value, 0:decrease the value
void setValue(int orientation)
{
  switch (selected_menu){
    case 1:
      if(orientation == 1){parameter1++;}
      if(orientation == 0){parameter1--;}
      menu(selected_menu);
      break;
    case 2:
      if(orientation == 1){parameter2++;}
      if(orientation == 0){parameter2--;}
      menu(selected_menu);
      break;
    case 3:
      if(orientation == 1){parameter3++;}
      if(orientation == 0){parameter3--;}
      menu(selected_menu);
      break;
  }
}

void setup() {
  lcd.createChar(0,plein);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  menu(1);
}

void loop() {
  // read 4 buttons
  if(up.getSingleDebouncedRelease()){
   changeMenu(1);
  }
  if(down.getSingleDebouncedRelease()){
    changeMenu(0);
  }
  if(right.getSingleDebouncedRelease()){
    setValue(1);
  }
  if(left.getSingleDebouncedRelease()){
    setValue(0);
  }
  //example: update the actual value displays in menu1 each 3sec
  actualValue = random(1,3);
  now = millis();
  if(now - before > 3000 && selected_menu == 1){
    menu(selected_menu);
    before = now;
  }
}
