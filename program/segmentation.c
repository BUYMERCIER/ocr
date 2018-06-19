// -------------------
// sengmentation.c
// --------------------

# include "pixel_operations.h"
# include "segmentation.h"
# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>
# include "characters.h"

SDL_Surface* drawLine(SDL_Surface* img, int list_lines []){ //draw horizontal lines to separe text lines
    int width = img->w;
    int i = 0;
    while (list_lines[i] != -1){
        for(int x = 0; x < width; x++){
            putpixel(img, x, list_lines[i], SDL_MapRGB(img->format, 255, 0, 0));
        }
        i++;
    }
    return (img);
}

SDL_Surface* drawLine_Char(SDL_Surface* img, int char_list [], int lines_list []){
    int i = 0;
    int n = 0;
    int h1 = 0;
    int h2 = 0;
    while (lines_list[i] != -1 ){
        h1 = lines_list[i];
        h2 = lines_list[i+1];
        while (char_list[n] < char_list[n+1]){
            for (int j = h1; j < h2; ++j){
                putpixel(img, char_list[n], j, SDL_MapRGB(img->format, 255, 0, 0));
            }
            n++;
        }
        for (int j = h1; j < h2; ++j){
            putpixel(img, char_list[n], j, SDL_MapRGB(img->format, 255, 0, 0));
        }
        n++;
        i += 2;
    }

    return img;
}


SDL_Surface* segment_char(SDL_Surface* img, int lines_list [], int char_list []){
    int black_found = 0;
    int top_found = 0;
    int char_num=0;
    for (int n = 0; n < img->w; n++)
        char_list[n] = -1;

    Uint32 pixel;
    Uint8 r, g, b;

    int i = 0;
    while(lines_list[i] != -1 && lines_list[i+1] != -1){ //take values two by two, to select the top and bottom of a line
        int h1 = lines_list[i];
        int h2 = lines_list[i+1];

        for(int x = 0; x < img->w ; ++x){
            black_found = 0;
            for(int y = h1; y < h2; ++y){
                pixel = getpixel(img, x, y);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                if (r == 0 && black_found < 200){ //counts black pixels
                    black_found++;
                }
            }

            if (black_found > 0 && top_found == 0){ //finds beginning of a char
                char_list [char_num] = x;
                char_num++;
                top_found = 1;
            }
            else if (black_found <= 0 && top_found == 1){ //find end of a char
                char_list [char_num] = x;
                char_num++;
                top_found = 0;
            }	
        }
        i += 2;
    }
    return img;
}

SDL_Surface* segment(SDL_Surface* img, int lines_list[]){
    int width = img->w;
    int height = img->h;
    for (int i = 0; i <  height; i++)
        lines_list[i] = -1;
    int lines_num = 0;
    int top_found = 0; // boolean if top found
    int black_found = 0;
    Uint32 pixel;
    Uint8 r, g, b;

    // goes through the image
    for(int x = 0; x < height; ++x){
        black_found = 0;
        for(int y = 0; y < width; ++y){
            pixel = getpixel(img, y, x);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);

            if (r == 0 && black_found < 200){ //counts for the number of black pixel
                black_found++;
            }
        }

        if (black_found > 0 && top_found == 0){ //looks for the beginning of a line
            lines_list [lines_num] = x;
            lines_num++;
            top_found = 1;
        }
        else if (black_found <= 0 && top_found == 1){ //looks for the end of a line
            lines_list [lines_num] = x;
            lines_num++;
            top_found = 0;
        }
    }
    //drawLine(img, lines_list);
    return img;
}
