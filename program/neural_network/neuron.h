#include <time.h>
#include <stdio.h>
#include <stdlib.h>


struct neuron {
    size_t height;
    size_t width;
    int *weights;
    char character;
};

// Initializes one neuron with the character it will recognize
void init_neuron(struct neuron *neur, size_t h, size_t w, char a);

// Changes the values of the weight of a neuron with an input
void learn (int input [], struct neuron *neuron);

// Computes the value XXX
int neuron_value (int input [], struct neuron *neuron);

// XXX
float character_value (int value, struct neuron *neuron);
