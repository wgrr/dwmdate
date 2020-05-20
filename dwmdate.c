#define _POSIX_C_SOURCE 200809L

#include <locale.h>
#include <stdio.h>
#include <time.h>

#include <X11/Xlib.h>


static const struct timespec sleeptime = {.tv_sec = 2, .tv_nsec = 0};
static char rootname[512];
static int die(const char *);

static int
die(const char *msg)
{
	fprintf(stderr, "dwmdate: %s\n", msg);
	return 1;
}

int
main(void)
{
	Display *dpy;
	int screen, n;
	Window root;
	time_t t;
	struct tm *local, *utc;

	setlocale(LC_ALL, "");

	dpy = XOpenDisplay(NULL);
	if (dpy == NULL)
		return die("fatal: cannot open display");

	screen = DefaultScreen(dpy);
	root = RootWindow(dpy, screen);

	for (;;) {
		time(&t);
		local = localtime(&t);
		n = strftime(rootname, sizeof rootname, "%a %d %b %Y %T %Z | ", local);

		utc = gmtime(&t);
		strftime(rootname + n, sizeof rootname, "%a %d %b %Y %T %Z", utc);
		
		XStoreName(dpy, root, rootname);
		XFlush(dpy);
		nanosleep(&sleeptime, NULL);
	}

	XCloseDisplay(dpy);
	return 0;
}
