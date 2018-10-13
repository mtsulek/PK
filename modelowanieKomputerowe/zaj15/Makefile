
PROGRAM_NAME=projekt.bin

SOURCES=src/main.cpp #src/Particle.cpp src/Allegro.cpp
HEADERS=headers
ALLEGRO_LIBS=`pkg-config --cflags --libs allegro-5 allegro_ttf-5 allegro_primitives-5 allegro_physfs-5 allegro_memfile-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_dialog-5 allegro_color-5 allegro_audio-5 allegro_acodec-5`

all:
	g++ $(SOURCES) -o $(PROGRAM_NAME) -I$(HEADERS) $(ALLEGRO_LIBS) --std=c++11
	./projekt.bin
run:
	g++ $(SOURCES) -o $(PROGRAM_NAME) $(ALLEGRO_LIBS) --std=c++11
	./$(PROGRAM_NAME)

onlyrun:
	./$(PROGRAM_NAME)

clean:
	rm $(PROGRAM_NAME)
