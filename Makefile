CFLAGS = 	`pkg-config --cflags gtk+-3.0`
LIBS = 		`pkg-config --libs gtk+-3.0`
OBJS = 		shi.o window.o
OUT = 		shi

example: $(OBJS)
	g++ -o$(OUT) $(OBJS) $(CFLAGS) $(LIBS)

shi.o: shi.cpp shi.h
	g++ -c $*.cpp $(CFLAGS) $(LIBS) -g3

window.o: window.cpp window.h
	g++ -c $*.cpp $(CFLAGS) $(LIBS) -g3

clean:
	rm -f $(OBJS) $(OUT)
