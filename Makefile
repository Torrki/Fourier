INCLUDE_PKG= $(shell pkg-config --cflags gtk4 alsa fftw3)
LIBS_PKG= $(shell pkg-config --libs gtk4 alsa fftw3)
SRC= *.c

compile:
	gcc -o ./build/Fourier $(INCLUDE_PKG) $(SRC) $(LIBS_PKG) -lrt
