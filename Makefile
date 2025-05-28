SUBDIRS := wm bar menu

.PHONY: all clean install $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

install:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir install; \
	done


uninstall:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir uninstall; \
	done
