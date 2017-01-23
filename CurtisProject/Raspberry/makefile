	
makefile: mirroringPI.c waitPeriod.c spi_pi.c data_interface.c print.c demo_mirroring.c demo_sprint_5.c hdmapi.c create_threads.c framecheck.c

gcc API/API_main.c API/HDMAPI/mirroringPI.c API/waitPeriod.c API/HDMAPI/spi_pi.c API/data_interface.c API/HDMAPI/framecheck.c  API/HDMAPI/print.c  API/XPSAPI/queue.c API/HDMAPI/hdmapi.c API/XPSAPI/xpsapi.c API/XPSAPI/go_forward.c application_code.c API/create_threads.c -o demoSprint5 -lpthread -lwiringPi -I /usr/include/linux/spi/ -I ./API/sources


