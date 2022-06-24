#include <wiringPi.h>

#include "ledanzeige/TM1637_intern.h"
#include "ledanzeige/segmentanzeige.h"

/**
 * @brief Setzt den Übergebenen Wert auf den Pin und wartet kurz damit die Spannung sich stabilisiert
 * 
 * @param pin Pin
 * @param value Neuer Wert des Pins
 */
void writeAndDelay(int pin, int value) 
{
    digitalWrite(pin, value);
    delayMicroseconds(DELAY_TIMER);
}

/**
 * @brief Überträgt den übergebenen Wert seriell
 * 
 * @param wr_data Zu übertragenen Wert
 */
void TM1637_write_byte(byte wr_data)
{
    byte mask = 1;
    while (mask > 0) {
        writeAndDelay(PIN_CLOCK, LOW);
        writeAndDelay(PIN_DATA, (wr_data & mask) > 0 ? HIGH : LOW);
        writeAndDelay(PIN_CLOCK, HIGH);

        mask <<= 1;
    }

    TM1637_ack();
}