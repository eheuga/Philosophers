NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -Iinclude
SRCS = main.c routine.c init/init_data.c init/init_philos.c init/init_mutex.c utils/get_time.c utils/print_action.c utils/ft_usleep.c action.c utils/free_all.c
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
