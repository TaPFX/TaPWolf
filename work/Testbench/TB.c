#include "TB.h"

extern char *optarg;

int main(int argc,char* argv[]){
	char *result;
	int debug = 0;
	int anz;
	int num, rgb, brt;
	char opt;

	while ((opt = getopt(argc, argv, "e:s:a:w")) != -1) {
		switch (opt) {
		case 'e':
			if(optarg != NULL){
				
				result = strtok(optarg,",");
	 			if(result != NULL)
					debug = atoi(result);
				
				result = strtok(NULL,",");	
				if(result != NULL)
					Sleep = atoi(result);
				
				result = strtok(NULL,",");	
				if(result != NULL)
					anz = atoi(result);
				
				printf("---Start TB---\n");
				tbledString(debug, anz);
				printf("---End TB---\n");
			}
			return 0;
			break;
		case 's':
			if(optarg != NULL){
				result = strtok(optarg,",");
	 			if(result != NULL)
					num = atoi(result);
				result = strtok(NULL,",");
	 			if(result != NULL)
					rgb =(int)strtol(result, NULL, 16);
				result = strtok(NULL,",");
	 			if(result != NULL)
					brt = atoi(result);
			}
			
			initLEDs(48);
			printf("setLED(%d,%d)= %d\n",num,rgb,setLED(num, rgb));
			printf("setBrightness(%d)= %d\n",brt,setBrightness(brt));
			
			return 0;
			break;		
		case 'a':
			if(optarg != NULL){
				result = strtok(optarg,",");
	 			if(result != NULL)
					rgb =(int)strtol(result, NULL, 16);
				
				result = strtok(NULL,",");
	 			if(result != NULL)
					brt = atoi(result);
			}
			
			initLEDs(48);
			printf("setLEDs(%d)= %d\n",rgb,setLEDs(rgb));
			printf("setBrightness(%d)= %d\n",brt,setBrightness(brt));
			
			return 0;
			break;	
		case 'w':
			wolfStart();
			return 0;
			break;
		default: /* '?' */
			printf("Usage: %s [-e] debug(0,1),Sleep(usec),anz(stringsize)  [-s] lednum,rgb(inHEx),brightness \n", argv[0]);
			return -2;
  	}
	}

	return 0;
}
