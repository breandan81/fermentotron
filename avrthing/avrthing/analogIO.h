#ifndef ANALOGIO_H
#define ANALOGIO_H

//variables

//prototypes
short 	getPin(short me);
void  	setRefVCC();
void	setRef(short me);
void 	setRefInternal();
void	setRefExternal();
short 	setPin(short me);
short 	convert();
short	analogRead(short me);
void	setDefaults();
void 	analogSetup();
short 	setThermo();
#endif
