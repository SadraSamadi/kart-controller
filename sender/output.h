#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <LiquidCrystal.h>

/* LCD pins */
#define RS        A0
#define E         A1
#define D4        A2
#define D5        A3
#define D6        A4
#define D7        A5

#define LCD_ROWS  16  // LCD rows number
#define LCD_COLS  2   // LCD columns number

/* LCD declaration */
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

/**
   LCD initialize
*/
void output_init(void)
{
  lcd.begin(LCD_COLS, LCD_ROWS);
}

/*
   Clear all data on LCD
*/
void clear(void)
{
  lcd.clear();
}

/**
   Move LCD cursor
*/
void gotoxy(unsigned char x, unsigned char y)
{
  lcd.setCursor(x, y);
}

/**
   Print on LCD
*/
void print(char *msg)
{
  lcd.print(msg);
}

/**
   Print text on given position
*/
void printxy(unsigned char x, unsigned char y, char *msg)
{
  gotoxy(x, y);
  print(msg);
}

/**
   Print a char on given position
*/
void putcharxy(unsigned char x, unsigned char y, char c)
{
  printxy(x, y, &c);
}

/**
   Clear first line of LCD
*/
void clearln1(void)
{
  printxy(0, 0, "                ");
}

/**
   Clear second line of LCD
*/
void clearln2(void)
{
  printxy(0, 1, "                ");
}

/**
   Print text on first line
*/
void println1(char *msg)
{
  clearln1();
  printxy(0, 0, msg);
}

/**
   Print text on second line
*/
void println2(char *msg)
{
  clearln2();
  printxy(0, 1, msg);
}

#endif /* OUTPUT_H_ */
