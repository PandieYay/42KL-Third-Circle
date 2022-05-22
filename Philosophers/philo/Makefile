NAME = philo
SRCS = ./main.c
FLAGS = -Wall -Wextra -Werror -g -pthread

all: $(NAME)

$(NAME): ${SRCS}
	gcc ${FLAGS} -o ${NAME} ${SRCS}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re