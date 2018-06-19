// pixel_operation.h

# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_

# include <stdlib.h>
# include <SDL.h>

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);


SDL_Surface* grayscale (SDL_Surface* img);
SDL_Surface* black_white(SDL_Surface* img);

# endif
