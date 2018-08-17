#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

#include "shi.h"

int main (int argc, char **argv)

{

	splashscreen a;
	splash (a);
	sleep (3);
	quitsplash (a);

	return 0;

}
