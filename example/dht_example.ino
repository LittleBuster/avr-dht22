#include <fdht.h>
#include <fdht.c>

struct dht_t dht;

void setup()
{
    Serial.begin(9600);
    dht_init(&dht, 1);
}

void loop()
{
    float t;
    float h;
    
    if (dht_read_data(&dht, &t, &h)) {
        Serial.print("\nTemp: ");
        Serial.println(t);
        Serial.print("Hum: ");
        Serial.println(h);
    } else {
        Serial.println("Error reading");
    }
    
    delay(2000);
}
