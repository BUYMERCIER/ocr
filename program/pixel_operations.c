// pixel_operations.c

// Simple get/put pixel for SDL
// Inspired by code from SDL documentation
// (http://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideo.html)

# include "pixel_operations.h"

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixelref(surface, x, y);
    switch(surface->format->BytesPerPixel) {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
    }
    return 0;
}

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
    Uint8 *p = pixelref(surface, x, y);
    switch(surface->format->BytesPerPixel) {
        case 1:
            *p = pixel;
            break;
        case 2:
            *(Uint16 *)p = pixel;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;
        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

SDL_Surface* grayscale (SDL_Surface* img){
    Uint32 pixel;
    Uint8 red;
    Uint8 blue;
    Uint8 green;
    Uint8 av;
    for (int w = 0; w < img->w; w++)
        for (int h = 0; h < img->h; h++){
            pixel = getpixel(img, w, h);
            SDL_GetRGB(pixel, img->format, &red, &green, &blue);

            red *= 0.3;
            green *= 0.59;
            blue *= 0.11;
            av = red + blue + green;

            pixel = SDL_MapRGB(img->format, av, av, av);
            putpixel(img, w, h, pixel);
        }
    return img;
}

// sdl
SDL_Surface* black_white(SDL_Surface* img)
{
    int black = 0;
    int white = 255;
    size_t histo[256];
    //build the histogram
    for (int w = 0; w < img -> w ; w++)
    {
        for (int h = 0; h < img -> h ; h++)
        {

            Uint32 pixel = getpixel(img, w, h);
            Uint8 red;
            Uint8 green;
            Uint8 blue;
            SDL_GetRGB(pixel, img->format, &red, &green, &blue);
            histo[(int)red] += 1;

        }
    }


    int size = img -> h * img -> w;
    //Compute Mu
    int mu = 0;
    for (int i = 0; i < 256; ++i)
    {
        mu += (i+1) * histo[i];
    }
    mu = mu / (size);

    // Computes sigma
    int sigma[256];
    for (int i = 0; i < 256; ++i)
    {
        double w = 0;
        double tmp = 0;
        for (int j = 0; j <= i; ++j)
        {
            w += histo[j];
            tmp += (j+1) * histo[j];
        }
        w /= size;
        tmp /= size;
        histo[i] = (int)(mu * w - tmp) * (mu * w - tmp) * (w * (1-w));
    }
    int threshold = 0;
    int max = 0;
    for (int i = 0; i < 256; ++i)
    {
        if(sigma[i] > max)
        {
            max = sigma[i];
            threshold = i;
        }
    }


    // threshold for making full white or full black

    Uint32 pixel;
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    for (int w = 0; w < img->w; w++)
        for (int h = 0; h < img->h; h++){
            pixel = getpixel(img, w, h);
            SDL_GetRGB(pixel, img->format, &red, &green, &blue);

            if((red+green+blue)/3 < threshold)
                red = black;
            else
                red = white;
            pixel = SDL_MapRGB(img->format, red, red, red);
            putpixel(img, w, h, pixel);
        }
    return img;
}
