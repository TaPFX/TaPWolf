#include "ledString.h"

ws2811_t myledstring =
{
	.freq = WS2811_TARGET_FREQ,
	.dmanum = 5,
	.channel = {
							[0] = {
										.gpionum = 18,
										.count = 50,
										.invert = 0,
										.brightness = 255,
										.strip_type = WS2811_STRIP_RGB,},
							[1] = {
										.gpionum = 0,
										.count = 0,
										.invert = 0,
										.brightness = 0,},
							},
};

initdone = 0;
LEDANZ = 50;

int initLEDs(int anz){
	initdone = 0;
	
	if(anz > 250 || anz < 1)
		return -2;

	LEDANZ = anz;
	myledstring.channel[0].count = anz;
	
	if(ws2811_init(&myledstring))
		return -1;

	initdone = 1;
	return 0;
}

int setLED(int ledNum, int rgb, int intensety){
	int i=0;
	if(initdone == 0)
		return -1;

	if(ledNum > myledstring.channel[0].count || ledNum < 0 )
		return -2;
	
	if(rgb > 0xFFFFFF || rgb < 0)
		return -2;

	if(intensety > 100 || intensety < 0)
		return -2;
	

	myledstring.channel[0].leds[ledNum] = rgb;

	if(ws2811_render(&myledstring))
		return -1;
	
	return 0;
}

int setLEDsOFF(){
	int i=0;
	if(initdone == 0)
		return -1;

	for(i=0;i<LEDANZ;i++)
		myledstring.channel[0].leds[i] = 0x00;

	if(ws2811_render(&myledstring))
		return -1;
	
	return 0;
}

int setLEDsR(){
	int i=0;
	if(initdone == 0)
		return -1;

	for(i=0;i<LEDANZ;i++)
		myledstring.channel [0].leds[i] = 0x200000;

	if(ws2811_render(&myledstring))
		return -1;
	
	return 0;
}

int setLEDsG(){
	int i=0;
	if(initdone == 0)
		return -1;

	for(i=0;i<LEDANZ;i++)
		myledstring.channel [0].leds[i] = 0x2000;

	if(ws2811_render(&myledstring))
		return -1;
	
	return 0;
}

int setLEDsB(){
	int i=0;
	if(initdone == 0)
		return -1;

	for(i=0;i<LEDANZ;i++)
		myledstring.channel [0].leds[i] = 0x20;

	if(ws2811_render(&myledstring))
		return -1;
	
	return 0;
}

int setLEDsW(){
	int i=0;
	if(initdone == 0)
		return -1;

	for(i=0;i<LEDANZ;i++)
		myledstring.channel [0].leds[i] = 0x2F2F2F;

	if(ws2811_render(&myledstring))
		return -1;
	
	return 0;
}
