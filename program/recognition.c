# include "recognition.h"
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "pixel_operations.h"
# include "segmentation.h"
# include "characters.h"
# include "sdl/sdl.h"
# include "dirent.h"

void print_net (struct net *net){
    for (size_t i = 0; i < net->size; i++){
        for (size_t n =0; n < net->neuron->height; n++){
            for (size_t j = 0; j < net->neuron->width; j++){
                printf("| %d", (net->neuron+i)->weights[j+ n*net->neuron->width]);
            }
            printf("|\n");
        }
        printf("\n");
        printf(" %c ", (net->neuron+i)->character);
    }
}

void save_net2(struct net *net){
    save_net(net, "new_net");
}

struct net *load_net2(char path []){
    printf("\n %s\n", path);
    struct net *net = load_net(path);
    print_net(net);
    return net;
}

int OCR(char *path, struct net *net){

    // IMAGE PREPROSS
    SDL_Surface *img = load_image(path);
    img = grayscale(img);
    img = black_white(img);

    // SEGMENTATION
    int lines_list[3000];
    int char_list[4000];
    segment(img, lines_list);
    segment_char(img, lines_list, char_list);

    loop_char(img, lines_list, char_list, 20, net);

    return 1;
}

struct net *new_net(char *path){
    char characters [37];
    characters[0] = '=';
    characters[1] = 'a';
    characters[2] = 'b';
    characters[3] = 'c';
    characters[4] = 'd';
    characters[5] = 'e';
    characters[6] = 'f';
    characters[7] = 'g';
    characters[8] = 'h';
    characters[9] = 'i';
    characters[10] = 'j';
    characters[11] = 'k';
    characters[12] = 'l';
    characters[13] = 'm';
    characters[14] = 'n';
    characters[15] = 'o';
    characters[16] = 'p';
    characters[17] = 'q';
    characters[18] = 'r';
    characters[19] = 's';
    characters[20] = 't';
    characters[21] = 'u';
    characters[22] = 'v';
    characters[23] = 'w';
    characters[24] = 'x';
    characters[25] = 'y';
    characters[26] = 'z';
    /*characters[27] = 'A';
    characters[28] = 'B';
    characters[29] = 'C';
    characters[30] = 'D';
    characters[31] = 'E';
    characters[32] = 'F';
    characters[33] = 'G';
    characters[34] = 'H';
    characters[35] = 'I';
    characters[36] = 'J';
    characters[37] = 'K';
    characters[38] = 'L';
    characters[39] = 'M';
    characters[40] = 'N';
    characters[41] = 'O';
    characters[42] = 'P';
    characters[43] = 'Q';
    characters[44] = 'R';
    characters[45] = 'S';
    characters[46] = 'T';
    characters[47] = 'U';
    characters[48] = 'V';
    characters[49] = 'W';
    characters[50] = 'X';
    characters[51] = 'Y';
    characters[52] = 'Z';
    characters[53] = '0';
    characters[54] = '1';
    characters[55] = '2';
    characters[56] = '3';
    characters[57] = '4';
    characters[58] = '5';
    characters[59] = '6';
    characters[60] = '7';
    characters[61] = '8';
    characters[62] = '9';*/
    characters[27] = '0';
    characters[28] = '1';
    characters[29] = '2';
    characters[30] = '3';
    characters[31] = '4';
    characters[32] = '5';
    characters[33] = '6';
    characters[34] = '7';
    characters[35] = '8';
    characters[36] = '9';

    struct net *net = init_net(characters, 37, 32, 32);
    // IMAGE PREPROSS

    int learn_times = 10;
    for (int i =0; i <learn_times; i++){
        DIR *d;
        struct dirent *dir;
        d = opendir("/home/tarkof/Documents/git/optical-character-recognition/database/letters");
        if (d){
            // ls
            while ((dir = readdir(d)) != NULL){
                if (dir->d_name[0] != '.'){
                    printf(" %s \n", dir->d_name);
                    char char_path [100];
                    snprintf(char_path, 100, "%s%s", "/home/tarkof/Documents/git/optical-character-recognition/database/letters/", dir->d_name);

                    SDL_Surface *img = load_image(char_path);
                    img = grayscale(img);
                    img = black_white(img);
                    int lines_list[3000];
                    int char_list[4000];
                    segment(img, lines_list);
                    segment_char(img, lines_list, char_list);

                    loop_char_learn(img, lines_list, char_list, 35,
                                                        dir->d_name[0], net);
                }
            }
            closedir(d);
        }
    }
    printf(">>learning done\n");
    return net;
}

