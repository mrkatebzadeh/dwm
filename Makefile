# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include wm/config.mk

SRC = $(wildcard wm/*.c)
OBJ = $(patsubst wm/%.c, build/%.o, $(SRC))

all: bin/dwm

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: wm/config.h wm/config.mk

bin/dwm: $(OBJ) | bin
	$(CC) -o $@ $^ $(LDFLAGS)

build/%.o: wm/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build bin

build:
	mkdir -p build

bin:
	mkdir -p bin

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	install -Dm755 bin/* scripts/* ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < wm/dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1
	mkdir -p ${DESTDIR}${PREFIX}/share/dwm

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm*\
		${DESTDIR}${MANPREFIX}/man1/dwm.1

.PHONY: all clean install uninstall
