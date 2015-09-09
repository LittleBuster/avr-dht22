/* Fast DHT Lirary
 *
 * Copyright (C) 2015 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 *
 * Original library written by Adafruit Industries. MIT license.
 */

#ifndef __FAST_DHT_H__
#define __FAST_DHT_H__

#include <stdint.h>

/*
 * Sensor's port
 */
#define DDR_DHT DDRB
#define PORT_DHT PORTB
#define PIN_DHT PINB

typedef struct dht_t DHT;

struct dht_t {
	uint8_t data[6];    /* data from sensor store here */
	uint8_t pin;        /* DDR & PORT pin */
	float temp;         /* current temperature */
	float hum;          /* current humidity */
};

/**
 * Init dht sensor
 * @dht: sensor struct
 * @pin: PORT & DDR pin
 */
void dht_init(DHT *dht, uint8_t pin);

/**
 * Reading temperature from sensor
 * @dht: sensor struct
 *
 * Returns 1 if succeful reading
 * Returns 0 if fail reading
 */
uint8_t dht_read_temp(DHT *dht);

/**
 * Reading humidity from sensor
 * @dht: sensor struct
 *
 * Returns 1 if succeful reading
 * Returns 0 if fail reading
 */
uint8_t dht_read_hum(DHT *dht);

/**
 * Reading temperature and humidity from sensor
 * @dht: sensor struct
 *
 * Returns 1 if succeful reading
 * Returns 0 if fail reading
 *
 * The fastest function for getting temperature + humidity.
 */
uint8_t dht_read_data(DHT *dht);


#endif
