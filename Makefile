CC=gcc
CFLAGS=-g -lm -fopenmp
DEPS = decl.h
OBJ = main.o alloc.o init.o solve.o IO.o
EXE = main.exe

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@.exe $^ $(CFLAGS)

clean:
	rm *.o *.exe
