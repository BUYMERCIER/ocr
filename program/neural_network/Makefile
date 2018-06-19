## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O0 -g3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

OBJ= main.o file_management.o neural_network.o neuron.o
DEP= ${SRC:.o=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} main
	${RM} main.d file_management.d neural_network.d neuron.d

-include ${DEP}

# END


