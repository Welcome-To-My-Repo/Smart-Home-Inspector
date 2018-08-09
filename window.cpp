#include <X11/Xlib.h>
#include <unistd.h>

int OpenSplashWdw ()

{

	return 0;

}

int OpenMainWdw ()

{

	Display *dpy = XOpenDisplay(0);
	if (dpy == 0)
		return 1;

	int black = BlackPixel (dpy, DefaultScreen(dpy));
	int white = WhitePixel (dpy, DefaultScreen(dpy));

	Window mainWdw = XCreateSimpleWindow (dpy, DefaultRootWindow(dpy), 0, 0, 700, 500, 0, black, black);	//create the window
	XSelectInput (dpy, mainWdw, StructureNotifyMask);	//get MapNotify events
	XMapWindow (dpy, mainWdw);				//Map the window (make it appear)
	GC graphics = XCreateGC (dpy, mainWdw, 0, 0);		//create a graphics context

	XSetForeground (dpy, graphics, white);		//tell the graphics context
							//we draw using the white color
	//wait for the MapNotify event
	for (;;)

	{

		XEvent a;
		XNextEvent (dpy, &a);
		if (a.type == MapNotify)
			break;

	}

	XDrawLine (dpy, mainWdw, graphics, 10, 60, 180, 20);	//draw the line
	XFlush (dpy);						//sent request to server

	sleep (2);

	return 0;

}
