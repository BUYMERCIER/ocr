# ifndef SDL_H
# define SDL_H

# include <SDL/SDL.h>

SDL_Surface* display_image(SDL_Surface *img);
void clear();
void menu(SDL_Surface *image);
SDL_Surface* load_image(char *path);
void display(char *path);
void display_bw(char *path);
void display_segmented(char *path);

# endif
