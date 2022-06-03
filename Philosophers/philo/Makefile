NAME = philo
NOTLIBFT = notlibft/ft_atoi.c notlibft/ft_atoichecker.c
SRCS = ./main.c ./errorhandling.c ./msleep.c ./printfunctions.c ./initializestuff.c
FLAGS = -Wall -Wextra -Werror -pthread
# -fsanitize=thread -g3

all: $(NAME)

$(NAME): ${SRCS}
	gcc ${FLAGS} -o ${NAME} ${SRCS} ${NOTLIBFT}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re