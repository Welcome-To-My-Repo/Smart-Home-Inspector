################################################################################
BOOST_LOCATION = /usr/lib
#BOOST_LOCATION is a separate variable because boost might be different between
#different systems.
#"-L" looks in the shared library's containing directory and "-l" is the name of
#the shared library excepting the initial "lib..." and ".so"
################################################################################
FLAGS = 	`pkg-config --cflags gtk+-3.0 --libs gtk+-3.0` -std=gnu++17
LIBS = 		-L $(BOOST_LOCATION) -l boost_regex
OBJS = 		shi.o window.o func.o classes.o
OUT = 		shi
DBG =

default: shi
debug: DBG = -g3
debug: shi

shi: $(OBJS)
	g++ $(OBJS) $(LIBS) $(FLAGS) -o$(OUT)

shi.o: shi.cpp shi.h classes.h
	g++ -c $*.cpp $(FLAGS) $(DBG)

window.o: window.cpp shi.h classes.h
	g++ -c $*.cpp $(FLAGS) $(DBG)

func.o: func.cpp shi.h classes.h
	g++ -c $*.cpp $(FLAGS) $(DBG)

classes.o: classes.cpp classes.h shi.h
	g++ -c $*.cpp $(FLAGS) $(DBG)

clean:
	rm -f $(OBJS) $(OUT)

install: shi

	mkdir ~/.local/share/shi
	mv shi /usr/local/bin

test:
	./shi
