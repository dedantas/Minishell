NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT	= libft/libft.a
SRC	= src/main.c src/ultils.c src/lexer.c src/parser.c \
	  src/heredoc_handle.c src/expand.c src/exec.c src/buitins.c \
	  src/buitins2.c src/buitins3.c src/buitins4.c src/buitins5.c \
	  src/new_add.c src/free.c src/signals.c src/quotes.c \
	  src/exc_utils2.c src/exc_utils.c src/exp_utils.c src/redir.c
OBJ	= $(SRC:.c=.o)
#SANITIZER	= -fsanitize=thread

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME) $(SANITIZER)

$(LIBFT):
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

val:				
					clear
						valgrind --leak-check=full \
						--show-leak-kinds=all \
						--track-origins=yes \
						--suppressions=readline_supressor ./$(NAME)

.PHONY: all clean fclean re
