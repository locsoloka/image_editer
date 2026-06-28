#include <gtk/gtk.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "image_readers/png/png_loader.h"
#include "image_readers/bmp/bmp_loader.h"

#include "file_types/history.h"
#include "file_types/raw_image.h"
#include "filter/filters.h"


int width = 0;
int height = 0;
bool running = true;

bool texture_needs_update = false;

RGB *out_texture = NULL;

static void on_file_open_ready(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
    GtkFileDialog *dialog = GTK_FILE_DIALOG(source_object);
    GtkWidget *window = GTK_WIDGET(user_data);
    GError *error = NULL;

    GFile *file = gtk_file_dialog_open_finish(dialog, res, &error);
    if (error != NULL) {
        g_clear_error(&error);
        return;
    }

    char *file_path = g_file_get_path(file);
    open_png(file_path, &width, &height, &out_texture);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(
        (const guchar *)out_texture,
        GDK_COLORSPACE_RGB,
        FALSE,
        8,
        width,
        height,
        width * 3,
        NULL,
        NULL
    );

    // GdkPixbuf → GdkTexture (GTK4-hoz kell)
    GdkTexture *texture = gdk_texture_new_for_pixbuf(pixbuf);
    g_object_unref(pixbuf);

    // GtkPicture: automatikusan skálázódik az ablakhoz
    GtkWidget *picture = gtk_picture_new_for_paintable(GDK_PAINTABLE(texture));
    g_object_unref(texture);

    // Megtartja az arányokat, de kitölti a teret
    gtk_picture_set_content_fit(GTK_PICTURE(picture), GTK_CONTENT_FIT_CONTAIN);

    gtk_widget_set_hexpand(picture, TRUE);
    gtk_widget_set_vexpand(picture, TRUE);

    gtk_window_set_child(GTK_WINDOW(window), picture);

    g_free(file_path);
    g_object_unref(file);
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Képmegjelenítő");

    // Alapméret beállítása
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkFileDialog *file_dialog = gtk_file_dialog_new();
    gtk_file_dialog_set_title(file_dialog, "Válassz ki egy PNG képet!");

    gtk_window_present(GTK_WINDOW(window));
    gtk_file_dialog_open(file_dialog, GTK_WINDOW(window), NULL, on_file_open_ready, window);
    g_object_unref(file_dialog);
}

int main(int argc, char *argv[])
{
    GtkApplication *app = gtk_application_new("hu.pelda.kep", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}

