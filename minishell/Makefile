NAME := minishell

SRCS_DIR := ./srcs
OBJS_DIR := ./objs

SRCS := main.c inits.c init_utils.c \
		node_utils.c checker.c tokenize.c \
		expand.c expand_utils.c \
		here_doc.c env.c error.c \
		direct.c direct_utils.c \
		parse.c parse_utils.c \
		execution.c execution_utils.c \
		free1.c free2.c \
		cdpwd.c builtins.c exportenv.c exportutils.c \
		exitutils.c
OBJS := $(SRCS:%.c=$(OBJS_DIR)/%.o)

CC := gcc -Wall -Werror -Wextra 

FLAGS := #-g3 -fsanitize=address

# -L "folder" to looks for library in the folder
# -l(ft) to link library file. l replaces lib
LIB := -L./libft -lft -lreadline -L/usr/local/opt/readline/lib
INC_RL	:= -I/usr/local/opt/readline/include

RED := \033[0;31m
GREEN := \033[0;32m
BLUE := \033[0;34m
PURPLE := \033[0;35m
YELLOW := \033[0;33m
CYAN := \033[0;36m
NC := \033[0m

# target : prerequisites
# <TAB> recipe
all : $(NAME)

# "make -C" run make in specific folder
# "-I" is  to look for header file in folder
# "$<" is to match prerequisites
# "$@" is to match target
$(NAME) : $(OBJS)
	make -C ./libft
	$(CC) $(FLAGS) -I includes -I libft $(LIB) $(OBJS) -o $@
	@echo "$(GREEN)Minishell Compiled Successful.$(NC)"

# "mkdir -p" creates dir if necessary, if dir exist, no error specified
# "gcc -c" is to create .o files or object files
# "gcc -o 'file' " use as a naming feature / place the output result to 'file'
$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) -I includes -I libft $(INC_RL) -c $< -o $@

# "echo -e" to allow backslash escapes \ 
clean :
	@rm -rf $(OBJS_DIR)
	@make clean -C ./libft
	@echo "$(YELLOW)Cleaned.$(NC)"

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C ./libft
	@echo "$(RED)Full Cleaned.$(NC)"

re: fclean all

.PHONY: all clean fclean re
