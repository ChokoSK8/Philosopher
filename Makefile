NAME	= philo

SRCS	= main.c ft_isdigit.c ft_atoi.c make_thread.c make_tasks.c tools.c ft_itoa.c ft_strjoin.c init_philo.c free_params.c

OBJS	= $(SRCS:.c=.o)

RM		= rm -rf

INC		= -I includes/

FLAGS	= -Wall -Werror -Wextra -g3 -g -pthread

%.o: %.c
	gcc $(FLAGS) $(INC) -o $@ -c $?

all:	$(NAME)

$(NAME):	$(OBJS)
		gcc $(FLAGS) $(OBJS) -o $(NAME)

clean:
		$(RM) *.o

fclean:		clean
			$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
