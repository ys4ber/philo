NAME = philo

CC = cc

CFLAGS =  -Wall -Wextra -Werror  -g3 -pthread -fsanitize=thread 


SRCS = main.c  ft_utils.c ft_sleep.c ft_utils1.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS)  $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	
fclean:
	rm -rf $(OBJS) $(NAME)

re: fclean all clean

.PHONY: all clean fclean re