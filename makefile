#
# WIP
# Copyright (c) 2020 Jovan Lanik
#

# Makefile

NAME = wip
CC = gcc
LDLIBS = -lm -lpthread -lGL -lGLEW -lconfig
CFLAGS = -std=c11 -Wall -pedantic -I ./ -I ./include

NDEBUG ?= 0
ifeq '$(NDEBUG)' '1'
	CFLAGS += -DNDEBUG -o3
else
	LDFLAGS = -pg
endif

SRC = $(wildcard src/*.c)
OBJ = $(SRC:%.c=%.o)
GLSL = $(wildcard glsl/*.vert glsl/*.frag)
CONF = wip.conf

WIP_WINDOW_BACKEND ?= glfw
LDLIBS += -l$(WIP_WINDOW_BACKEND)
SRC += backend/wip_window_$(WIP_WINDOW_BACKEND).c

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $@
src/wip_conf.o : include/baked/config.h
src/wip_gl.o : include/baked/shaders.h
include/baked/config.h : $(CONF)
	@echo making $@ from $(CONF)
	@util/bake $(CONF) $@
include/baked/shaders.h: $(GLSL:%=%.h)
	@cat $(GLSL:%=%.h) > $@
	@echo making $@ from $(GLSL)
%.vert.h: %.vert
	@glslangValidator $<
	@util/bake $< $<.h
%.frag.h: %.frag
	@glslangValidator $<
	@util/bake $< $<.h
clean:
	rm -f $(wildcard include/baked/*.h)
	rm -f $(GLSL:%=%.h)
	rm -f $(OBJ)
	rm -f gmon.out

.PHONY: all clean
