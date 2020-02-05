CC      = gcc
CFLAGS  = -W -Wall -ansi -pedantic
LDFLAGS = -std=c11 -O3 
EXEC    = norm test

all: $(EXEC)

norm : glib.o
test : glib.o

%: %.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf norm *.o

mrproper: clean
	rm -rf $(EXEC)