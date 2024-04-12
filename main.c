#include "App.h"
#ifdef DEBUG
#include <stdio.h>
#endif

myContext *ctx;

int main(int argc, char *argv[]){
	ctx=(myContext*)calloc(1,sizeof(myContext)); //creazione contesto
	timer_t idTimer;
	if(InitPCM(&(ctx->pcm)) < 0){ //creazione PCM
		exit(EXIT_FAILURE);
	}
	
	//preparazione fftw
	const unsigned int N=((double)(ctx->pcm->fcamp))*((double)ctx->pcm->latenza/1000000.0);
	ctx->N=N;
	ctx->bufferAudio=(double*)fftw_malloc(N*sizeof(double));
	ctx->bufferInter=(short*)malloc(N*(ctx->pcm->dimFrame));
	ctx->out=(fftw_complex*)fftw_malloc(sizeof(fftw_complex)*((N/2)+1));
	ctx->p=fftw_plan_dft_r2c_1d(N, ctx->bufferAudio, ctx->out, FFTW_ESTIMATE);
	
	//timer, installazione del sigaction, start del thread audio
	timer_create(CLOCK_REALTIME, NULL, &idTimer);
	struct sigaction newAct={.sa_flags=0, .sa_handler=alrmHandler};
	sigaction(SIGALRM, &newAct, NULL);
	struct itimerspec ts={.it_interval={.tv_sec=0L, .tv_nsec=1000000000L/FPS}, .it_value={.tv_sec=1L, .tv_nsec=0L}};
	pthread_create(&(ctx->threadAudio), NULL, routineAudio, NULL);
	
	//start GUI
	GtkApplication *app=gtk_application_new("GTK.Fourier", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(G_APPLICATION(app), "activate", G_CALLBACK(InitApp), NULL);
	timer_settime(idTimer, 0, &ts, NULL);
	int status=g_application_run(G_APPLICATION(app), argc, argv);
	pthread_join(ctx->threadAudio, NULL);
	
	//pulizia
	timer_delete(idTimer);
	free(ctx->bufferInter);
	fftw_free(ctx->bufferAudio);
	fftw_free(ctx->out);
	fftw_destroy_plan(ctx->p);
	DelPCM(ctx->pcm);
	free(ctx);
	return status;
}
