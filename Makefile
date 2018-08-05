objs = watchdog.o

Watchdog: $(objs)
	g++ -owatchdog $(objs)

watchdog.o: watchdog.cpp watchdog.h

clean:
	rm $(objs)

install:
	mv watchdog /usr/local/bin
	rm $(objs)
