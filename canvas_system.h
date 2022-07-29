#include <X11/Xlib.h>

typedef struct canvas_framework {
	Display *display;
	Window window;
	XEvent event;
	u32 screen;
} canvas_framework;

i8 canvas_system_initialize(void* game_canvas);
void canvas_system_shutdown(void* canvas_framework);
