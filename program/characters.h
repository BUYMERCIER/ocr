# ifndef CHARACTERS_H
# define CHARACTERS_H


 void convert(SDL_Surface* img , int mat[], int pos1x , int pos1y , int pos2x , int pos2y);

// protoypes
void loop_char(SDL_Surface* img, int lines_list [], int char_list [], int space_size, struct net* net);

void box_char(SDL_Surface* img, int pos1[], int pos2 []);

void loop_char_learn(SDL_Surface* img, int lines_list [], int char_list [], int space_size, char character, struct net *net);
# endif
