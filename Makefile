NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT	= libft/libft.a
SRC	= src/main.c src/ultils.c src/exec.c src/buitins.c
OBJ	= $(SRC:.c=.o)
#SANITIZER	= -fsanitize=thread

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME) $(SANITIZER)

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
