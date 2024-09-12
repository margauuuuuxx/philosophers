NAME	= philo
CC		= cc 
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

SRCS	= dinner.c display.c getters_setters.c init.c \
			parsing.c safe.c synchro_utils.c utils.c main.c
OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "Compiling all object files"

%.o: %.c
		@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(RM) $(OBJ)

fclean:
		@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re