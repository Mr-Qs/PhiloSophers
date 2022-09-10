# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 01:29:58 by mrobaii           #+#    #+#              #
#    Updated: 2022/09/10 19:20:06 by mrobaii          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Philo

SRC		= srcs/philo.c srcs/philo_utils.c srcs/philo_data.c

CC		= gcc -pthread

FLAGS	= -Wall -Werror -Wextra

RM		= rm -rf

OBJ		= $(SRC:.c=.o)

All: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) $(FLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)
 
re: fclean $(NAME)
