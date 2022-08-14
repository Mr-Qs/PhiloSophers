NAME	= Philo

CC		= gcc -pthread

FLAGS	= -Wall -Werror -Wextra

SRC		= philo.c philo_utils.c

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