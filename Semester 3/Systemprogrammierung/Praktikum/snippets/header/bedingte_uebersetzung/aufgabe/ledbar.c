/*
 * ledbar.c
 *
 * Author: Carsten Gips
 *
 */

#include "ledbar_intern.h"
#include "ledbar.h"


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
