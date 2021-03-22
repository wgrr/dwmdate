/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
	/* unreachable */

	XCloseDisplay(dpy);
	return 0;
}
