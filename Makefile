INCLUDE_PKG= $(shell pkg-config --cflags gtk4 alsa fftw3)
LIBS_PKG= $(shell pkg-config --libs gtk4 alsa fftw3)
SRC= PCM.c App.c main.c
gui:
	gcc $(INCLUDE_PKG) -DGUI -o ./build/Fourier $(SRC) $(LIBS_PKG) -lrt -lpthread -lm
gui_debug:
	gcc -g $(INCLUDE_PKG) -DDEBUG -DGUI -o ./build/Fourier $(SRC) $(LIBS_PKG) -lrt -lpthread -lm
