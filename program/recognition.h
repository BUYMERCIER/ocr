#include <stdio.h>
#include <stdlib.h>
#include "neural_network/neuron.h"
#include "neural_network/neural_network.h"
#include "neural_network/file_management.h"

int OCR (char *path, struct net *net);

struct net *new_net(char *path);
struct net *load_net2(char *path);
void save_net2(struct net *net);
