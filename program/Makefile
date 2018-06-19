## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3 -g
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl` -lSDL_image
 
OBJ= characters.o segmentation.o pixel_operations.o main.o \
interface/interface.o sdl/sdl.o neural_network/file_management.o \
neural_network/neural_network.o neural_network/neuron.o \
recognition.o
DEP= ${SRC:.o=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} main
	${RM} *.o *.d interface/*.d interface/*.o sdl/*d sdl/*.o neural_network/*.o neural_network/*.d

-include ${DEP}

# END
