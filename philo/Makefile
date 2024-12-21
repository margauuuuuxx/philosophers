NAME	= philo
CC		= cc 
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -f

SRCS	= srcs/dinner.c srcs/display.c srcs/getters_setters.c srcs/init.c srcs/main.c \
			srcs/monitor.c srcs/parsing.c srcs/safe.c srcs/synchro_utils.c srcs/utils.c
OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "Compiling all object files"
		@echo "Program ready ! :)"

%.o: %.c
		@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(RM) $(OBJS)

fclean:
		@$(RM) $(OBJS) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
