#ifndef DHT_H
#define DHT_H
#include "Arduino.h"

/* DHT library 

MIT license
written by Adafruit Industries
rewritten by Denisov Sergey 2015
*/

// how many timing transitions we need to keep track of. 2 * number bits + extra
#define DDR_DHT DDRC	//
#define PORT_DHT PORTC	// Port for connection
#define PIN_DHT PINC	//

struct DHT {
	uint8_t data[6];
	uint8_t _pin, _type, _count;
	unsigned long _lastreadtime;
	bool firstreading;
};

void dht_begin( DHT *dht, uint8_t pin );
float dht_readTemperature( DHT *dht, bool S=false );
float dht_readHumidity( DHT *dht );

#endif
