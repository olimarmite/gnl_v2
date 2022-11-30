CC=cc
CFLAGS=-Wall -Wextra -Werror
LIBS=get_next_line.h
SRCS=get_next_line.c  get_next_line_utils.c
BONUS_SRCS=

BONUS_OBJS= ${BONUS_SRCS:.c=.o}
TEST_SRCS = ./test/*.c
NAME=get_next_line.h
OBJS= ${SRCS:.c=.o}

RM = rm -f

all: ${NAME}


${NAME}: ${OBJS}
#	ar -rc ${NAME} ${OBJS}

.c.o:
	${CC} -c ${CFLAGS} $<

bonus: ${BONUS_OBJS}
	ar -rc ${NAME} ${BONUS_OBJS}

clean:
	${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
	${RM} ${NAME}
	${RM} a.out

re: fclean all

.PHONY: all bonus clean fclean re
