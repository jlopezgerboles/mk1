#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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

int main(void) {
	Display *display;
	Window window, root_window;
	XEvent event;
	const char *msg = "Hello, World!";
	int screen;
	
	display = XOpenDisplay(NULL);
	screen = DefaultScreen(display);
	
	//THIS WORKS AND HAS BEEN PROVED
	XSetWindowAttributes att;
	att.background_pixel = 0x0000ff;
	window = XCreateWindow(
			display,
			RootWindow(display, screen),
			100,
			100,
			RESOLUTION_WIDTH*2, // Multiplying here by 2 does not increate the size of the pixels. TODO
			RESOLUTION_HEIGHT*2, // Multiplying here by 2 does not increate the size of the pixels. TODO
			0,
			CopyFromParent,
			InputOutput,
			CopyFromParent,
			CWBackPixel,
			&att
			);
	
	GC gc;
	XGCValues values;
	values.function = GXcopy;
	values.foreground = 0x00ffff;
	values.background = 1;
	values.line_width = 3;
	values.line_style = LineSolid;
	values.cap_style = CapButt;
	values.join_style = JoinMiter;
	values.fill_style = FillSolid;
	values.fill_rule = EvenOddRule;
	values.arc_mode = ArcPieSlice;
	values.ts_x_origin = 0;
	values.ts_y_origin = 0;
	values.subwindow_mode = ClipByChildren;
	values.graphics_exposures = True;
	values.clip_x_origin = 0;
	values.clip_y_origin = 0;
	values.clip_mask = None;
	values.dash_offset = 0;
	values.dashes = 4;
	gc = XCreateGC(
			display,
			window,
			GCFunction|GCForeground|GCBackground|GCLineWidth|GCLineStyle|GCCapStyle|GCJoinStyle|GCFillStyle|GCFillRule|
			GCTileStipXOrigin|GCTileStipYOrigin|GCSubwindowMode|GCGraphicsExposures|GCClipXOrigin|GCClipYOrigin|GCClipMask|
			GCDashOffset|GCDashList|GCArcMode,
			&values
			);

	XSelectInput(display, window, ExposureMask | KeyPressMask);
	
	XMapWindow(display, window);

	
	while (1) {
		XNextEvent(display, &event);
		if (event.type == Expose) {
			XFillRectangle(display, window, gc, 0, 0, 64, 64);
			
			i16 i;
			i16 Px[4], Py[4];
			for (i=0; i <= RESOLUTION_WIDTH; i++) {
				XDrawLine(display, window, gc, i*64, 0, i*64, RESOLUTION_HEIGHT*2); // Notice the dimensions of the width and height should not be edited here.		
				XDrawLine(display, window, gc, 0, i*64, RESOLUTION_WIDTH*2, i*64); // Notice the dimensions of the width and height should not be edited here.
			}

			//XDrawString(display, window, DefaultGC(display, screen), 10, 50, msg, strlen(msg)); // Notice the text pops on top of the square.
			//XDrawLine(display, window, gc, 64, 0, 64, 448);
			//XDrawLine(display, window, gc, 0, 64, 512, 64); // To implement all the lines in the canvas. TODO
		}
		if (event.type == KeyPress)
			break;
	}
	XFreeGC(display, gc);
	XCloseDisplay(display);
	return 0;
}
	// THIS WORKS AND HAS BEEN PROVED








/* DEFINE THE COORDINATES OF THE TILES IN THE GAME WINDOW */

#define BACKGROUND_TILESET_WIDTH 16
#define BACKGROUND_TILESET_HEIGHT 16

/*
 * simple-drawing.c - demonstrate drawing of pixels, lines, arcs, etc.
 *                    on a window. All drawings are done in black color
 *                    over a white background.
 */
