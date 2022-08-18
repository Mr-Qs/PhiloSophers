NAME	= Philo

CC		= gcc -pthread

FLAGS	= -Wall -Werror -Wextra

SRC		= srcs/philo.c srcs/philo_utils.c srcs/philo_data.c

OBJ		= $(SRC:.c=.o)

RM		= rm -rf

All: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) $(FLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)
 
re: fclean $(NAME)