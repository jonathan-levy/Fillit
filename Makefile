# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: famartin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/16 18:42:57 by famartin          #+#    #+#              #
#    Updated: 2018/03/16 18:50:43 by famartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = main.c fillit_read.c fillit_tetromino.c fillit_solve.c \
		ft_bzero.c ft_strsplit.c ft_putchar.c ft_putstr.c \
		ft_strlen.c ft_memdel.c ft_memset.c ft_sqrt.c ft_putstr_fd.c \
		ft_wordcount.c ft_wordlen.c

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror 

SRCDIR = .

all: $(NAME)

%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf  $(NAME)

re: fclean all
