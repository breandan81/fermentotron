#include "avrthing.h"
#include <stdio.h>
#include "analogIO.h"
#include "digitalIO.h"
#include <avr/pgmspace.h>
#include "pins/awesomedip.h"
int main(void)
{
	
	int i = 0;
	int pin = 0;
	initUSBSerial();
	initRTC();
 	
	analogSetup();	
	setRefVCC();
	pin = setPin(37);

	while(true)
	{
		short temp = convert();
		printf("pin %d = %d or %d deg C read %d times ADCSRB = %x ADMUX = %x 1<<6 = %x \n\r", pin, temp, (short)((((long)temp*500l)/1024l)-273), i, ADCSRB, ADMUX, 1<<6);
		setDirection(8, 1);
		digitalWrite(8,1);
		delayMillis(100);
		i++;
	}	

	return 0;
}
