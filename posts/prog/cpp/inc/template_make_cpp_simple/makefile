OUT_BIN=$(shell basename $(CURDIR))
SRC_DIR=src
DEP_DIR:=deps
OBJ_DIR:=obj

ifdef VERBOSE
Q =
E = @true 
else
Q = @
E = @echo 
endif

SRC_C:=$(shell find $(SRC_DIR) -mindepth 1 -maxdepth 4 -name "*.c")
SRC_CXX:=$(shell find $(SRC_DIR) -mindepth 1 -maxdepth 4 -name "*.cpp")
#SRC_INF:=$(SRC_C) $(SRC_CXX)
#DEPFILES:=$(SRC_CXX:$(SRC_DIR)/%.cpp=%) $(SRC_C:$(SRC_DIR)/%.c=%)
OBJ_SRC:=$(SRC_CXX:$(SRC_DIR)/%.cpp=%) $(SRC_C:$(SRC_DIR)/%.c=%)
OBJS:=$(OBJ_SRC:%=$(OBJ_DIR)/%.o)

FLAGS_COMMON:= -Wall -Wextra -pedantic -O3 
ifdef DEBUG
FLAGS_COMMON:=$(FLAGS_COMMON) -g
endif
SYS_DEF:= -fpic -Wl,-rpath=.
INC_PATH:= -I. -I./include
#LDFLAGS:= -L/usr/libx86_64-linux-gnu/  -L/usr/lib/x86_64-linux-gnu -L/usr/local/lib -L.
LDFLAGS:=
#LIBS:= -lusb-1.0 -lopencv_core -lopencv_highgui -lreadline -lopencv_calib3d -lopencv_imgcodecs -lc -lopencv_imgproc
LIBS:=

all: $(OUT_BIN)
ifeq ($(MAKECMDGOALS),)
-include Makefile.dep
endif
ifneq ($(filter-out clean, $(MAKECMDGOALS)),)
-include Makefile.dep
endif

CC = gcc
CXX = g++
CFLAGS:=$(FLAGS_COMMON) --std=c99 $(SYS_DEF) $(INC_PATH)
CXXFLAGS:=$(FLAGS_COMMON) --std=c++0x $(SYS_DEF) $(INC_PATH)

-include Makefile.local

.PHONY: clean all depend
.SUFFIXES:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(E)compiling c source: $<
	$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(Q)$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(E)compiling cpp source: $<
	$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(Q)$(CXX) -o $@ -c $< $(CXXFLAGS)

Makefile.dep: $(SRC_C) $(SRC_CXX)
	$(E)depend
	$(Q)for i in $(^); do $(CXX) $(CXXFLAGS) -MM "$${i}" -MT $(OBJ_DIR)/`basename $${i%.*}`.o; done > $@

$(OUT_BIN): $(OBJS)
	$(E)linking bin: $@
	$(Q)$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

clean:
	$(E)clean all
	$(Q)rm -f $(OUT_BIN) $(OBJ_DIR)/* Makefile.dep
