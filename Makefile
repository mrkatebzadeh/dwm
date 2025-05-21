# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include wm/config.mk

WM_SRC = $(wildcard wm/*.c)
WM_OBJ = $(patsubst wm/%.c, build/%.o, $(WM_SRC))

all: bin/dwm bin/dwmblocks

.c.o:
	${CC} -c ${CFLAGS} $<

${WM_OBJ}: wm/config.h wm/config.mk

bin/dwm: $(WM_OBJ) | bin
	$(CC) -o $@ $^ $(LDFLAGS)

build/%.o: wm/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@


BAR_SRC = $(wildcard bar/*.c)
BAR_OBJ = $(patsubst bar/%.c, build/%.o, $(BAR_SRC))

${BAR_OBJ}: bar/config.h

bin/dwmblocks: $(BAR_OBJ) | bin
	$(CC) -o $@ $^ $(LDFLAGS)

build/%.o: bar/%.c | build
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
