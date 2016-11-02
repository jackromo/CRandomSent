
P = sentgen

BUILDDIR = ./build

OBJECTS = $(patsubst %.c, $(BUILDDIR)/%.o, $(shell ls *.c))

CFLAGS=-g -Wall -O3
LDLIBS=
CC=gcc


$(BUILDDIR)/$(P): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BUILDDIR)/$(P) $(LDLIBS)


$(BUILDDIR)/%.o: ./%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm $(BUILDDIR)/*.o $(BUILDDIR)/$(P)

