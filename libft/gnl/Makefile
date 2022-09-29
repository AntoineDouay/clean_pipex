# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adouay <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 20:53:27 by adouay            #+#    #+#              #
#    Updated: 2022/09/26 15:09:17 by adouay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

CC = gcc -Wall -Wextra -Werror

SRC = get_next_line_bonus.c \
	get_next_line_utils_bonus.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	echo "\033[33mMaking Gnl\033[0m"
	ar rc $(NAME) $^
	echo "\033[32mDone\033[0m"

%.o : %.c
	$(CC) -c $^

bonus : $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
.SILENT :
