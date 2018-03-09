objs = main.o hub_protocols.o device_types.o display_functs.o

Watchdog: $(objs)
	g++ -owatchdog $(objs)

main.o: hub_protocols.h device_types.h display_functs.h

hub_protocols.o: hub_protocols.cpp hub_protocols.h

device_types.o: device_types.cpp device_types.h

display_functs.o: display_functs.cpp display_functs.h

clean: 
	rm $(objs)

install:
	mv watchdog /usr/local/bin
	rm $(objs)
