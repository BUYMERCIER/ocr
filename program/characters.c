// -----------
// characters.c
//------------

# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "pixel_operations.h"
# include "recognition.h"

void convert(SDL_Surface* img, int mat[], int pos1x, int pos1y , int pos2x,
                                                         int pos2y, int temp){
    Uint32 pixel;
    Uint8 r, g , b;
    for(int i = pos1y; i < pos2y;i++){
        for(int j = pos1x; j < pos2x;j++){
            pixel = getpixel(img , j , i);
            SDL_GetRGB(pixel, img->format , &r , &g , &b);
            if(r == 0)
                mat[(j-pos1x) + (i-pos1y)*temp] = 1;
            else
                mat[(j-pos1x) + (i-pos1y)*temp] = 0;
        }
    }
}

void downsize_image(int dim, int inputs[], int resized_inputs[], int width,
                                                                  int height){
    double xscale = (float)(dim) / width;
    double yscale = (float)(dim) / height;
    double threshold = 0.5 / (xscale * yscale);
    double yend = 0.0;
    for (int f = 0; f < dim; f++) // y on output
    {
        double ystart = yend;
        yend = (f + 1) / yscale;
        if (yend >= height) yend = height - 0.000001;
        double xend = 0.0;
        for (int g = 0; g < dim; g++) // x on output
        {
            double xstart = xend;
            xend = (g + 1) / xscale;
            if (xend >= width) xend = width - 0.000001;
            double sum = 0.0;
            for (int y = (int)ystart; y <= (int)yend; ++y)
            {
                double yportion = 1.0;
                if (y == (int)ystart) yportion -= ystart - y;
                if (y == (int)yend) yportion -= y+1 - yend;
                for (int x = (int)xstart; x <= (int)xend; ++x)
                {
                    double xportion = 1.0;
                    if (x == (int)xstart) xportion -= xstart - x;
                    if (x == (int)xend) xportion -= x+1 - xend;
                    sum += inputs[x + y*width] * yportion * xportion;
                }
            }
            resized_inputs[g + f*dim] = (sum > threshold) ? 1 : 0;
        }
    }
}


void box_char(SDL_Surface* img, int pos1[], int pos2[]);

void loop_char(SDL_Surface* img, int lines_list [], int char_list [],
                                             int space_size, struct net *net){
    FILE *file;
    file = fopen("output", "w");
    int x = 0;
    int y = 0;
    while (lines_list[y] != -1 && lines_list[y+1] != -1){
        while(char_list[x] < char_list[x+1]){
            if (x%2 == 1){
                if(char_list[x+1] - char_list[x] > space_size){
                    fputs(" ", file);
                }
            }
            else{
                int pos1[] = {char_list[x], lines_list[y]};
                int pos2[] = {char_list[x+1], lines_list[y+1]};
                box_char(img, pos1, pos2);
                int *p = NULL;
                int temp = 0;
                if (pos2[0] - pos1[0] > pos2[1]- pos1[1]){
                    p = calloc(sizeof(int),(pos2[0]-pos1[0])*(pos2[0]-pos1[0]));
                    temp = (pos2[0]-pos1[0]);
                }
                else{
                    p = calloc(sizeof(int),(pos2[1]-pos1[1])*(pos2[1]-pos1[1]));
                    temp = (pos2[1]-pos1[1]);
                }
                convert(img, p, pos1[0], pos1[1], pos2[0], pos2[1], temp);
                int final_mat [32*32];
                downsize_image(32, p, final_mat, temp, temp);

                fprintf(file, "%c", recognition(final_mat, net));
                printf("%c", recognition(final_mat, net));

            }
            x++;
        }
        fputs("\n", file);
        x++;
        y += 2;
    }
    fclose(file);
}

void loop_char_learn(SDL_Surface* img, int lines_list [],
            int char_list [], int space_size, char character, struct net *net){
    int x = 0;
    int y = 0;
    while (lines_list[y] != -1 && lines_list[y+1] != -1){
        while(char_list[x] < char_list[x+1]){
            if (x%2 == 1){
                if(char_list[x+1] - char_list[x] > space_size){
                    printf("space");
                }
            }
            else{
                int pos1[] = {char_list[x], lines_list[y]};
                int pos2[] = {char_list[x+1], lines_list[y+1]};
                box_char(img, pos1, pos2);
                int *p = NULL;
                int temp = 0;
                if (pos2[0] - pos1[0] > pos2[1]- pos1[1]){
                    p = calloc(sizeof(int),(pos2[0]-pos1[0])*(pos2[0]-pos1[0]));
                    temp = (pos2[0]-pos1[0]);
                }
                else{
                    p = calloc(sizeof(int),(pos2[1]-pos1[1])*(pos2[1]-pos1[1]));
                    temp = (pos2[1]-pos1[1]);
                }
                convert(img, p, pos1[0], pos1[1], pos2[0], pos2[1], temp);
                int final_mat [net->neuron->height * net->neuron->width];
                downsize_image(net->neuron->height, p, final_mat, temp, temp);

                learning(character, final_mat, net,
                                    net->neuron->height, net->neuron->height);

            }
            x++;
        }
        x++;
        y += 2;
    }
}

void box_char(SDL_Surface* img, int pos1[], int pos2[]){
    int black = 0;
    Uint32 pixel;
    Uint8 r, g , b;
    int y = pos1[1];
    while(y < pos2[1] && black < 1){
        for(int x = pos1[0]; x < pos2[0]; x++){
            pixel = getpixel(img, x, y);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if (r == 0)
                black = 1;
        }
        if (black != 0)
            break;
        y++;
    }
    pos1[1] = y;

    black = 0;
    y = pos2[1];
    while(y > pos1[1]){
        for(int x = pos1[0]; x < pos2[0]; x++){
            pixel = getpixel(img, x, y);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if (r == 0)
                black = 1 ;
        }
        if (black != 0)
            break;
        y--;
    }
    pos2[1] = y;

}
