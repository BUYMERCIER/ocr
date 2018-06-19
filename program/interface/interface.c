// ----
// interface.c
// author: corentin.mercier (K4LI) 
// ----

# include <stdio.h>
# include <stdlib.h>
# include <gtk/gtk.h>
# include <string.h>

# include "err.h"
# include "SDL/SDL.h"
# include "SDL/SDL_image.h"
# include "../pixel_operations.h"
# include "../segmentation.h"
# include "../characters.h"
# include "../sdl/sdl.h"
# include "../recognition.h"

// global variables
char *path = NULL;
struct net *net = NULL;
char *path2 = NULL;


static void _load(GtkWidget* button, gpointer window)
{
    // opens a file explorer so you can choose your image
    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new("Choose a picture", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_widget_show_all(dialog);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));

    if(resp == GTK_RESPONSE_OK){
        printf("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
        // getting the path of the image in the global variable
        path2 = malloc(sizeof(char));
        path2 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }
    else
        g_print("You pressed Cancel\n");
    // closing the window
    gtk_widget_destroy(dialog);

    // load
    net = load_net2(path2);
}


static void open_dialog(GtkWidget* button, gpointer window)
{
    // opens a file explorer so you can choose your image
    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new("Choose a picture", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_widget_show_all(dialog);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));

    if(resp == GTK_RESPONSE_OK){
        printf("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
        // getting the path of the image in the global variable
        path = malloc(sizeof(char));
        path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }
    else
        g_print("You pressed Cancel\n");
    // closing the window
    gtk_widget_destroy(dialog);
}

static void button_clicked()
{
    if(path)
        display(path);
}

static void black_and_white()
{
    if(path)
        display_bw(path);
}

static void segmentation()
{
    if(path)
        display_segmented(path);
}

static void _OCR(){
    if (path && net)
        OCR(path, net);
}

static void _new(GtkApplication* app,  gpointer user_data)
{
    net = new_net("neurals/");
}

static void _save_net2(GtkApplication* app,  gpointer user_data)
{
    save_net2(net);
}

//
static void activate(GtkApplication* app,  gpointer user_data)
{
    // declaring buttons
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *display_image;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *exit;
    GtkWidget *button5;
    GtkWidget *save;
    GtkWidget *load;
    GtkWidget *convert;
    GtkWidget *learn;
    GtkWidget *new;

    // declaring the image
    GtkWidget *image;

    image = gtk_image_new_from_file("../pictures_bank/ocr.png");

    // title and size
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "OCR");
    gtk_window_set_default_size (GTK_WINDOW (window), 300, 65);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window),grid);

    // buttons labels
    display_image = gtk_button_new_with_label("Display Image");
    button2 = gtk_button_new_with_label("Black and White");
    button3 = gtk_button_new_with_label("Segmentation");
    exit = gtk_button_new_with_label("Exit");
    button5 = gtk_button_new_with_label("Load image");
    convert = gtk_button_new_with_label("Convert");
    save = gtk_button_new_with_label("Save");
    load = gtk_button_new_with_label("Load");
    learn = gtk_button_new_with_label("Learn");
    new = gtk_button_new_with_label("New");

    // opens file explorer to select path to image
    g_signal_connect(load, "clicked", G_CALLBACK(_load), NULL); 
    g_signal_connect(button5, "clicked", G_CALLBACK(open_dialog), NULL);

    // exits the program
    g_signal_connect_swapped(exit, "clicked", G_CALLBACK(gtk_widget_destroy), 
                                                                        window);
    // displays vanilla image
    g_signal_connect(display_image, "clicked", G_CALLBACK(button_clicked), NULL);

    // displays black and white image
    g_signal_connect(button2, "clicked", G_CALLBACK(black_and_white), NULL);

    // displays segmented image
    g_signal_connect(button3, "clicked", G_CALLBACK(segmentation), NULL);

    // lanches the neural net
    g_signal_connect(convert, "clicked", G_CALLBACK(_OCR), NULL);

    // new
    g_signal_connect(new, "clicked", G_CALLBACK(_new), NULL);

    // saves it
    g_signal_connect(save, "clicked", G_CALLBACK(_save_net2), NULL);

    // display buttons in the window
    gtk_grid_attach(GTK_GRID(grid),display_image, 0 , 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),button2, 1 , 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),button3, 2 , 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),convert, 0 , 4, 3, 1);
    gtk_grid_attach(GTK_GRID(grid),button5, 0 , 0, 3, 1);
    gtk_grid_attach(GTK_GRID(grid),exit, 0, 6, 3, 1);
    gtk_grid_attach(GTK_GRID(grid),save, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),load, 1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid),new, 2, 5, 1, 1);

    gtk_grid_attach(GTK_GRID(grid),image, 0, 1, 4, 1);

    gtk_widget_show_all (window);
}

int main_gtk(){
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run(G_APPLICATION(app), NULL, NULL);
    g_object_unref(app);
}
