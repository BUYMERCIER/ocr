# ifndef SEGMENTATION
# define SEGMENTATION

SDL_Surface* drawLine(SDL_Surface* img, int list_lines []);
SDL_Surface* drawLine_Char(SDL_Surface* img, int char_list [], int lines_list []);
SDL_Surface* segment_char(SDL_Surface* img, int lines_list [], int char_list []);
SDL_Surface* segment(SDL_Surface* img, int lines_list[]);
SDL_Surface* drawLine(SDL_Surface* img, int list_lines []);

# endif
