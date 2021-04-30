CC=clang
CFLAGS=-std=gnu11 -Wall $(shell curl-config --cflags) $(shell curl-config --libs) -lm
DEBUG_CFLAGS=-O1 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address

genie: genie.c
	$(CC) $(CFLAGS) -lportaudio -lfftw3 genie.c weather.c cJSON.c listener.c -o genie
