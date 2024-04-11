#include "PCM.h"

int InitPCM(MyPCM **pcm_h){
	//apertura del PCM e configurazione
	int err;
	*pcm_h=(MyPCM*)malloc(sizeof(MyPCM));
	(*pcm_h)->fcamp=48000.0;
	(*pcm_h)->formato=SND_PCM_FORMAT_S16_LE;
	(*pcm_h)->latenza=50000.0;
	(*pcm_h)->dimFrame=2.0;
	err=snd_pcm_open(&((*pcm_h)->handlePCM), "default", SND_PCM_STREAM_CAPTURE, 0);
	if(err < 0) return err;
	err=snd_pcm_set_params((*pcm_h)->handlePCM, (*pcm_h)->formato, SND_PCM_ACCESS_RW_INTERLEAVED, 1, (*pcm_h)->fcamp, 0, (*pcm_h)->latenza);
	return err;
}

void DelPCM(MyPCM *pcm_h){
	snd_pcm_close(pcm_h->handlePCM);
	free(pcm_h);
}

int ReadPCM(MyPCM *pcm_h, void* b){
	return snd_pcm_readi(pcm_h->handlePCM, b, pcm_h->fcamp*(pcm_h->latenza/1000000.0));
}
