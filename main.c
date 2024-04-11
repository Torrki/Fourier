#define _POSIX_C_SOURCE 199309L //per sigaction e timer

#include "GUI.h"
#include "PCM.h"
#include <fftw3.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alrmAction(int sig);
fftw_plan p;

int main(int argc, char *argv[]){
	#ifndef GUI
	MyPCM *pcm=NULL;
	size_t framesLetti=0;
	if( InitPCM(&pcm) < 0){
		printf("Errore in InitPCM\n");
		exit(EXIT_FAILURE);
	}
	
	//installazione sigaction per timer
	struct sigaction newAct={.sa_flags=0, .sa_handler=alrmAction};
	sigaction(SIGALRM, &newAct, NULL);
	
	timer_t idTimer;
	timer_create(CLOCK_REALTIME, NULL, &idTimer);
	struct itimerspec tSpec={.it_interval={.tv_sec=0L,.tv_nsec=1000000000L/FPS}, .it_value={.tv_sec=0L, .tv_nsec=1000000000L/FPS}};
	
	const unsigned long N=(pcm->fcamp)*(pcm->latenza)/1000000.0; //Numero di frames per registrazione
	
	//preparazione fftw
	void *bufferAudio=calloc(N, pcm->dimFrame);
	fftw_complex *out=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*(N/2+1));
	p=fftw_plan_dft_r2c_1d(N, bufferAudio, out, 0);
	
	timer_settime(idTimer, TIMER_ABSTIME, &tSpec, NULL);
	while(framesLetti < (pcm->fcamp)*5.0){
		framesLetti+=ReadPCM(pcm, bufferAudio);
	}
	printf("%lu\n", framesLetti);
	timer_delete(idTimer);
	fftw_destroy_plan(p); //elimina automaticamente bufferAudio e out
	DelPCM(pcm);
	return 0;
	#else
	GtkApplication *app=gtk_application_new("GTK.Fourier", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(InitWin), NULL);
	int status=g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
	#endif
}

void alrmAction(int sig){
	fftw_execute(p); //esecuzione trasformata
}
