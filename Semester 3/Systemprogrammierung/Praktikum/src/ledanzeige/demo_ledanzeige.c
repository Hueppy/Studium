#include <stdio.h>
#include "TM1637.c"
#include "segmentanzeige.c"

/**
 * @brief `main()` des Demo-Programms
 * 
 * @return int Rückgabewert
 */
int main()
{
    uint8_t i;

    TM1637_setup();
    for (i = 0; i < 10; i++)
    {
        TM1637_display_number(i * 111.1);
        delay(2000);
    }    

    return 0;
}