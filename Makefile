objs = shi.o window.o
shi: $(objs)
	@echo compiling...
	#@g++ -oshi $(objs) `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0`
	@g++ -oshi shi.cpp shi.h `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0`

shi.o: shi.h shi.cpp
window.o: window.h window.cpp

clean:
	@echo removing...
	@rm -f $(objs) shi

install:
	@echo installing...
	@mv shi /usr/local/bin
	@rm $(objs)
