/*
 * ledbar.h
 *
 * Author: Carsten Gips
 *
 */

#ifndef SP_LEDBAR_H
#define SP_LEDBAR_H


/* Datentypen mit enum und struct */
typedef ... led;
typedef ... brightness;

/* Schnittstelle */
void init_led_bar(void);
int set_led(led l, brightness b);


#endif //SP_LEDBAR_H
