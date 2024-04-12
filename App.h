#define _POSIX_C_SOURCE 199309L

#ifdef GUI
#include <gtk/gtk.h>
#define NFREQ 70
#define COLONNA 20
#define FPS 25L

void drawArea(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data);
void closeWin(GtkWindow *self, gpointer user_data);
#endif
#include "PCM.h"
#include <fftw3.h>

typedef struct _myContext{
#ifdef GUI
	GtkDrawingArea *cairoArea;
#endif
	fftw_plan p;
	MyPCM *pcm;
	double *bufferAudio;
	short *bufferInter;
	fftw_complex *out;
	int startRec; //sostituire con variabile condizionale
	pthread_t threadAudio;
	unsigned int N; //numero di frames
} myContext;

void InitApp(GtkApplication *self, gpointer user_data);
void* routineAudio(void* args);
void alrmHandler(int seg);
