# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 02:32:33 by mrobaii           #+#    #+#              #
#    Updated: 2022/09/08 17:58:36 by mrobaii          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		Philo_Bonus

SRC			=		Philo_bonus.c Philo_bonus_utils.c philo_utils.c

CC			=		gcc

FLAGS		=		-Wall -Werror -Wextra 

RM			=		rm -rf

OBJ			=		$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) $(FLAGS) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean $(NAME)
