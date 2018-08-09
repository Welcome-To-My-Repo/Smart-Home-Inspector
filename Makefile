objs = watchdog.o window.o

Watchdog: $(objs)
	g++ -owatchdog $(objs)

watchdog.o: watchdog.cpp watchdog.h
window.o: window.cpp window.h

clean:
	rm $(objs)

install:
	mv watchdog /usr/local/bin
	rm $(objs)
