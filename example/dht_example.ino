#include <fdht.h>
#include <fdht.c>

struct dht_t dht;

void setup()
{
    Serial.begin(9600);
    /* Digital pin 9 */
    dht_init(&dht, 1);
}

void loop()
{
    if (dht_read_data(&dht)) {
        Serial.print("\nTemp: ");
        Serial.println(dht.temp);
        Serial.print("Hum: ");
        Serial.println(dht.hum);
    } else {
        Serial.println("Error of reading");
    }
    
    delay(2000);
}
