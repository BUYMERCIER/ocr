// ######################### C O M P E N D I U M #############################

// PREPROS $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

// Segmentation.c

SDL_Surface* drawLine(SDL_Surface* img, int list_lines []);

SDL_Surface* drawLine_Char(SDL_Surface* img, int char_list [], int lines_list []);

SDL_Surface* segment_char(SDL_Surface* img, int lines_list []);

SDL_Surface* segment(SDL_Surface* img)

// Pixel_operation.c ~~~~~~~~~~~~~~~~~~~~~~~

SDL_Surface* grayscale (SDL_Surface* img);

SDL_Surface* black_white(SDL_Surface* img)

// Character.c ~~~~~~~~~~~~~~~~~~~~~~~~~~~`

void convert(SDL_Surface* img , int mat[], int pos1x , int pos1y , int pos2x , int pos2y);

void save_char(SDL_Surface* img, int topleft[], int topright[], int bottomleft[], int bottomr    ight[]);

void send_img_coord (SDL_Surface* img, int lines_list [], int char_list []); //FIXME


// NEURAL $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

// file_management.c

void save_net(struct net *net, char path []);

struct net *load_net(char path []);

// neural_net.c ~~~~~~~~~~~~~~~~~~~~~~~~~

struct net *init_net(char characters [], size_t num_of_char, size_t h, size_t w);

void learning(char l_char, int input[], struct net *net, size_t input_h, size_t input_w);

char recognition(int input [], struct net *net)

// neuron.c ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void init_neuron(struct neuron *neur, size_t h, size_t w, char a)

void learn (int input [], struct neuron *neuron);

int neuron_value (int input [], struct neuron *neuron);

int neuron_value (int input [], struct neuron *neuron);

