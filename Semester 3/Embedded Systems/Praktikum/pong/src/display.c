// Original code from https://github.com/agra-uni-bremen/sifive-hifive1
#include "display.h"

#include <stdlib.h>
#include "platform.h"

#define MAX_SPI_FREQ   ( 8000000)

static void sleep_u(uint64_t micros)
{
    volatile uint64_t * now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + ((micros * RTC_FREQ) / (1000 * 1000));
    while (*now < then){}
}

static uint32_t mapPinToReg(uint8_t pin)
{
	uint32_t result = 0U;
    if(pin < 8U)
    {
        result = pin + PIN_0_OFFSET;
    }
    if((pin >= 8U) && (pin < 14U))
    {
        result = pin - 8U;
    }
    //ignoring non-wired pin 14 <==> 8
    if((pin > 14U) && (pin < 20U))
    {
        result = pin - 6U;
    }
    return result;
}

void setPin(uint8_t pin, uint8_t val)
{
	if(val > 0U)
	{
		GPIO_REG(GPIO_OUTPUT_VAL) |= 1U << mapPinToReg(pin);
	}
	else
	{
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~(1U << mapPinToReg(pin));
	}
}

void spi_init(void)
{

	//Pins enable output
	GPIO_REG(GPIO_INPUT_EN)   &= ~((1U << mapPinToReg(OLED_SDIN)) |
									(1U << mapPinToReg(OLED_SCLK)) |
									(1U << mapPinToReg(OLED_CS)));
	GPIO_REG(GPIO_OUTPUT_EN)  |= ((1U << mapPinToReg(OLED_SDIN)) |
									(1U << mapPinToReg(OLED_SCLK)) |
									(1U << mapPinToReg(OLED_CS)));

    // Select IOF SPI1.MOSI [SDIN] and SPI1.SCK [SLCK] and SPI1.SS0 [CS]
    GPIO_REG(GPIO_IOF_SEL)    &= ~((1U << mapPinToReg(OLED_SDIN)) |
    								(1U << mapPinToReg(OLED_SCLK)) |
									(1U << mapPinToReg(OLED_CS)));

    GPIO_REG(GPIO_IOF_EN )    |=  ((1U << mapPinToReg(OLED_SDIN)) |
    								(1U << mapPinToReg(OLED_SCLK)) |
    								(1U << mapPinToReg(OLED_CS)));

    // Set up SPI controller
    /** SPI clock divider: determines the speed of SPI
     * transfers.
     * The formula is CPU_FREQ/(1+SPI_SCKDIV)
     */
    SPI1_REG(SPI_REG_SCKDIV)    = (get_cpu_freq() / MAX_SPI_FREQ) - 1;
    SPI1_REG(SPI_REG_SCKMODE)   = 0; /* pol and pha both 0 - SCLK is active-high, */
    SPI1_REG(SPI_REG_CSID)      = OLED_CS_OFS;
    SPI1_REG(SPI_REG_CSDEF)     = 0xffff; /* CS is active-low */
    SPI1_REG(SPI_REG_CSMODE)    = SPI_CSMODE_HOLD; /* hold CS where possible */
    /* SPI1_REG(SPI_REG_DCSSCK)    = */
    /* SPI1_REG(SPI_REG_DSCKCS)    = */
    /* SPI1_REG(SPI_REG_DINTERCS)  = */
    /* SPI1_REG(SPI_REG_DINTERXFR) = */
    SPI1_REG(SPI_REG_FMT)       = SPI_FMT_PROTO(SPI_PROTO_S) | SPI_FMT_ENDIAN(SPI_ENDIAN_MSB) | SPI_FMT_DIR(SPI_DIR_TX) | SPI_FMT_LEN(8);
    /* SPI1_REG(SPI_REG_TXCTRL)    = 1; *//*interrupt when <1 in tx fifo (completion) */
    /* SPI1_REG(SPI_REG_RXCTRL)    = */
    /* SPI1_REG(SPI_REG_IE)        = SPI_IP_TXWM;	*/ /* enables TXWM-Interrupt */
}

void spi(uint8_t data)
{
    while ((SPI1_REG(SPI_REG_TXFIFO) & SPI_TXFIFO_FULL) > 0U) {
    	asm volatile("nop");
	}
    SPI1_REG(SPI_REG_TXFIFO) = data;
}


