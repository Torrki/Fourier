#include <alsa/asoundlib.h>

typedef struct _MyPCM{
	snd_pcm_t *handlePCM;
	unsigned int fcamp;
	snd_pcm_format_t formato;
	unsigned int latenza;
	size_t dimFrame;
}MyPCM;

int InitPCM(MyPCM **pcm_h);
void DelPCM(MyPCM *pcm_h);
int ReadPCM(MyPCM *pcm_h, void* b);
#ifdef DEBUG
void printPCM(MyPCM *pcm_h);
#endif
