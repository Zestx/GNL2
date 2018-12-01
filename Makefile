CC=gcc
CFLAGS := -Wall -Wextra --pedantic
#CFLAGS += -Werror
CFLAGS += -Wimplicit-function-declaration
CFLAGS += -g -O0

all: test_gnl

test_gnl: libft/libft.a get_next_line.o main.o
	$(CC) $(CFLAGS) -o test_gnl $^


libft/libft.a:
	make -C libft/

clean:
	rm *.o

fclean: clean
	rm test_gnl


export CFLAGS
export CC
