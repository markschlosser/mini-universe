# Makefile for mini-universe
# usage: make, make clean, make debug=1

SRCDIR = ./src/
BINDIR = ./bin/
OBJDIR = ./obj/
CFLAGS = -Wall -Wno-deprecated-declarations
LFLAGS = -lm
OBJFILES = $(OBJDIR)simulation.o $(OBJDIR)render.o $(OBJDIR)main.o $(OBJDIR)file.o

ifeq ($(debug),1)
    CFLAGS += -g
endif

BINEXE = $(BINDIR)mini-universe

all: $(BINEXE)

clean:
	rm -rf ./obj/* ./bin/*

$(OBJDIR)simulation.o: $(SRCDIR)simulation.c $(SRCDIR)simulation.h
	gcc -c $(SRCDIR)simulation.c -o $(OBJDIR)simulation.o $(CFLAGS)

$(OBJDIR)render.o: $(SRCDIR)render.c $(SRCDIR)render.h
	gcc -c $(SRCDIR)render.c -o $(OBJDIR)render.o $(CFLAGS)

$(OBJDIR)main.o: $(SRCDIR)main.c
	gcc -c $(SRCDIR)main.c -o $(OBJDIR)main.o $(CFLAGS)

$(OBJDIR)file.o: $(SRCDIR)file.c
	gcc -c $(SRCDIR)file.c -o $(OBJDIR)file.o $(CFLAGS)

$(BINEXE): $(OBJFILES)
	gcc $(OBJFILES) -o $(BINEXE) $(LFLAGS)
