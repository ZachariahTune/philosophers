# Основная директория проекта
SRC_DIR	=	./files/

# Параметры сборки и удаления
NAME	=	philo
SRCS	=	philo.c philo_threads.c philo_utils.c philo_puts.c
OBJS	=	$(addprefix $(SRC_DIR),$(SRCS:.c=.o))
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
RM 		= 	rm -f

all:		$(NAME)

$(SRC_DIR)%.o:$(SRC_DIR)%.c
			$(CC) $(CFLAGS) -I $(SRC_DIR) -o $@ -c $< -Ofast

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -lpthread $(OBJS) -Ofast -lm -o $(NAME)

clean:
			${RM} $(OBJS)

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
