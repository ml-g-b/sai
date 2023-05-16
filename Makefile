CC=gcc
CFLAGS=-W -Wall -O3
GLUT=-lglut -lGLU -lGL
MATH=-lm

inc_objf := $(addprefix include/, graphe_TLA.o  liste.o)
inc_h    := $(wildcard include/*.h)
inc_c    := $(wildcard include/*.c)
header   := $(wildcard header/*.h)
inc_obj  := $(inc_c:.c=.o)

EXE=main

all : $(EXE)

$(EXE) : $(EXE).c $(inc_obj) $(inc_objf) $(header)
	$(CC) $(CFLAGS) $(EXE).c $(inc_obj) $(inc_objf) -o $(EXE) $(GLUT) $(MATH)

run : $(EXE)
	./$(EXE)

clean :
	rm -f $(EXE) $(inc_obj)