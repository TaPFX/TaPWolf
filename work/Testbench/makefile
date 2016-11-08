all: TB.o

TB.o: TB.c tbledString.c ../ledString.c ../wolfFX.c ../ws2811/ws2811.c ../ws2811/dma.c ../ws2811/rpihw.c ../ws2811/mailbox.c ../ws2811/pwm.c
	gcc TB.c tbledString.c ../ledString.c ../wolfFX.c ../ws2811/ws2811.c ../ws2811/dma.c ../ws2811/rpihw.c ../ws2811/mailbox.c ../ws2811/pwm.c -o tb
