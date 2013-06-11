#include "avrthing.h"
#include <stdio.h>
#include "analogIO.h"
#include "digitalIO.h"
#include <avr/pgmspace.h>
#include "pins/awesomedip.h"
#include "fermostat.h"
#include <avr/wdt.h>


char buf[10];

void loop(void);
void delaySec(unsigned int t);

int main(void)
{
	
	int i = 0;
	int pin = 0;


	wdt_enable(WDTO_500MS);

	initUSBSerial();
	initRTC();
 	
	analogSetup();	
	setRefVCC();
	pin = setPin(37);
 	setDirection(8, 1);	
	
	
	while(true)
	{
		runUSB();
		loop();
	}	

	return 0;
}

void loop(void)
{
	fermostat();
//	printf("looped\n\r");
	wdt_reset();

}
void delaySec(unsigned int t)
{
	unsigned long start = seconds();
	while(seconds()-start < t)
	{
		runUSB();
	}
}
