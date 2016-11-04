#include "TB.h"
#include "../ledString.h"
#define SIZESETLEDVAL2D 2

int tbledString(int debug, int anz){
	int i = 0;
	ErrCNT = 0;
	signed char retinitLEDs, retsetLED, retsetLEDsR,  retsetLEDsG, retsetLEDsB, retsetLEDsW;
	
	// Array[erwartungswert][funktVariablen 0]..[funktVariablen n]
	signed char setLEDVal[][SIZESETLEDVAL2D] =	{{0,1},
											{0,2},
											{0,3},
											{0,4},
											{-2,0},
											{-2,5},
											{-2,-1}, };
											
	
	printf("---Testing LEDString---,\n");
	
	if(init == 0){
		init = 1;
		retinitLEDs = initLEDs(anz);
		if(retinitLEDs != 0){
			printf("ERROR  %d initLEDs(48) faild\n",retinitLEDs);
			ErrCNT++;
			return -1; }
		else if(debug){	printf("PASSED %d initLEDs(0)\n",retinitLEDs); usleep(Sleep);}
	}
	
	retsetLEDsR = setLEDsR();
	if(retsetLEDsR != 0){
		printf("ERROR  %d setLEDsR() faild\n",retsetLEDsR);
		ErrCNT++;
		return -1; }
	else if(debug){	printf("PASSED %d setLEDsR()\n",retsetLEDsR); usleep(Sleep);}
	
	retsetLEDsG = setLEDsG();
	if(retsetLEDsG != 0){
		printf("ERROR  %d setLEDsG() faild\n",retsetLEDsG);
		ErrCNT++;
		return -1; }
	else if(debug){	printf("PASSED %d setLEDsG()\n",retsetLEDsG); usleep(Sleep);}

	retsetLEDsB = setLEDsB();
	if(retsetLEDsB != 0){
		printf("ERROR  %d setLEDsB() faild\n",retsetLEDsB);
		ErrCNT++;
		return -1; }
	else if(debug){	printf("PASSED %d setLEDsB()\n",retsetLEDsB); usleep(Sleep);}

	retsetLEDsW = setLEDsW();
	if(retsetLEDsW != 0){
		printf("ERROR  %d setLEDsW() faild\n",retsetLEDsW);
		ErrCNT++;
		return -1; }
	else if(debug){	printf("PASSED %d setLEDsW()\n",retsetLEDsW); usleep(Sleep);}
	
	setLEDsOFF();

	for(i=0;i<anz;i++){
		setLED(i,0x2F2F2F,50);
		usleep(Sleep);
	}

	
/*	
	for(i=0;i<sizeof(setLEDVal)/SIZEMOFFVAL2D;i++){
		retmagnetOFF = magnetOFF(mOFFVal[i][1]);
		if(retmagnetOFF != mOFFVal[i][0]){
			printf("ERROR  %d magnetOFF(%d) faild\n",retmagnetOFF,mOFFVal[i][1]);
			ErrCNT++; }
		else if(debug){ 
			printf("PASSED %d magnetOFF(%d)\n",retmagnetOFF,mOFFVal[i][1]);
			usleep(Sleep);}
		if(printBuff) printSPIBuff();
	}
*/

	if(ErrCNT == 0)
		printf("PASSED ledString\n");
	else{
		printf("ERROR ledString faild\n");
		return -1;}
	
	return 0;
}
