NAME = philo

CC = cc

CFLAGS =  -Wall -Wextra -Werror -fsanitize=address -g3 -pthread


SRCS = main.c

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