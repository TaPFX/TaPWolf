#include "wolfFX.h"

int wolfStart(){
	int i;
	int num,c;
	int color[3] = {0xFF0000,0x00FF00,0x0000FF};
	int anzLED;
	int sizeofcolor;

	initLEDs(10);
	anzLED = 10;
	sizeofcolor = 3;

	//Augenpaare aktivieren
	for(i=0;i<anzLED;i=i+2){
		c = rand() % sizeofcolor;
//		setLED(i, color[c]);
		printf("setLED(%d,%d)=%d\n",i,c,setLED(i,color[c]));
		usleep(1000);
//		setLED(i+1, color[c]);
		printf("setLED(%d,%d)=%d\n",i+1,c,setLED(i+1,color[c]));
		usleep(1000);
		printf("num=%d, c=%d\n", num, c);

	}

	usleep(10000000);

	//Augenpaare blinzeln
	for(i=0;i<10;i++){
		num = rand() % (anzLED-1);
				
		if(num % 2 != 0){
			num++;
		}
		
		setLED(num, 0);
		setLED(num+1, 0);
		
		printf("num=%d\n",num);
		usleep(2000000);
	}
	ws2811_fini(&myledstring);
	return 0;
}
