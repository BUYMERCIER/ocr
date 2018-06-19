
//~~~~~~~~~~~~~~~~~~~//
// file_management.c //
//~~~~~~~~~~~~~~~~~~~//

#include "neuron.h"
#include "neural_network.h"
#include <limits.h>
#include <float.h>

void save_net(struct net *net, char path []){
    FILE *file;
    file = fopen(path, "w");
    fprintf(file, "%zu\n%zu\n%zu\n", net->size, net->neuron->height, net->neuron->width);

    for (size_t i = 0; i < net->size; i++){
        fprintf(file, "%c", (net->neuron + i)->character);
    }
    fputs("\n", file);

    for (size_t i = 0; i < net->size; i++){
        for (size_t n =0; n < net->neuron->height; n++){
            for (size_t j = 0; j < net->neuron->width; j++){
                fprintf(file, "|%d", (net->neuron+i)->weights[j+ n*net->neuron->width]);
            }
            fputs("|\n", file);
        }
        fputs("\n", file);
    }
    fclose(file);
}

struct net *load_net(char path []){
    FILE *file;
    file = fopen(path, "r");//FIXME Case: Wrong path

    char buff [255];
    size_t size = 0;
    size_t height = 0;
    size_t width = 0;

    // XXX use of strtol instead of atoi?
    fgets(buff, 255, (FILE*)file); //gets size
    size = atoi(buff);
    fgets(buff, 255, (FILE*)file); //gets size
    height = atoi(buff);
    fgets(buff, 255, (FILE*)file); //gets size
    width = atoi(buff);

    fgets(buff, 255, (FILE*)file); //gets characters string
    struct net *net = init_net(buff, size, height, width);

    fgets(buff, 255, (FILE*)file); //gets first neuron;
    for (size_t i = 0; i < size; i++){
        for (size_t n = 0; n < height; n++){
            int c = 1;
            for (size_t j = 0; j < width; j++){
                int sign = 1;
                while(buff[c] != '|'){
                    if(buff[c] == '-'){
                        sign = -1;
                        c++;
                    }
                    int cst = (buff[c] - '0')*sign;
                    (net->neuron +i)->weights[j+n*width] =
                        (net->neuron +i)->weights[j+n*width] * 10 + cst;
                    c++;
                }
                c++;
            }
            fgets(buff, 255, (FILE*)file); //gets next line of neuron;
        }
        fgets(buff, 255, (FILE*)file); //gets first line of next neuron;
    }
    return net;
}










//~~~~~~~~~~~~~~~~~~~//
// file_management.c //
//~~~~~~~~~~~~~~~~~~~//
