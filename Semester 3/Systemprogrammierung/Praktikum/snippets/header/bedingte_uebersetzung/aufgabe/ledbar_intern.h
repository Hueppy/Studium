/*
 * ledbar_intern.h
 *
 * Author: Carsten Gips
 *
 */

#ifndef SP_LEDBAR_INTERN_H
#define SP_LEDBAR_INTERN_H


#include "ledbar.h"  /* fuer brightness */


/* Defines der Pins */
#define PIN_DATA  16    /* auf dem Shield PIN 15 */
#define PIN_CLOCK 27    /* auf dem Shield PIN 16 */

/* LED-Status (intern) */
extern brightness LED_Bar_Status[10];

/* interne Hilfsfunktionen */
void toggle_clock(void);
void send_led_data(void);


#endif //SP_LEDBAR_INTERN_H
