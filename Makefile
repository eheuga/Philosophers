NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = main.c init/init_data.c init/init_philos.c init/init_mutex.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re