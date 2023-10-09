CC=x86_64-w64-mingw32-gcc
LIB_NAME=libefi.a
OBJS=console.o init.o string.o pool.o stdlib.o

$(LIB_NAME): $(OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) -O2 -ffreestanding -Iinclude/ -c -o $@ $<

.PHONY: clean

clean:
	rm -rf *.o $(LIB_NAME)
