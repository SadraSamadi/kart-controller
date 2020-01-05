#ifndef INPUT_H_
#define INPUT_H_

#include <Keypad.h>

/* Keypad pins */
#define ROW0      6
#define ROW1      5
#define ROW2      4
#define ROW3      3
#define COL0      2
#define COL1      1
#define COL2      0

const byte KPD_ROWS = 4; // Keypad rows number
const byte KPD_COLS = 3; // Keypad column numbers

/* Keypad map */
char keys[KPD_ROWS][KPD_COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

/* Keypad rows array */
byte rowPins[KPD_ROWS] = { ROW0, ROW1, ROW2, ROW3 };
/* Keypad columns array */
byte colPins[KPD_COLS] = { COL0, COL1, COL2 };

/* Keypad declaration */
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, KPD_ROWS, KPD_COLS);

/**
   This function will be called once a button is clicked
*/
void on_keypad(char key);

/**
   Scan the keypad. Put this function on main loop
*/
void input_scan(void)
{
  char key = kpd.getKey();
  if (key)
    on_keypad(key);
}

#endif /* INPUT_H_ */
