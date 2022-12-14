# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adouay <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 12:22:12 by adouay            #+#    #+#              #
#    Updated: 2022/09/27 15:49:52 by adouay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc -Wall -Werror -Wextra

SRC = pipex.c \
	child.c	\
	here_doc.c \
	error.c \
	utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	echo "\033[36mMaking Pipex\033[0m"
	$(CC) $(OBJ) -g -L libft/. -lft -I libft/. -o $(NAME)
	echo "\033[32mDone\033[0m"

bonus : $(NAME)

%.o: %.c
	$(CC) -c $^ 

clean:
	rm -f $(OBJ)
	$(MAKE) fclean -C libft

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all bonus clean fclean re