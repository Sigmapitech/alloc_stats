CC = cc

SRC += resolve_symbol.c
SRC += print_stats.c
SRC += wrap_allocation.c
SRC += wrap_exit.c

OBJ := $(SRC:.c=.o)
LIB := libmy_malloc.so

.PHONY: all
all: $(LIB)

$(LIB): $(OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) $(OBJ)

.PHONY: fclean
fclean: clean
	$(RM) $(LIB)

.PHONY: re
re: fclean
	$(MAKE) all
