#include "standard.h"
#include "canvas_system.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


i8 main(void* game_canvas) {

	Display *display;
	Window window;
	XEvent event;
	u32 screen;

	u8 *msg = "Sabrina esta muy guapa!";

	/* CREATRION OF THE CANVAS DISPLAY */
	display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}

	/* CREATION OF THE CANVAS SCREEN */
	screen = DefaultScreen(display);

	/* CREATION OF THE CANVAS WINDOW */
	window = XCreateSimpleWindow(
			display,
			RootWindow(display, screen),
			10,
			10,
			100,
			100,
			1,
			BlackPixel(display, screen),
			WhitePixel(display, screen));

	/* XSelectInput(display, window, ExposureMask | KeyPressMask);*/
	XMapWindow(display, window);
 
	while (1) {
		XNextEvent(display, &(event));
		if (event.type == Expose) {
			XFillRectangle(display, window, DefaultGC(display, screen), 20, 20, 10, 10);
			XDrawString(display, window, DefaultGC(display, screen), 10, 50, msg, strlen(msg));
		}
		if (event.type == KeyPress)
			break;
	}

	XUnmapWindow(display, window);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
	return 0;
}
