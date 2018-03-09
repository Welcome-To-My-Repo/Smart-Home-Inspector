#include <iostream>
#include <string>
#include <cstdlib>

#include "display_functs.h"
#include "device_types.h"
#include "hub_protocols.h"

int main ( int argv, char** argc )

{

	QApplication app ( argc, argv );

	QPushButton button ( "Hello world !" );
	button.show();

	return app.exec ();

}
