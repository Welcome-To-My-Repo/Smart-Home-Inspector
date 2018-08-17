OBJS = 		shi.o window.o
NAME = 		shi
CFLAGS = 	`pkg-config --cflags gtk+-3.0`
LIBS = 		`pkg-config --libs gtk+-3.0`

shi: $(OBJS)
	g++ -o$(NAME) $(OBJS) $(ALLFLAGS)

shi.o: shi.cpp shi.h
	g++ -c $*.cpp $(CFLAGS) $(LIBS)

window.o: window.cpp window.h
	g++ -c $*.cpp $(CFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) $(OUT)

install: shi
	mv $(OUT) /usr/local/bin
	rm -f $(OBJS)
