#include <gtk/gtk.h>
#define NFREQ 70
#define COLONNA 20.0
#define FPS 25L

void InitWin(GtkApplication *self, gpointer user_data);
void drawArea(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data);
