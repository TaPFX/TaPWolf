#include <stdint.h>
#include <stdio.h>
#include "./ws2811/ws2811.h"

ws2811_t myledstring;

int initdone;
int LEDANZ;

int initLEDs(int anz);
int setLED(int ledNum, int rgb, int intensety);
int setLEDsOFF();
int setLEDsR();
int serLEDsG();
int setLEDsB();
int setLEDsW();