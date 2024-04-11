#include "GUI.h"

void InitWin(GtkApplication *app, gpointer user_data){
	GtkBuilder *builder=gtk_builder_new_from_file("../WinUI.ui"); //prendo la configurazione da un file
	GtkWindow *mainWin=GTK_WINDOW(gtk_builder_get_object(builder, "MainWin"));
	GtkDrawingArea *cairoArea=GTK_DRAWING_AREA(gtk_builder_get_object(builder, "cairoArea"));
	gtk_application_add_window(app, mainWin);
	gtk_drawing_area_set_draw_func(cairoArea, drawArea, NULL, NULL);
	gtk_window_present(mainWin);
}

void drawArea(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data){
	for(int i=0; i<NFREQ; i++) cairo_rectangle(cr,(i*COLONNA)+1,399,COLONNA-1,-40);
	cairo_set_source_rgb(cr,255,0,0);
	cairo_fill(cr);
	for(int i=0; i<NFREQ; i++) cairo_rectangle(cr,(i*COLONNA),400,COLONNA,-41);
	cairo_set_source_rgb(cr,0,0,0);
	cairo_stroke(cr);
}
