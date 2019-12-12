#include <avr/io.h>
#include <avr/interrupt.h>

#include <can.h>
#include <logger.h>
#include <nodeman.h>
#include <spi.h>

int can_test_tx(void) {
	
	can_init();
	sei();

	uint8_t dat[8] = {0xAA};
	const uint32_t duration = 1000000;
	uint32_t ledi;
	uint8_t leds = 0x01;
	uint8_t dir = 0;
	DDRC = 0xFF;
	
	while (1) {
		
		can_transmit(dat, 1);
		
		for (ledi = 0; ledi < duration; ledi++);
		if (leds == 0x80) {
			dir = 1;
		} else if (leds == 0x01) {
			dir = 0;
		}
		if (dir) {
			leds >>= 1;
		} else {
			leds <<= 1;
		}
		PORTC = leds;
	}

	while(1);
	return 0;
}