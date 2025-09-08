# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# SRC = *.c
# OBJS = $(SRC:.c=.o)
# NAME = philo
# AR = ar rcs
# LIB_PATH = ./libft
# LIBFT = $(LIB_PATH)/libft.a
# HEADER = philo.h

# all: $(LIBFT) $(NAME)

# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# $(LIBFT):
# 	make -C $(LIB_PATH) all

# %.o: %.c $(HEADER)
# 	$(CC) -c $(CFLAGS) -I ./ $< -o $@

# fclean: clean
# 	make -C $(LIB_PATH) fclean
# 	rm -rf $(NAME)

# clean:
# 	rm -f $(OBJS)
# 	make -C $(LIB_PATH) clean

# re: fclean all

# .PHONY: all clean fclean re

CC = cc
CFLAGS =-pthreads
SRC = main.c utils.c init.c routine.c
OBJS = $(SRC:.c=.o)
NAME = philo
AR = ar rcs
HEADER = philo.h

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) -I ./ $< -o $@

fclean: clean
	make -C fclean
	rm -rf $(NAME)

clean:
	rm -f $(OBJS)
	make -C clean

re: fclean all

.PHONY: all clean fclean re