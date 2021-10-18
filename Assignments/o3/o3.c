#include "o3.h"
#include "gpio.h"
#include "systick.h"
#include <stdbool.h>
/**************************************************************************//**
 * @brief Konverterer nummer til string 
 * Konverterer et nummer mellom 0 og 99 til string
 *****************************************************************************/

volatile gpio_map_t* gpio_base_address = (gpio_map_t*) GPIO_BASE;
volatile systick_map_t* systick_base_address = (systick_map_t*) SYSTICK_BASE;
int currentState = 0;
char currentTime[6];
int seconds;
int minutes;
int hours;


void int_to_string(char *timestamp, unsigned int offset, int i) {
    if (i > 99) {
        timestamp[offset]   = '9';
        timestamp[offset+1] = '9';
        return;
    }

    while (i > 0) {
	    if (i >= 10) {
		    i -= 10;
		    timestamp[offset]++;
		
	    } else {
		    timestamp[offset+1] = '0' + i;
		    i=0;
	    }
    }
}

/**************************************************************************//**
 * @brief Konverterer 3 tall til en timestamp-string
 * timestamp-argumentet må være et array med plass til (minst) 7 elementer.
 * Det kan deklareres i funksjonen som kaller som "char timestamp[7];"
 * Kallet blir dermed:
 * char timestamp[7];
 * time_to_string(timestamp, h, m, s);
 *****************************************************************************/
void time_to_string(char *timestamp, int h, int m, int s) {
    timestamp[0] = '0';
    timestamp[1] = '0';
    timestamp[2] = '0';
    timestamp[3] = '0';
    timestamp[4] = '0';
    timestamp[5] = '0';
    timestamp[6] = '\0';

    int_to_string(timestamp, 0, h);
    int_to_string(timestamp, 2, m);
    int_to_string(timestamp, 4, s);


}

void initialize_LED(void) {
	uint32_t MODELcontent = gpio_base_address->ports[4].MODEL;						//Contents in MODEH in PORT E

	uint32_t ledMesh = 0b1111<<8;											//Creating mesh for MODEH clean out PIN10 data.
	ledMesh = ~ledMesh;														//Inverting ledMesh
	uint32_t LEDoutputMESH = GPIO_MODE_OUTPUT<<8;							//Creating mesh for set GPIO_MODE_OUTPUT

	MODELcontent = MODELcontent & ledMesh;									//Clearing out PIN10 data
	MODELcontent = MODELcontent | LEDoutputMESH;							//Finishing output
	gpio_base_address->ports[4].MODEL = MODELcontent;									//GPIO_MODE for LED is now set active
}

void turn_on_LED(void) {
	uint32_t ledMesh = 1<<2;															//Mesh for turning LED on
	gpio_base_address->ports[4].DOUTSET = ledMesh;
}

void turn_off_LED(void) {
	uint32_t ledMesh = 1<<2;															//Mesh for turning LED on
	gpio_base_address->ports[4].DOUTCLR = ledMesh;
}

void initialize_Buttons(void) {
	uint32_t MODEHcontent = gpio_base_address->ports[1].MODEH;
	uint32_t EXTIPSELHcontent = gpio_base_address->EXTIPSELH;
	uint32_t EXTIFALLcontent = gpio_base_address->EXTIFALL;
	uint32_t IENcontent = gpio_base_address->IEN;

	uint32_t pb0Mesh = 0b1111<<4;											//Selecting PIN9 on PORTB
	uint32_t pb1Mesh = 0b1111<<8;											//Selecting PIN10 on PORTB
	pb0Mesh = ~pb0Mesh;
	pb1Mesh = ~pb1Mesh;

	MODEHcontent = MODEHcontent & pb0Mesh & pb1Mesh;
	EXTIPSELHcontent = EXTIPSELHcontent & pb0Mesh & pb1Mesh;

	pb0Mesh = GPIO_MODE_INPUT<<4;
	pb1Mesh = GPIO_MODE_INPUT<<8;

	MODEHcontent = MODEHcontent | pb0Mesh | pb1Mesh;
	EXTIPSELHcontent = EXTIPSELHcontent | pb0Mesh | pb1Mesh;

	gpio_base_address->ports[1].MODEH = MODEHcontent;
	gpio_base_address->EXTIPSELH = EXTIPSELHcontent;

	pb0Mesh = 1<<9;
	pb1Mesh = 1<<10;

	EXTIFALLcontent = EXTIFALLcontent | pb0Mesh | pb1Mesh;
	IENcontent = IENcontent | pb0Mesh | pb1Mesh;

	gpio_base_address->EXTIFALL = EXTIFALLcontent;
	gpio_base_address->IEN = IENcontent;
}

void initialize_SysTick(void) {
	systick_base_address->CTRL = systick_base_address->CTRL | SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
	systick_base_address->LOAD = FREQUENCY;
	systick_base_address->VAL = FREQUENCY;
}

void SysTick_Handler(void) {
	if (currentState == 3) {
		if (seconds > 0) {
			seconds--;
			time_to_string(currentTime, hours, minutes, seconds);
			lcd_write(currentTime);
		}
		else if (minutes > 0) {
			minutes--;
			seconds = 59;
			time_to_string(currentTime, hours, minutes, seconds);
			lcd_write(currentTime);
		}
		else if (hours > 0) {
			hours--;
			minutes = 59;
			seconds = 59;
			time_to_string(currentTime, hours, minutes, seconds);
			lcd_write(currentTime);
		}
		else {
			currentState++;
			turn_on_LED();
		}
	}
}

void GPIO_ODD_IRQHandler(void) {
	switch(currentState){
	case 0:
		if (seconds < 59) {
			seconds++;

			time_to_string(currentTime, hours, minutes, seconds);
			lcd_write(currentTime);
		}
		else {
			seconds = 0;

			time_to_string(currentTime, hours, minutes, seconds);
			lcd_write(currentTime);
		}
		break;
	case 1:
		if (minutes < 59) {
			minutes++;

			time_to_string(currentTime, hours, minutes, seconds);
			lcd_write(currentTime);
		}
		else {
			minutes = 0;

			time_to_string(currentTime, hours, minutes, seconds);
			lcd_write(currentTime);
		}
		break;
	case 2:
		if (hours < 99) {
			hours++;

			time_to_string(currentTime, hours, minutes, seconds);
			lcd_write(currentTime);
		}
		else {
			hours = 0;

			time_to_string(currentTime, hours, minutes, seconds);
			lcd_write(currentTime);
		}
		break;
	}
	uint32_t pb0Mesh = 1<<9;
	gpio_base_address->IFC = (gpio_base_address->IFC)| pb0Mesh;
}

void GPIO_EVEN_IRQHandler (void) {
	switch(currentState){
	case 0:
		turn_off_LED();
		currentState++;
		break;
	case 1:
		currentState++;
		break;
	case 2:
		currentState++;
		break;
	case 4:
		currentState = 0;
		turn_off_LED();
		break;
		}
	uint32_t pb1Mesh = 1<<10;
	gpio_base_address->IFC = (gpio_base_address->IFC)| pb1Mesh;
}

int main(void) {
    init();
    // Skriv din kode her...
    initialize_Buttons();
    initialize_LED();
    initialize_SysTick();
    time_to_string(currentTime,0,0,0);
    lcd_write(currentTime);
    while(1) {

    }
    return 0;
}
