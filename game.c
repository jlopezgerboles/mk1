#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>

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
#define CANVAS_WIDTH RESOLUTION_WIDTH*2
#define CANVAS_HEIGHT RESOLUTION_HEIGHT*2

int main(void) {
	
	/////////////////////////////////////
	/* DECALRE & DEFINE X11 PARAMETERS */
	
	Display *x11_Display = XOpenDisplay(NULL);
	Drawable x11_Window;
	Drawable x11_RootWindow;
	i8 x11_Screen = DefaultScreen(x11_Display);
	XSetWindowAttributes x11_WindowAttributes;
	i64 x11_WindowAttributesMask;
	XVisualInfo *x11_VisualInfo;
	XEvent x11_Event;

	///////////////////////////////////////
	/* DECLARE AND DEFINE GLX PARAMETERS */

	GLXContext glx_Context;
	GLXFBConfig *glx_Framebuffer_config; 
	GLXWindow glx_Window;

	GLint glx_Framebuffer_attributes[] = {GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT, GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_DOUBLEBUFFER, True, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, None};

	///////////////////////////////
	/* CREATE THE GAME INTERFACE */
	
	i32 value;
	glx_Framebuffer_config = glXChooseFBConfig(x11_Display, DefaultScreen(x11_Display), glx_Framebuffer_attributes, &value);
	
	x11_VisualInfo = glXGetVisualFromFBConfig(x11_Display, glx_Framebuffer_config[0]);

	x11_WindowAttributes.border_pixel = 0;
	x11_WindowAttributes.colormap = XCreateColormap(
			x11_Display,
			RootWindow(x11_Display, x11_VisualInfo -> screen),
			x11_VisualInfo -> visual,
			AllocNone);

	x11_WindowAttributes.event_mask = StructureNotifyMask;
	x11_WindowAttributesMask = CWBorderPixel|CWEventMask|CWColormap;
	
	x11_Window = XCreateWindow(x11_Display, x11_RootWindow = XRootWindow(x11_Display, x11_Screen), 100, 100, CANVAS_WIDTH, CANVAS_HEIGHT, 0,
			x11_VisualInfo -> depth, InputOutput, x11_VisualInfo -> visual, x11_WindowAttributesMask, &x11_WindowAttributes);
	
	XMapWindow(x11_Display, x11_Window);
	
	glx_Context = glXCreateNewContext(x11_Display, glx_Framebuffer_config[0], GLX_RGBA_TYPE, NULL, True);
	glx_Window = glXCreateWindow(x11_Display, glx_Framebuffer_config[0], x11_Window, NULL);
	glXMakeContextCurrent(x11_Display, x11_Window, glx_Window, glx_Context); 

	glEnable(GL_DEPTH_TEST);
	
	XSelectInput(x11_Display, x11_Window, ExposureMask | KeyPressMask); // I missed to define the input mask.
	
	while (1) {
		XNextEvent(x11_Display, &x11_Event);

		if (x11_Event.type == Expose) {

			XGetWindowAttributes(x11_Display, x11_Window, &x11_WindowAttributes);
			glViewport(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
			glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
			
			glBegin(GL_LINE_LOOP);
			glVertex3f(0.0f, 0.0f, 1.5f);
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);

			//glBegin(GL_LINES);
			//glVertex3f(-1.0f, -1.0f, -1.0f);
			//glVertex3f(1.0f, 1.0f, 1.0f);

			glEnd();

			glXSwapBuffers(x11_Display, x11_Window);
		}

		if (x11_Event.type == KeyPress) {
			XDestroyWindow(x11_Display, x11_Window);
			XCloseDisplay(x11_Display);
			break;
		}
	}
}

	////////////////////////
	////////////////////////

	/////////////////////////////////////////
	/* FULL CREATION OF WINDOW THROUGH X11 */
	/*
	x11_WindowAttributes.background_pixel = 0x0000ff;
	x11_Window = XCreateWindow(
			x11_Display, x11_RootWindow = RootWindow(x11_Display, x11_Screen), 100, 100, 512, 448, 0, CopyFromParent, InputOutput,
			CopyFromParent,	CWBackPixel, &x11_WindowAttributes
	);

	XGCValues values;
	values.function = GXcopy;
	values.foreground = 0x00ffff;
	GC x11_GraphicContext = XCreateGC(x11_Display, x11_Window, GCFunction|GCForeground, &values);

	XMapWindow(x11_Display, x11_Window);

	GLXContext glx_context; yGLXFBConfig glx_framebuffer_config; 


	////////////////////////////////
	////////////////////////////////

	u8 msg[] = "Hola preciosa.";
	XEvent x11_Event;	

	*/
	/* LOOP OF THE SOFTWARE */
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
