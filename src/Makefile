CC      = gcc -g
CFLAGS  = -W -Wall -ansi -pedantic -std=c11
LDFLAGS = -O3
EXEC    = norm test n_of_graph norm_inc print_test gen_graph \
           label shuffle fifo direct_by_deg triangle connected diameter page_rank\
		   cluster load_adjarray load_edges load_matrix real_nb_node \
			kcore heap_test score heap_test2 communauty_triangle

all: $(EXEC)

norm : glib.o
test : glib.o

n_of_graph : glib.o
norm_inc   : glib.o
print_test : glib.o
gen_graph  : glib.o
label      : glib.o 
shuffle    : glib.o
fifo       : glib.o
triangle   : glib.o
connected  : glib.o
diameter   : glib.o
page_rank  : glib.o
cluster    : glib.o
kcore	   : glib.o

direct_by_deg : glib.o
load_adjarray : glib.o
load_edges    : glib.o
load_matrix   : glib.o
real_nb_node  :
heap_test 	  : glib.o
score         : glib.o
heap_test2 	  : glib.o

communauty_triangle : glib.o


%: %.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)