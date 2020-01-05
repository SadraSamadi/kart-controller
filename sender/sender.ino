#include "output.h"
#include "input.h"
#include "radio.h"

/* Inpput buffer length */
#define BUFFLEN   4

/* Message for send to receiver */
#define MSG       "on"

/* Buffer for save input (+1 for null) */
char buff[BUFFLEN + 1];
unsigned char ptr = 0; // Pointer for LCD cursor

/**
   Show message on start up
*/
void welcome(void)
{
  for (unsigned char i = 0; i < 3; i++)
  {
    println1(" Carting Remote ");
    println2("Design : S. & P.");
    delay(400);
    clear();
    delay(200);
  }
}

/**
   Reset the buffer
*/
void clear_buffer(void)
{
  for (unsigned char i = 0; i < BUFFLEN; i++)
    buff[i] = NULL;
  ptr = 0;
}

/**
   Show a message for one second
*/
void state(char *msg)
{
  clear_buffer();
  println2(msg);
  delay(1000);
  clearln2();
}

/**
   Check input and send data. Will be called when '#' is clicked
*/
void action(int address)
{
  if (!address) // Check if address is valid
  {
    state("Invalid Input !");
  }
  else
  {
    sendto(address, MSG);
    state("Done ...");
  }
}

/**
   Initialize
*/
void setup(void)
{
  output_init();
  radio_init();
  welcome();
  println1("Car Number :    ");
}

/**
   Main loop
*/
void loop(void)
{
  input_scan();
}

/**
   Will be called when a key is clicked
*/
void on_keypad(char key)
{
  switch (key)
  {
    case '*':
      clear_buffer();
      break;
    case '#':
      // Parse char array to intiger number
      action(atoi(buff));
      break;
    default:
      /* Save data in buffer */
      if (ptr < BUFFLEN)
        buff[ptr++] = key;
  }
  println2(buff);
}
