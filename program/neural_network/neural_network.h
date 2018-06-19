
struct net {
    struct neuron *neuron;
    size_t size;
};

// Initializes the neural networ
struct net *init_net(char characters [], size_t num_of_char, size_t h, size_t w);

// Finds the corresponding neuron to a given input and teaches it;
void learning(char l_char, int input[], struct net *net, size_t input_h, size_t input_w);

char recognition(int input [], struct net *net);

//void save_net(struct net *net, char path []);

//struct net *load_net(char path []);
