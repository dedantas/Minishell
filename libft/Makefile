# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 19:19:44 by dedantas          #+#    #+#              #
#    Updated: 2025/04/27 16:40:03 by dedantas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome da biblioteca
NAME = libft.a

# Busca automática de fontes
SRCS = ./ft_calloc.c ./ft_strncmp.c ./ft_memcmp.c ./ft_toupper.c \
      ./ft_atoi.c ./ft_tolower.c ./ft_strmapi.c ./ft_strlcpy.c \
      ./ft_memchr.c ./ft_isascii.c ./ft_isdigit.c ./ft_memmove.c \
      ./ft_striteri.c ./ft_strnstr.c ./ft_memset.c ./ft_memcpy.c \
      ./ft_bzero.c ./ft_strchr.c ./ft_strtrim.c ./ft_strrchr.c \
      ./ft_isalpha.c ./ft_isprint.c ./ft_strdup.c ./ft_strlen.c \
      ./ft_isalnum.c ./ft_strjoin.c ./ft_split.c ./ft_putchar_fd.c \
      ./ft_itoa.c ./ft_substr.c ./ft_putstr_fd.c ./ft_putnbr_fd.c \
      ./ft_strlcat.c ./ft_putendl_fd.c ./ft_strcmp.c ./ft_isspace.c\
      ./ft_lstnew_bonus.c ./ft_lstadd_back_bonus.c ./ft_strjoin3.c\
 	./ft_lstadd_front_bonus.c ./ft_lstlast_bonus.c \
        ./ft_lstsize_bonus.c ./ft_lstdelone_bonus.c \
       ./ft_lstclear_bonus.c ./ft_lstiter_bonus.c \
             ./ft_lstmap_bonus.c
PRINTF = ft_printf/ft_printf.c ft_printf/ft_printf_utils.c ft_printf/ft_put.c
GNL = get_next_line/get_next_line.c

# Objetos
OBJS = $(SRCS:.c=.o) $(PRINTF:.c=.o) $(GNL:.c=.o)

# Comandos
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -f

# Regra padrão
all: $(NAME)

# Regra de compilação implícita correta
.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

# Construção da biblioteca
$(NAME): ${OBJS}
	${AR} $(NAME) $(OBJS)
	@echo Compiled
# Limpeza
clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
