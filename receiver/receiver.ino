#include "radio.h"

/* The unique address of device */
#define ADDRESS   2

/* Relay pin */
#define RELAY     2

/* Message for action */
#define MSG       "on"

/**
   Return the position of a character in string
*/
int index_of(char c, char *str)
{
  for (int i = 0; i < strlen(str); i++)
    if (str[i] == '#')
      return i;
  return -1;
}

/**
   Compare two string
*/
bool compare(char *a, char *b)
{
  unsigned char alen = strlen(a);
  unsigned char blen = strlen(b);
  if (alen != blen)
    return false;
  for (unsigned char i = 0; i < alen; i++)
    if (a[i] != b[i])
      return false;
  return true;
}

/**
   Turn on relay for 15 seconds
*/
void relay(void)
{
  digitalWrite(RELAY, 1);
  delay(15000);
  digitalWrite(RELAY, 0);
}

/**
   Check address and message for action
*/
void action(int address, char *msg)
{
  if (address == ADDRESS)
    if (compare(msg, MSG))
      relay();
}

/**
   Initialize
*/
void setup()
{
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, 0);
  radio_init();
}

/**
   Main loop
*/
void loop()
{
  radio_scan();
}

/**
   This function will be called when data is received
*/
void on_data(char *data)
{
  Serial.println(data);
  unsigned char hash_index = index_of('#', data);
  unsigned char data_length = strlen(data);
  unsigned char address_length = hash_index;
  unsigned char msg_length = data_length - hash_index - 1;
  if (address_length < 1 || msg_length < 0)
    return;
  char address[address_length + 1];
  for (unsigned char i = 0; i < address_length; i++)
    address[i] = data[i];
  address[address_length] = '\0';
  char msg[msg_length + 1];
  for (unsigned char i = 0; i < msg_length; i++)
    msg[i] = data[hash_index + i + 1];
  msg[msg_length] = '\0';
  action(atoi(address), msg);
}

