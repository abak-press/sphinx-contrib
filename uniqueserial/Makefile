include ../Makefile.inc

SPH_UDF_VERSION ?= 9
PLUGIN_NAME = uniqueserial
CFLAGS = -fPIC -shared -Wall -std=c++11 -D'SPH_UDF_VERSION=$(SPH_UDF_VERSION)'
CC ?= gcc

.PHONY: all install

all: plugins/$(PLUGIN_NAME)

plugins/$(PLUGIN_NAME): src/$(PLUGIN_NAME).cpp
		$(CC) $(CFLAGS) -o ./$(PLUGIN_NAME).so ./src/$(PLUGIN_NAME).cpp

install:
	mkdir -p $(DESTDIR)$(PREFIX)$(LIB_SPHINX_DIR)/
	install -pm 755 $(PLUGIN_NAME).so $(DESTDIR)$(PREFIX)$(LIB_SPHINX_DIR)/

uninstall:
	rm -f $(DESTDIR)$(PREFIX)$(LIB_SPHINX_DIR)/$(PLUGIN_NAME).so

clean:
	rm -f ./$(PLUGIN_NAME).so
