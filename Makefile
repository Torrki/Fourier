INCLUDE_PKG= $(shell pkg-config --cflags gtk4 alsa fftw3)
LIBS_PKG= $(shell pkg-config --libs gtk4 alsa fftw3)
SRC= main.c PCM.c

terminal:
	gcc -o ./build/Fourier $(INCLUDE_PKG) $(SRC) $(LIBS_PKG) -lrt
gui:
	gcc -o ./build/Fourier $(INCLUDE_PKG) -D GUI $(SRC) GUI.c $(LIBS_PKG) -lrt
