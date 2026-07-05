#include <stdio.h>
#include <stdbool.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xinerama.h>

bool in_screen_bounds(int x, int y, XineramaScreenInfo* cs) {
    if (x >= cs->x_org && x < cs->x_org + cs->width
            && y >= cs->y_org && y < cs->y_org + cs->height) return true;
    return false;
}

int main(void) {
    Display* dpy = XOpenDisplay(NULL);
    if (!dpy) return 1;
    int scr = DefaultScreen(dpy);
    Window root = RootWindow(dpy, scr);
    Window focused = NULL;
    int rev;
    XGetInputFocus(dpy, &focused, &rev);
    if (focused == None) focused = root;
    XWindowAttributes a;
    XGetWindowAttributes(dpy, focused, &a);
    int rx, ry, wx, wy;
    unsigned int mr;
    int nscreens;
    XineramaScreenInfo* screens = XineramaQueryScreens(dpy, &nscreens);
    if (!screens) return 1;
    XQueryPointer(dpy, focused, &root, &root, &rx, &ry, &wx, &wy, &mr);
    for (int i = 0; i < nscreens; ++i) {
        XineramaScreenInfo cs = screens[i]; 
        if (in_screen_bounds(rx, ry, &cs)) printf("%d\n", cs.screen_number);
    }
    XFree(screens);
    XCloseDisplay(dpy);
    return 0;
}
