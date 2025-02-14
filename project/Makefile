CC = gcc
CFLAGS = -Wall

all: webSearch

webSearch: webSearch.o crawler.o index.o
	$(CC) $(CFLAGS) -o webSearch webSearch.o crawler.o index.o -lm

webSearch.o: webSearch.c crawler.h index.h
	$(CC) $(CFLAGS) -c webSearch.c

crawler.o: crawler.c crawler.h index.h
	$(CC) $(CFLAGS) -c crawler.c

index.o: index.c index.h
	$(CC) $(CFLAGS) -c index.c

clean:
	rm -f webSearch webSearch.o crawler.o index.o
