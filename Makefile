#	TODO: add proper compilation flags
CC      = cc
CFLAGS  = -pthread
RM      = rm -f

SRC     = main.c utils.c init.c routine.c routine_utils.c
OBJS    = $(SRC:.c=.o)
NAME    = philo
HEADER  = philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
