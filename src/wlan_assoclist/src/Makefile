LDFLAGS +=

PROC=assoclist_demo
SRC=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

all : $(PROC)
	@echo "compile done"

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(PROC): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -fr $(PROC) $(OBJS)
