CC=clang
CFLAGS=-std=gnu11 -Wall $(shell curl-config --cflags) $(shell curl-config --libs) -lm
DEBUG_CFLAGS=-O1 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address

genie: genie.c
	$(CC) $(CFLAGS) genie.c cJSON.c -o genie

debug: genie.c
	$(CC) $(CFLAGS) $(ASAN_CFLAGS) genie.c -o genie
