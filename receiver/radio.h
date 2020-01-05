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
   This function will be called when data is received
*/
void on_data(char *data);

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
  nrf.openReadingPipe(0, rx_addr);
  nrf.startListening();
}

/**
   Scan the radio. Put this function on main loop
*/
void radio_scan(void)
{
  if (nrf.available())
  {
    char data[LENGTH + 1];
    nrf.read(&data, sizeof(data));
    on_data(data);
  }
}

#endif /* RADIO_H_ */