/*
#include <X11/Xlib.h>


static u8 background_bitmap[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff,
	0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

Drawable create_canvas(Display* display, i16 width, i16 height, i16 x, i16 y) {
	i8 screen = DefaultScreen(display);
	Drawable window, root_window;
	root_window = RootWindow(display, screen);

	window = XCreateSimpleWindow(display, root_window, x, y, width, height, 0, BlackPixel(display, screen), WhitePixel(display, screen));
	
	XMapWindow(display, window);
	XFlush(display);

	return window;
	}

GC create_GC(Display* display, Drawable window) {
	GC gc;
	XGCValues values;
	gc = XCreateGC(display, window, 0, NULL);
	i8 screen = DefaultScreen(display);

	XSetForeground(display, gc, BlackPixel(display, screen));
	XSetBackground(display, gc, WhitePixel(display, screen));
	
	XSetLineAttributes(display, gc, 0, LineSolid, CapButt, JoinBevel);

	return gc;
}

void main(i32 argc, i8* argv[]) {

	INITIALIZATION OF THE X WINDOW VARIABLES
	Display *display;
	i32 screen;
	i32 display_width, display_height, width, height;
	Drawable window;
	GC gc;

	display	= XOpenDisplay(NULL);
	screen = DefaultScreen(display);
	display_width = DisplayWidth(display, screen);
	display_height = DisplayHeight(display, screen);
	width = (display_width/3);
	height = (display_height/3);

	window = create_canvas(display, width, height, 0, 0);
	gc = create_GC(display, window);
	XSync(display, False);

	XDrawPoint(display, window, gc, 5, 5);

	XFlush(display);
	XSync(display, False);

	sleep(10);

	XCloseDisplay(display);
}

	LOAD THE BACKGROUND TILES FROM BACKGROUND BITMAP
	Pixmap background = XCreatePixmapFromBitmapData(
				display,
				win_root,
				background_bitmap,
				16,
				16,
				BlackPixel(display, screen),
				WhitePixel(display, screen),
				DefaultDepth(display, screen)
				);

	// DEFINITION OF THE X WINDOW VARIABLES FOR GRAPHICAL CONTEXT //
	gcv.background = WhitePixel(display, screen);
	gcv.foreground = BlackPixel(display, screen);
	gc = XCreateGC(display, DefaultRootWindow(display),GCForeground|GCBackground,&gcv);

	// CREATION OF THE ACTUAL GAME WINDOW // 
	//XSetWindowAttributes att;
	//att.background_pixel = 0x0000ff;
	//att.background_pixmap = background;

	Drawable window = XCreateSimpleWindow(
				display,
				win_root,
				100,
				100,
				300,
				300,
				1,
				0x000000,
				0x0000ff
				//DefaultDepth(display, screen),
				//InputOutput,
				//CopyFromParent,
				//CWBackPixmap|CWBackPixel,
				//&att
				);

	//XSelectInput(display, window, ExposureMask|KeyPressMask);


	// CREATE THE GRAPHICAL CONTEXT OF THE GAME WINDOW //
	
	// DRAW IN THE GAME WINDOW //
	//XDrawLine(display, window, gc, 16, 0, 16, 300);
	//XDrawPoint(display, window, gc, 5, 5);

	// DRAW THE CONTENT OF THE BACKGROUND TILEMAP IN THE GAME WINDOW //
	XDrawRectangle(display, window, gc, 120, 120, 50, 50);
	XPoint points[] = {
		{  0,   0}, { 16,   0}, { 32,   0},
		{ 16,   0}, { 16,  16},
		{ 32,   0}
	};
	i64 npoints = sizeof(points)/sizeof(XPoint);
	XDrawLines(display, window, gc, points, npoints,  CoordModeOrigin);

	// MAP THE WINDOW IN THE DISPLAY //
	
	//XMapRaised(display, window);


	XMapWindow(display, window);
	
	XEvent event;
	
	while (1) {
		XNextEvent(display, &event);
		if (event.type == Expose) {

			XFillRectangle(display, window, DefaultGC(display, screen), 20, 20, 10, 10);
			XDrawLine(display, window, gc, 300, 300, 360, 360);
			//XFillRectangle(display, window, gc, 16, 16, 128, 128); 
			}
		if (event.type != KeyPress) {
			break;
		}
	XFlush(display);
	}
	 FINALIZATION OF THE X WINDOW SERVER
	//XFreeGC(display, gc);
	XUnmapWindow(display, window);
	XDestroyWindow(display, window);
	//XFreePixmap(display, background);
	XCloseDisplay(display);
	return 0;
}
*/
