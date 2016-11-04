all: test.o

test.o: TaPWolf.c ws2811.c dma.c rpihw.c mailbox.c pwm.c
	gcc test.c ws2811.c dma.c rpihw.c mailbox.c pwm.c -o mytest		
