//
// sdl.c
// @author: corentin.mercier
//

# include <stdio.h>
# include <stdlib.h>

# include "err.h"
# include <SDL/SDL.h>
# include "SDL/SDL_image.h"
# include "../pixel_operations.h"
# include "../segmentation.h"
# include "../characters.h"
# include "sdl.h"

// Waiting for a key
void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}

// Initializing SDL
void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}

//Loading an image from a file
SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

//Now, we can write a function that take the surface corresponding to a loaded image and open a window with the same dimension, display the image on it and wait for a key:
SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }

  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  // wait for a key
  wait_for_keypressed();

  // return the screen for further uses
  return screen;
}

void clear(){ //Clears terminal
	printf("\n");
	int sys = system("clear");

	if (sys != 0){	//Catches any error of system()
		printf("damn");
	}
}

// vanilla display (twice for mac)
void display(char *path)
{
    display_image(load_image(path));
}

// black and white display
void display_bw(char *path)
{
    display_image(black_white(grayscale(load_image(path))));
}

// segmented display
void display_segmented(char *path)
{
    int lines_list[3000];
    int char_list[3000];
    SDL_Surface *img = load_image(path);
    grayscale(img);
    black_white(img);
    segment(img, lines_list);
    segment_char(img, lines_list, char_list);
    drawLine(img, lines_list);
    drawLine_Char(img, char_list, lines_list);

    display_image(img);
}
