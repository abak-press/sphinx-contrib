include ../Makefile.inc

PLUGIN_NAME = random_float
CFLAGS = -fPIC -shared
CC ?= gcc

.PHONY: all install

all: plugins/$(PLUGIN_NAME)

plugins/$(PLUGIN_NAME): $(PLUGIN_NAME).c
		$(CC) $(CFLAGS) -o ./$(PLUGIN_NAME).so ./$(PLUGIN_NAME).c

install:
	mkdir -p $(DESTDIR)$(PREFIX)$(LIB_SPHINX_DIR)/
	install -pm 755 $(PLUGIN_NAME).so $(DESTDIR)$(PREFIX)$(LIB_SPHINX_DIR)/

uninstall:
	rm -f $(DESTDIR)$(PREFIX)$(LIB_SPHINX_DIR)/$(PLUGIN_NAME).so

clean:
	rm -f ./$(PLUGIN_NAME).so
