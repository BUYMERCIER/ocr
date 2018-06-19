#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "neuron.h"

void init_neuron(struct neuron *neur, size_t h, size_t w, char a){
    neur->height = h;
    neur->width = w;
    neur->character = a;
    neur->weights = calloc(h * w, sizeof(int));
}

void learn (int input [], struct neuron *neuron){
    for (size_t i = 0; i < neuron->height; i++)
        for (size_t j = 0; j < neuron->width; j++){
            if (input [j + i*neuron->width] == 1)
                *(neuron->weights + (j + i * neuron->width)) += 1;
            else
                *(neuron->weights + (j + i * neuron->width)) += -1;
        }
}

int neuron_value (int input [], struct neuron *neuron){
    int value = 0;
    for (size_t i = 0; i < neuron->height; i++)
        for (size_t j = 0; j < neuron->width; j++){
            value += input[j + i*neuron->width] *
                                            neuron->weights[j+i*neuron->width];
    }
    return value;
}

float character_value(int value, struct neuron *neuron){
    int char_value = 0;
    for (size_t i = 0; i < neuron->height; i++)
        for (size_t j = 0; j < neuron->width; j++){
            if (neuron->weights[j + i* neuron->width] > 0)
                char_value += neuron->weights[j + i * neuron->width];
        }
    return (float)value/(float)char_value;
}

