objs = shi.o window.o
watchdog: $(objs)
	@echo compiling...
	@g++ -owatchdog $(objs) `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0`

shi.o: shi.h shi.cpp
window.o: window.h window.cpp

clean:
	@echo removing...
	@rm -f $(objs) watchdog

install:
	@echo installing...
	@mv watchdog /usr/local/bin
	@rm $(objs)
