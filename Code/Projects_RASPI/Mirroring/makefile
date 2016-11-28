	
makefile: mirroringPI.c waitPeriod.c spi_pi.c data.c print.c demoMirroring.c 
	gcc mirroringPI.c waitPeriod.c spi_pi.c data.c print.c demoMirroring.c -o demoMirroring -lpthread -lwiringPi -I /usr/include/linux/spi/ -I ./inc
