
NAME =		philo
SRC =		activity.c\
			init.c\
			parse_input.c\
			philo.c\
			utils.c
OBJ_DIR =	obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CFLAGS = -Wall -Wextra -Werror

PURPLE = \033[0;35m
RESET = \033[0m

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@cc $(OBJ) -o $(NAME)
	@printf "$(PURPLE)compiled successfully\n$(RESET)"

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@printf "cleaned\n"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re