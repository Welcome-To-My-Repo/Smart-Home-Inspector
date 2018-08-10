watchdog: watchdog.o window.o
	@echo compiling...
	@g++ -owatchdog watchdog.o window.o -lX11 -lxcb -Wall -O3

watchdog.o: watchdog.h watchdog.cpp
window.o: window.h window.cpp

clean:
	@echo removing...
	@rm -f $(objs) watchdog

install:
	@echo installing...
	@mv watchdog /usr/local/bin
	@rm $(objs)
