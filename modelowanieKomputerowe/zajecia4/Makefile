# Makefile for Allegro5 programs
# PARSE


PROGRAM_NAME=Gauss
# export PROGRAM_NAME
# target:
#     $(MAKE) -N target

SOURCES=main.cpp
ALLEGRO_LIBS=`pkg-config --cflags --libs allegro-5 allegro_ttf-5 allegro_primitives-5 allegro_physfs-5 allegro_memfile-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_dialog-5 allegro_color-5 allegro_audio-5 allegro_acodec-5`
# OUTPUT_DIR=bin
# LINUX_GCC=gcc
# LINUX_CFLAGS=-O2 -Wall
# ALLEGRO5_LINUX=`pkg-config --cflags --libs allegro-5 allegro_ttf-5 allegro_primitives-5 allegro_physfs-5 allegro_memfile-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_dialog-5 allegro_color-5 allegro_audio-5 allegro_acodec-5`
# export PKG_CONFIG_PATH=/usr/i686-w64-mingw32/lib/pkgconfig/

all:
	g++ $(SOURCES) -o $(PROGRAM_NAME) $(ALLEGRO_LIBS) --std=c++11

run:
	g++ $(SOURCES) -o $(PROGRAM_NAME) $(ALLEGRO_LIBS) --std=c++11
	./$(PROGRAM_NAME)

onlyrun:
	./$(PROGRAM_NAME)

clean:
	rm $(PROGRAM_NAME)
