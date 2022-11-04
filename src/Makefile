SRCS = matrix.c
	
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE -lm

all: matrix.a matrix

matrix.a: ${SRCS}
	${CC} ${CFLAGS} -c ${SRCS}
	@ar rcs matrix.a ${OBJS}
	@ranlib matrix.a

matrix: matrix.a
	@${CC} matrix.a -o matrix
	
clean:
	@rm -rf *.o *.a matrix

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c