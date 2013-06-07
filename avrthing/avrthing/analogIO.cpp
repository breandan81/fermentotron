#include "avrthing.h"
#include "analogIO.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <stdio.h>

/*Hardware dependent, translates a pin on the package to the bits that need to be written to ADMUX
this is written for the AWESOMEDIP

returns -1 if pin is invalid

AD Channel	Port Pin	AwesomeDIP Pin
		
AD0		PF0		38
AD1		PF1		37
AD2		none		
AD3		none
AD4		PF4		36
AD5		PF5		35
AD6		PF6		34
AD7		PF7		33
AD8		PD4		22
AD9		PD6		23
AD10		PD7		24
AD11		PB4		25
AD12		PB5		26
AD13		PB6		27
*/

short getPin(short me)
{
	switch(me)
	{
		case 38: return 0; //ADC0
		case 37: return 1; //ADC1
		case 36: return 4; //ADC4
		case 35: return 5; //ADC5
		case 34: return 6; //ADC6
		case 33: return 7; //ADC7
		case 22: return 32; //ADC8
		case 23: return 33; //ADC9
		case 24: return 34; //adc10
		case 25: return 35; //adc11
		case 26: return 36; //adc12
		case 27: return 37; //adc13
	}
	return -1;
}

void setRef(short me)
{
	ADMUX = (ADMUX &(0x3F)) | ((char)me<<6);
}
void setRefInternal()
{
	setRef(3);
}
void setRefExternal()
{
	setRef(0);
}
void setRefVCC()
{
	setRef(1);
}
short setPin(short me)
{
	short pin = getPin(me);
	if(pin < 0)
		return -1;
	else
	{
		ADMUX = (ADMUX & 0xC0) | (pin&0x0F);
		if(pin & 0xF0)
		{
			ADCSRB |= _BV(MUX5);
		}
		else
		{
			ADCSRB &= ~_BV(MUX5);
		}
	}
	return pin;
}
short setThermo()
{
	setRefInternal();

        short pin = 39;
        if(pin < 0)
                return -1;
        else
        {
                ADMUX = (ADMUX & 0xC0) | (pin&0x0F);
                if(pin & 0xF0)
                {
                        ADCSRB |= _BV(MUX5);
                }
                else
                {
                        ADCSRB &= ~_BV(MUX5);
                }
        }
        return pin;

}

short convert()
{
	ADCSRA |= 1 << ADEN; //enable ADC
	ADCSRA |= 1 << ADSC; //begin a conversion

	
	while(ADCSRA & (1 << ADSC))
	{}
	short result = ADCL;
	result |= ADCH<<8;
	
	ADCSRA &= ~(1<<ADEN);
	return result;
}

void analogSetup()
{
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
	setRefInternal();
}
short analogRead(short me)
{
	if(setPin(me)<0)
		return -1;

	short result = convert();
	return result;
}

