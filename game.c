#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef signed char i8;
typedef signed short  i16;
typedef signed int i32;
typedef signed long i64;
typedef char b8;

#define TRUE 1
#define FALSE 0

#define RESOLUTION_WIDTH 512
#define RESOLUTION_HEIGHT 448

/* DEFINE THE COORDINATES OF THE TILES IN THE GAME WINDOW */

#define BACKGROUND_TILESET_WIDTH 16
#define BACKGROUND_TILESET_HEIGHT 16

static u8 background_bitmap[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff,
	0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

i8 main() {

	/* INITIALIZATION OF THE X WINDOW SERVER */
	Display *display = XOpenDisplay(NULL);
	i8 screen = DefaultScreen(display);
	
	/* LOAD THE BACKGROUND TILES FROM BACKGROUND BITMAP */
	/*Pixmap background = XCreatePixmapFromBitmapData(
				display,
				RootWindow(display, screen),
				background_bitmap,
				16,
				16,
				BlackPixel(display, screen),
				WhitePixel(display, screen),
				DefaultDepth(display, screen)
				);*/

	/* CREATION OF THE ACTUAL GAME WINDOW */
	XSetWindowAttributes att;
	att.background_pixel = 0x0000ff;
	/*att.background_pixmap = background;*/
	Window window = XCreateWindow(
				display,
				RootWindow(display,screen),
				RESOLUTION_WIDTH*0.25,
				RESOLUTION_HEIGHT*0.25,
				RESOLUTION_WIDTH*2,
				RESOLUTION_HEIGHT*2,
				0,
				DefaultDepth(display, screen),
				InputOutput,
				CopyFromParent,
				/*CWBackPixmap|*/CWBackPixel,
				&att
				);

	/* CREATE THE GRAPHICAL CONTEXT OF THE GAME WINDOW */
	i16 line_width = 3;
	XGCValues values;
        values.line_style = LineSolid;
	values.line_width = line_width;
	values.cap_style = CapButt;
	values.join_style = JoinBevel;
	values.fill_style = FillSolid;
	values.foreground = 0xff0000;
	/*values.background = 0xffffff;*/
	GC gc = XCreateGC(
			display,
			window,
			GCForeground|GCBackground|GCFillStyle|GCLineStyle|GCLineWidth|GCCapStyle|GCJoinStyle,
			&values
			);

	/* DRAW IN THE GAME WINDOW */
	/*XSetForeground(display, gc, BlackPixel(display, screen));
	XSetBackground(display, gc, WhitePixel(display, screen));
	XSetFillStyle(display, gc, FillSolid);
	XSetLineAttributes(display, gc, 2, LineSolid, CapRound, JoinRound);
	XDrawLine(display, window, gc, 16, 0, 16, 447);
	XDrawPoint(display, window, gc, 5, 5);*/

	u8 *msg = "Sabrina esta muy guapa!";
	XEvent event;

	/* DRAW THE CONTENT OF THE BACKGROUND TILEMAP IN THE GAME WINDOW */
	/*XDrawRectangle(display, window, gc, 120, 120, 50, 50);
	XPoint points[] = {
		{  0,   0}, { 16,   0}, { 32,   0},
		{ 16,   0}, { 16,  16},
		{ 32,   0}
	};
	i64 npoints = sizeof(points)/sizeof(XPoint);
	XDrawLines(display, window, gc, points, npoints,  CoordModeOrigin);
	*/
	/* MAP THE WINDOW IN THE DISPLAY */
	
	XMapWindow(display, window);
	XMapRaised(display, window);
	XFlush(display);
 
	while (1) {
		XNextEvent(display, &(event));
		if (event.type == Expose) {
			XDrawString(display, window, gc, 10, 50, msg, strlen(msg));
			XFillRectangle(display, window, gc, 16, 16, 128, 128); 
		}
		if (event.type == KeyPress)
			break;
	}

	/* FINALIZATION OF THE X WINDOW SERVER */
	XUnmapWindow(display, window);
	XDestroyWindow(display, window);
	/*XFreePixmap(display, background);*/
	XCloseDisplay(display);
	return 0;
}
