/* DHT Sensor library
 *
 * MIT license
 * written by Adafruit Industries
 * rewritten by Denisov Sergey 2015
 */

#include "DHT.h"
#include <avr/io.h>
#include <util/delay.h>

#define DHT_COUNT 6
#define DHT_MAXTIMINGS 85


/* Init sensor */
void dht_begin(DHT *dht, uint8_t pin)
{
    dht->_pin = pin;
    dht->firstreading = true;
    /* Setup the pins! */
    DDR_DHT &= ~(HIGH << dht->_pin);
    PORT_DHT |= (HIGH << dht->_pin);
    dht->_lastreadtime = 0;
}

bool dht_read(DHT *dht)
{
    uint8_t laststate = HIGH;
    uint16_t counter = 0;
    uint8_t j = 0, i;
    uint8_t tmp;
    unsigned long currenttime;
    /*
     * Pull the pin high and wait 250 milliseconds
     */
    PORT_DHT |= (HIGH << dht->_pin);
    _delay_ms(250);

    currenttime = millis();
    if (currenttime < dht->_lastreadtime) {
        /* IE there was a rollover */
        dht->_lastreadtime = 0;
    }
    if (!dht->firstreading && ((currenttime - dht->_lastreadtime) < 2000))
        return true;

    dht->firstreading = false;
    dht->_lastreadtime = millis();

    dht->data[0] = dht->data[1] = dht->data[2] = dht->data[3] = dht->data[4] = 0;

    /* Now pull it low for ~20 milliseconds */
    DDR_DHT |= (HIGH << dht->_pin);
    PORT_DHT &= ~(HIGH << dht->_pin);
    _delay_ms(20);
    cli();
    PORT_DHT |= (HIGH << dht->_pin);
    _delay_us(40);
    DDR_DHT &= ~(HIGH << dht->_pin);

    /* Read the timings */
    for (i = 0; i < DHT_MAXTIMINGS; i++) {
        counter = 0;
        while (1) {
            tmp = ((PIN_DHT & (HIGH << dht->_pin)) >> 1);
            _delay_us(3);

            if (tmp != laststate)
                break;

            counter++;
            _delay_us(1);

            if (counter == 255)
                break;
        }

        laststate = ((PIN_DHT & (HIGH << dht->_pin)) >> 1);

        if (counter == 255)
            break;

        /* Ignore first 3 transitions */
        if ((i >= 4) && (i%2 == 0)) {
            /* Shove each bit into the storage bytes */
            dht->data[j/8] <<= 1;
            if (counter > DHT_COUNT)
                dht->data[j/8] |= 1;
            j++;
        }
    }

    sei();

    if ((j >= 40) && (dht->data[4] == ((dht->data[0] + dht->data[1] +
                                    dht->data[2] + dht->data[3]) & 0xFF)) ) {
        return true;
    }
    return false;
}

/*
 * boolean S == Scale.
 * True == Farenheit;
 * False == Celcius
 *
 */
float dht_readTemperature(DHT *dht, bool S)
{
    float f;
    if (dht_read(dht)) {
        f = dht->data[2] & 0x7F;
        f *= 256;
        f += dht->data[3];
        f /= 10;

        if (dht->data[2] & 0x80)
            f *= -1;
        return f;
    }
    return NAN;
}

float dht_readHumidity(DHT *dht)
{
    float f;

    if (dht_read(dht)) {
        f = dht->data[0];
        f *= 256;
        f += dht->data[1];
        f /= 10;
        return f;
    }
    return NAN;
}
