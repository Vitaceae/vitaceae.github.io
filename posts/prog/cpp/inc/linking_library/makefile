BIN_STATIC_LINK=static_linking
BIN_DYNA_LINK=dynamic_linking
BIN_DYNA_LOAD=dynamic_loading

DEBUG:=1

SO_SEARCH_PATH:=$(shell pwd)/so_path
INC_PATH:= -I. -I./include
LIB_PATH:= -L. -L$(SO_SEARCH_PATH)

CFLAGS:= -Wall -Wextra -pedantic -O3 --std=c99 $(INC_PATH)
ifeq ($(DEBUG),1)
CFLAGS+=$(FLAGS_COMMON) -g
endif

CC:=gcc
AR:=gcc-ar

.PHONY: clean all
all: clean static_linking dynamic_linking dynamic_loading

static_linking:
	@mkdir -p $(SO_SEARCH_PATH)
	@echo "make libdep_s.a"
	@$(CC) $(CFLAGS) -c -static dep3.c dep4.c
	@$(AR) rcs $(SO_SEARCH_PATH)/libdep_s.a dep3.o dep4.o
	@echo "make $(BIN_STATIC_LINK)"
	@$(CC) $(CFLAGS) static_linking.c $(LIB_PATH) -ldep_s -o $(BIN_STATIC_LINK)

dynamic_linking:
	@mkdir -p $(SO_SEARCH_PATH)
	@echo "make libdep2.so"
	@$(CC) $(CFLAGS) \
	       -fPIC -shared dep2.c \
	       -o $(SO_SEARCH_PATH)/libdep2.so
	@echo "make dep1.so.1.0"
	@$(CC) $(CFLAGS) $(LIB_PATH) -ldep2 \
	       -fPIC -shared -Wl,-rpath,`pwd`:$(SO_SEARCH_PATH) dep1.c \
	       -Wl,-soname,libdep1.so.1 \
	       -Xlinker --version-script dynamic_linking.lds \
	       -o $(SO_SEARCH_PATH)/libdep1.so.1.0
	@ln -s -r $(SO_SEARCH_PATH)/libdep1.so.1.0 $(SO_SEARCH_PATH)/libdep1.so.1
	@ln -s -r $(SO_SEARCH_PATH)/libdep1.so.1 $(SO_SEARCH_PATH)/libdep1.so
	@echo "make $(BIN_DYNA_LINK)"
	@$(CC) $(CFLAGS) $(LIB_PATH) -ldep1 \
	       -Wl,-rpath,`pwd`:$(SO_SEARCH_PATH) dynamic_linking.c \
	       -o $(BIN_DYNA_LINK)

dynamic_loading:
	@mkdir -p $(SO_SEARCH_PATH)
	@echo "make libdep.so.1.0"
	@$(CC) $(CFLAGS) \
	       -fPIC -shared -Wl,-rpath,`pwd`:$(SO_SEARCH_PATH) dep.c \
	       -Wl,-soname,libdep.so.1 \
	       -Xlinker --version-script dynamic_loading.lds \
	       -o $(SO_SEARCH_PATH)/libdep.so.1.0
	@echo "make $(BIN_DYNA_LOAD)"
	@ln -s -r $(SO_SEARCH_PATH)/libdep.so.1.0 $(SO_SEARCH_PATH)/libdep.so.1
	@ln -s -r $(SO_SEARCH_PATH)/libdep.so.1 $(SO_SEARCH_PATH)/libdep.so
	@$(CC) $(CFLAGS) $(LIB_PATH) -ldl \
	       -D_GNU_SOURCE -rdynamic \
	       -Wl,-rpath,`pwd`:$(SO_SEARCH_PATH) dynamic_loading.c \
	       -o $(BIN_DYNA_LOAD)

clean:
	@echo clean all
	@rm -rf $(BIN_STATIC_LINK) $(BIN_DYNA_LINK) $(BIN_DYNA_LOAD) $(SO_SEARCH_PATH) *.o *.so
