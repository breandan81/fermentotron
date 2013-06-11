#include "avrthing.h"
#include "fermostat.h"
#include <stdlib.h>
#include <stdio.h>

/*---
Command set:

sxx set temp to xx
get get temp
o11 turn on
o10 turn off

------*/
//constants
#define maxTemp 55
#define minTemp -1
#define sensorPin 37
#define relayPin 8
#define minOff 300 //minimum time off in seconds
#define hyst 1 //will try to hold +- 1 C
#define VREF 495

//prototypes
void doCmd(void);
short getTemp(short pin);
void checkTemp();
void switchOn();
void switchOff();
//end prototypes


//globals
char cmd[3];
int index = -1;
int setTemp = 20;
unsigned long timeOff = 0;
//end globals

void checkTemp()
{
	if(getTemp(sensorPin) > setTemp + hyst)
	{
		switchOn();
	}
	else
		switchOff();
}
void switchOn()
{
	if(timeOff + minOff < seconds())
	{
		return;
	}
	if(getTemp(sensorPin)>maxTemp)
	{
		return;
	}
	
	digitalWrite(relayPin, HIGH);
	timeOff = -1;
}
void switchOff()
{
	if(timeOff == -1) //then we're on, otherwise don't do anything
	{
		digitalWrite(relayPin, LOW);
		timeOff = seconds();
	}
}

short getTemp(short pin)
{
	long me = analogRead(pin);
	
	me *= VREF;
	me /= 1024;
	me -= 273;
	return (short) me;
}
void doCmd()
{
	switch(cmd[0])
	{
		case 'g':
			if(cmd[1] == 'e' && cmd[2] == 't')
			{
				printf("temp is %d\n\r",getTemp(sensorPin));
			}
			break;
		case 'o':
			if(cmd[1] == '1' && (cmd[2]=='0' || cmd[2]=='1'))
			{
				digitalWrite(relayPin, cmd[2]-'0');
				printf("pin %d %d \n\r", relayPin,  cmd[2]-'0');
			}			
			break;
		case 's':
			if(cmd[1] >= '0' && cmd[1] <= '9')
			{
				if(cmd[2] >= '0' && cmd[2] <= '9')
				{
					setTemp = (10*(cmd[1]-'0'))+(cmd[2]-'0');
					printf("setpoint is %d\n\r", setTemp);
				}
			}
			break;
		default:
			printf("error \n\r");
			break;
	}
}
void fermostat()
{
//first part of this is going to get chars from the serial and either discard them or put them in the current command
	int me = getchar();
	
	if(me > -1)
	{
		putchar(me);
		if (me == 'f')
		{
			index = 0;
		}
		else if(index < 3 && index > -1)
		{
			cmd[index] = me;
			index++;
		}

	}	
	if(index == 3)
	{
		doCmd();
		index = -1;
	}

	checkTemp();
}

