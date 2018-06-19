//~~~~~~~~~~~~~~//
// neural_net.c //
//~~~~~~~~~~~~~~//

#include "neuron.h"
#include "neural_network.h"
#include <limits.h>
#include <float.h>

struct net *init_net(char characters [], size_t num_of_char, size_t h, size_t w){
    struct net *net = malloc(sizeof(struct net));
    net->size = num_of_char;
    net->neuron = malloc((sizeof(struct neuron)) * num_of_char);
    for (size_t i = 0; i < num_of_char; i++){
        init_neuron((net->neuron + i), h, w, characters[i]);
    }
    return net;
}

void learning(char l_char, int input[], struct net *net, size_t input_h, size_t input_w){
    if (net->neuron->height == input_h && net->neuron->width == input_w){
        for (size_t i = 0; i < net->size; i++){
            if ((net->neuron + i)->character == l_char){
                learn(input, (net->neuron + i));
                return;
            }
        }
    }
    else
        printf("INPUT : wrong dimension");
}

char recognition(int input [], struct net *net){
    float i_res = -1 * FLT_MAX;
    char res = '1';
    for (size_t i = 0; i < net->size; i++){
        float temp = character_value(neuron_value(input, (net->neuron+i)),
                                                            (net->neuron+i));
        if (i_res < temp){
            i_res = temp;
            res = (net->neuron +i)->character;
        }
    }
    return res;
}

