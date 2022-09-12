#include <stdlib.h>
#include <X11/Xlib.h>
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
	i32 glx_Framebuffer_attributes[] = {GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT, GLX_RENDER_TYPE, GLX_RGBA_BIT, GLX_DOUBLEBUFFER, True, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, None};

	/////////////////////////////////////////////////////////////////////////////////////
	/* COMBINE THE X11 SERVER CONNECTION WITH THE GLX EXTENSION THROUGH THE X11_VISUAL */
	i32 value;
	glx_Framebuffer_config = glXChooseFBConfig(x11_Display, DefaultScreen(x11_Display), glx_Framebuffer_attributes, &value);
	x11_VisualInfo = glXGetVisualFromFBConfig(x11_Display, glx_Framebuffer_config[0]);

	////////////////////////////
	/* CREATION OF THE WINDOW */
	x11_WindowAttributes.border_pixel = 0;
	x11_WindowAttributes.colormap = XCreateColormap(
			x11_Display,
			RootWindow(x11_Display, x11_VisualInfo -> screen),
			x11_VisualInfo -> visual,
			AllocNone);
	x11_WindowAttributesMask = CWBorderPixel|CWEventMask|CWColormap;
	x11_Window = XCreateWindow(x11_Display, x11_RootWindow = XRootWindow(x11_Display, x11_Screen), 100, 100, CANVAS_WIDTH, CANVAS_HEIGHT, 0,
			x11_VisualInfo -> depth, InputOutput, x11_VisualInfo -> visual, x11_WindowAttributesMask, &x11_WindowAttributes);
	XMapWindow(x11_Display, x11_Window);

	////////////////////////////////////
	/* CREATION OF THE OPENGL CONTEXT */
	glx_Context = glXCreateNewContext(x11_Display, glx_Framebuffer_config[0], GLX_RGBA_TYPE, NULL, True);
	glx_Window = glXCreateWindow(x11_Display, glx_Framebuffer_config[0], x11_Window, NULL);
	glXMakeContextCurrent(x11_Display, x11_Window, glx_Window, glx_Context); 
	glEnable(GL_DEPTH_TEST);
	
	XSelectInput(x11_Display, x11_Window, ExposureMask | KeyPressMask);

	///////////////
	/* GAME LOOP */
	while (1) {
		XNextEvent(x11_Display, &x11_Event);
		if (x11_Event.type == Expose) {
			glViewport(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
			glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
			float V[3][3] =
			{
				{-0.5, +0.0, +0.0},
				{+0.5, +0.0, +0.0},
				{+0.0, +0.5, +0.0}
			};
			glBegin(GL_TRIANGLES);
				glVertex3fv(V[0]);
				glVertex3fv(V[1]);
				glVertex3fv(V[2]);
			glEnd();
			glXSwapBuffers(x11_Display, x11_Window);
		}
		/* COMMANDS FOR CLOSING THE GAME */
		if (x11_Event.type == KeyPress) {
			XDestroyWindow(x11_Display, x11_Window);
			XCloseDisplay(x11_Display);
			break;
		}
	}
	return 0;
}
