#ifndef RADIO_H_
#define RADIO_H_

#include <SPI.h>
#include <RF24.h>

/* nRF pins */
#define CE        8
#define CSN       9

/* Maximum data length */
#define LENGTH    32

/* Pipe address */
const byte rx_addr[6] = "00001";
RF24 nrf(CE, CSN);

/**
   Config nRF module
*/
void radio_init(void)
{
  nrf.begin();
  nrf.setPALevel(RF24_PA_MAX);
  nrf.setDataRate(RF24_250KBPS);
  nrf.setCRCLength(RF24_CRC_8);
  nrf.setRetries(15, 15);
  nrf.openWritingPipe(rx_addr);
  nrf.stopListening();
}

/**
   Send data
*/
void send(const char *data)
{
  nrf.write(data, strlen(data) + 1);
}

/**
   Seperate address and message with '#' then send them
*/
void sendto(int address, char *msg)
{
  char str[LENGTH + 1];
  sprintf(str, "%d#%s", address, msg);
  send(str);
}

#endif /* RADIO_H_ */
