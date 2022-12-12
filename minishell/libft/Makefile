SRCS := ./ft_atoi.c ./ft_bzero.c ./ft_calloc.c ./ft_isalnum.c ./ft_isalpha.c ./ft_isascii.c \
		./ft_isdigit.c ./ft_isprint.c ./ft_memchr.c ./ft_memcmp.c ./ft_memcpy.c ./ft_memmove.c ./ft_memset.c \
		./ft_strchr.c ./ft_strdup.c ./ft_strjoin.c ./ft_strlcat.c ./ft_strlcpy.c ./ft_strlen.c \
		./ft_strncmp.c ./ft_strnstr.c ./ft_strrchr.c ./ft_strtrim.c ./ft_substr.c ./ft_tolower.c ./ft_toupper.c \
		./ft_split.c ./ft_itoa.c ./ft_strmapi.c ./ft_striteri.c ./ft_putchar_fd.c ./ft_putstr_fd.c ./ft_putendl_fd.c \
		./ft_putnbr_fd.c ./get_next_line.c

SRCS_BONUS :=	./ft_lstnew.c ./ft_lstadd_front.c ./ft_lstsize.c ./ft_lstlast.c ./ft_lstadd_back.c ./ft_lstdelone.c ./ft_lstclear.c \
				./ft_lstiter.c ./ft_lstmap.c

OBJS_BONUS := ${SRCS_BONUS:.c=.o}

OBJS := ${SRCS:.c=.o}

NAME := libft.a

CC := gcc -Wall -Werror -Wextra

RED := \033[0;31m
GREEN := \033[0;32m
BLUE := \033[0;34m
PURPLE := \033[0;35m
YELLOW := \033[0;33m
CYAN := \033[0;36m
NC := \033[0m

$(NAME) : ${OBJS}
		@ar rcs ${NAME} ${OBJS}
		@echo "${GREEN}Libft library created.${NC}"

all : $(NAME)

bonus : ${OBJS_BONUS}
		@ar rcs ${NAME} ${OBJS_BONUS}

%.o : %.c
		@${CC} -c $<

clean :
		@rm -f ${OBJS} ${OBJS_BONUS}

fclean : clean
		@rm -f libft.a

re : fclean all

.PHONY : clean fclean all bonus re