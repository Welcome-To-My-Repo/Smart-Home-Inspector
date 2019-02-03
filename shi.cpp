#include "shi.h"

int main (int argc, char **argv)

{

	//all the other functions of SHI explode out from calling
	//splashscreen
	//splashscreen ();
	mainwindow();

	return 0;

}

smart_dev::smart_dev ()
{
}

smart_dev::~smart_dev ()
{
}

void smart_dev::add_event ()
{
	event_types ++;
	events.push_back (event (event_types));
}
