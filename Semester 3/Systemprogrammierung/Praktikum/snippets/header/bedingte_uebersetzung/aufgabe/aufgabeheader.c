/*
 * aufgabeheader.c
 *
 * Author: Carsten Gips
 *
 */

/* Defines der Pins */
#define PIN_DATA  16    /* auf dem Shield PIN 15 */
#define PIN_CLOCK 27    /* auf dem Shield PIN 16 */

/* Datentypen mit enum und struct */
typedef ... led;
typedef ... brightness;

/* LED-Status (intern) */
brightness LED_Bar_Status[10];

/* interne Hilfsfunktionen */
void toggle_clock(void) { ... }
void send_led_data(void) {
    /* uses toggle_clock() */
}

/* Schnittstelle */
void init_led_bar(void) {
    /* uses LED_Bar_Status and send_led_data() */
}
int set_led(led l, brightness b) {
    /* uses LED_Bar_Status and send_led_data() */
}

/* Demo */
int main(void) {
    init_led_bar();
    set_led(LED01, FULL);
}