void mode_data(void)
{	//not already in data mode
	if(!(GPIO_REG(GPIO_OUTPUT_VAL) & (1U << mapPinToReg(OLED_DC))))
	{
		setPin(OLED_DC, 1);
	}
}

void mode_cmd(void)
{
	//not already in command mode
	if((GPIO_REG(GPIO_OUTPUT_VAL) & (1U << mapPinToReg(OLED_DC))) > 0)
	{
		setPin(OLED_DC, 0U);
	}
}

void setDisplayOn(uint8_t on)
{
	mode_cmd();
	spi(0xAEU | (on & 1U));
}

void setChargePumpVoltage(uint8_t voltage)
{
	mode_cmd();
	spi(0b00110000U | (voltage & 0b11U));
}

void invertColor(uint8_t invert)
{
	mode_cmd();
	spi(0b10100110U | (invert & 1U));	//set 'normal' direction (1 = bright)
}

void setEntireDisplayOn(uint8_t allWhite)
{
	mode_cmd();
	spi(0b10100100U | (allWhite & 1U));
}

void setDisplayStartLine(uint8_t startline)
{
	mode_cmd();
	spi(0b01000000U | (startline & 0b111111U));
}

void setDisplayOffset()
{
	mode_cmd();
    spi(0b11010011U);	//double byte to set display offset to (y)0;
    spi(0b00000000U);	//double byte to set display offset to (y)0;
}

void flipDisplay(uint8_t flip)
{
	mode_cmd();
	spi(0b11000000U | (0b1111U * (flip & 1U)));
}

void setContrast(uint8_t contrast)
{
	/**
	 * Segment output current setting: ISEG = a/256* IREF * scale_factor
	 * Where a is contrast step, IREF is reference current (12.5uA), scale_factor = 16
	 */
	mode_cmd();
	spi(0b10000001U);	//Contrast mode
	spi(contrast);
}

void fadeIn(uint64_t millis)
{
	for(uint8_t contrast = 0U; contrast != 0xffU; contrast++)
	{
		setContrast(contrast);
		sleep_u((millis * 1000U) / 256U);
	}
}

void fadeOut(uint64_t millis)
{
	for(uint8_t contrast = 0xffU; contrast != 0U; contrast--)
	{
		setContrast(contrast);
		sleep_u((millis * 1000U) / 256U);
	}
}

/** Initialize pmodoled module */
void oled_init()
{
    spi_init();

    // Initial setup

    //Enable RESET and D/C Pin
	GPIO_REG(GPIO_INPUT_EN)   &= ~((1U << mapPinToReg(OLED_RES)) |
									(1U << mapPinToReg(OLED_DC)));
	GPIO_REG(GPIO_OUTPUT_EN)  |= ((1U << mapPinToReg(OLED_RES)) |
									(1U << mapPinToReg(OLED_DC)));
	setPin(OLED_DC, 0U);

	//RESET
	setPin(OLED_RES,0U);
	sleep_u(10U);		//min 10us
	setPin(OLED_RES,1U);
	sleep_u(100000U);	//'about 100ms'

    // Command mode
	mode_cmd();

    // To see the bug better. Normally, this is the last thing to do.
    // setDisplayOn(1);

	// Initialize display to desired operating mode.

    setChargePumpVoltage(0b10U);
    invertColor(0U);
    //flipDisplay(1);
    setContrast(0xffU);		//MY EYES!!!

    // 4. Clear screen (entire memory)
    oled_clear();
    setDisplayOn(1U);
}

void set_x(unsigned col)
{
    mode_cmd();
    spi(0x00U | ((col+DISP_W_OFFS) & 0xfU));
    spi(0x10U | (((col+DISP_W_OFFS) >> 4U)&0xfU));
    mode_data();
}
void set_row(unsigned row)
{
    mode_cmd();
    spi(0xb0U | (row & 0x7U));
    mode_data();
}

void set_xrow(unsigned col, unsigned row)
{
    mode_cmd();
    spi(0x00U | ((col+DISP_W_OFFS) & 0xfU));
    spi(0x10U | (((col+DISP_W_OFFS) >> 4U)&0xfU));
    spi(0xb0U | (row & 0x7U));
    mode_data();
}

void oled_clear(void)
{
	for (unsigned y = 0U; y < (DISP_H/8U); ++y) {
    	set_xrow(0U, y);
		for (unsigned x=0; x < DISP_W; ++x) {
    		spi(0x00U);
    	}
    }
	set_xrow(0U,0U);
}

