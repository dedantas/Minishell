NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC			= src/main.c
OBJ			= $(SRC:.c=.o)
#SANITIZER	= -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(SANITIZER)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re