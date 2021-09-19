cc = gcc
CFLAGS=-I.

main: main.o foo/foo.o bar/bar.o
	$(cc) -o main main.o foo/foo.o bar/bar.o

clean:
	rm main