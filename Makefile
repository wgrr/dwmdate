SRC = dwmdate.c
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -std=c99 -pedantic -O3 -march=native -mtune=native 
LDFLAGS = -flto

PREFIX = /usr/local

all: dwmdate

${OBJ}: ${SRC}
	${CC} -c ${CFLAGS} $<

dwmdate: ${OBJ}
	${CC} -o $@ ${LDFLAGS} $^ -lX11

clean:
	rm -f ${OBJ} dwmdate

install: all
	mkdir -p ${PREFIX}/bin
	cp -f dwmdate ${PREFIX}/bin/dwmdate
	chmod 755 ${PREFIX}/bin/dwmdate

uninstall:
	rm -f ${PREFIX}/bin/dwmdate

.PHONY: all clean install uninstall

