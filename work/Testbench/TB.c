#include "TB.h"

int main(int argc,char* argv[]){
	int debug = 0;
	int anz;
	debug = atoi(argv[1]);
	Sleep = atoi(argv[2]);
	printBuff = atoi(argv[3]);
	anz = atoi(argv[4]);
	
	printf("---Start TB---\n");
	
	tbledString(debug, anz);
	
	printf("---End TB---\n");
	return 0;
}
