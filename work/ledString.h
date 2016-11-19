#include <stdint.h>
#include <stdio.h>
#include "./ws2811/ws2811.h"

ws2811_t myledstring;

int initdone;
int LEDANZ;

int getLEDcolor(int ledNum);

int initLEDs(int anz);
int setLED(int ledNum, int rgb);
int setBrightness(int brt);
int setLEDsOFF();
int setLEDS(int rgb);
int setLEDsR();
int serLEDsG();
int setLEDsB();
int setLEDsW();
