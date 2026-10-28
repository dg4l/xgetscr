#include <stdio.h>
#include <stdbool.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xinerama.h>

bool in_x(int x, XineramaScreenInfo* cs) {
    return x >= cs->x_org && x < cs->x_org + cs->width;
}

bool in_y(int y, XineramaScreenInfo* cs) {
    return y >= cs->y_org && y < cs->y_org + cs->height;
}

bool in_screen_bounds(int x, int y, XineramaScreenInfo* cs) {
    return (in_x(x, cs) && in_y(y, cs));
}

int main(void) {
    Display* dpy = XOpenDisplay(NULL);
    if (!dpy) return 1;
    Window root, child;
    int rx, ry, wx, wy;
    unsigned int mr;
    XQueryPointer(dpy, DefaultRootWindow(dpy), &root, &child, &rx, &ry, &wx, &wy, &mr);
    int nscreens;
    XineramaScreenInfo* screens = XineramaQueryScreens(dpy, &nscreens);
    for (int i = 0; i < nscreens; ++i) {
        if (in_screen_bounds(rx, ry, &screens[i])) printf("%d\n", screens[i].screen_number);
    }
    XFree(screens);
    XCloseDisplay(dpy);
    return 0;
}
