objs = shi.o window.o
watchdog: $(objs)
	@echo compiling...
	@g++ -owatchdog $(objs) -lX11 -lxcb -Wall -O3

shi.o: shi.h shi.cpp
window.o: window.h window.cpp

clean:
	@echo removing...
	@rm -f $(objs) watchdog

install:
	@echo installing...
	@mv watchdog /usr/local/bin
	@rm $(objs)
