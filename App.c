#include "App.h"
#ifdef DEBUG
#include <stdio.h>
#endif

extern myContext *ctx;

void InitApp(GtkApplication *self, gpointer user_data){
	GtkBuilder *builder=gtk_builder_new_from_file("../WinUI.ui");
	GtkWindow *MainWin=GTK_WINDOW(gtk_builder_get_object(builder, "MainWin"));
	ctx->cairoArea=GTK_DRAWING_AREA(gtk_builder_get_object(builder, "cairoArea"));
	gtk_drawing_area_set_draw_func(ctx->cairoArea, drawArea, NULL, NULL);
	g_signal_connect(GTK_WIDGET(MainWin), "close-request", G_CALLBACK(closeWin), NULL);
	gtk_application_add_window(self,MainWin);
#ifdef DEBUG
	for(int i=0; i< (ctx->N/2); i++) printf("%d: %f\n", i, (double)i*(double)(ctx->pcm->fcamp)/(double)(ctx->N));
#endif
	gtk_window_present(MainWin);
}

void alrmHandler(int seg){
	if(ctx->startRec==0) ctx->startRec=1;
	else{
		for(int i=0; i<ctx->N; i++) (ctx->bufferAudio)[i]=(ctx->bufferInter)[i];
		fftw_execute(ctx->p);
		gtk_widget_queue_draw(GTK_WIDGET(ctx->cairoArea));
	}
}

void* routineAudio(void* args){
	while(ctx->startRec==0);
	while(1){
		ReadPCM(ctx->pcm, ctx->bufferInter);
	}
	return NULL;
}

#ifdef GUI
void drawArea(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data){
	for(int i=0; i<NFREQ; i++) {
		const double h= sqrt(((ctx->out)[6+i*5])[0]*((ctx->out)[6+i*5])[0]+((ctx->out)[6+i*5])[1]*((ctx->out)[6+i*5])[1])/((double)(ctx->N));
		cairo_rectangle(cr,(i*COLONNA)+1,399,COLONNA-1,-h);
	}
	cairo_set_source_rgb(cr,255,0,0);
	cairo_fill(cr);
	for(int i=0; i<NFREQ; i++){
		const double h= sqrt(((ctx->out)[6+i*5])[0]*((ctx->out)[6+i*5])[0]+((ctx->out)[6+i*5])[1]*((ctx->out)[6+i*5])[1])/((double)(ctx->N));
		cairo_rectangle(cr,(i*COLONNA),400,COLONNA,-h-1);
	}
	cairo_set_source_rgb(cr,0,0,0);
	cairo_stroke(cr);
}

void closeWin(GtkWindow *self, gpointer user_data){
	pthread_cancel(ctx->threadAudio);
}
#endif
