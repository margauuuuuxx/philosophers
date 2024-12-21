NAME	= philo
INCS	= includes
CC		= cc 
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -f

SRCS	= srcs/dinner.c srcs/display.c srcs/getters_setters.c srcs/init.c srcs/main.c \
			srcs/monitor.c srcs/parsing.c srcs/safe.c srcs/synchro_utils.c srcs/utils.c
OBJSDIR	= objects
OBJS	= $(SRCS:%.c=$(OBJSDIR)/%.o)

all:	$(NAME)

$(OBJSDIR)/%.o: %.c
		@mkdir -p $(OBJSDIR)/srcs
		@$(CC) $(CFLAGS) -I $(INCS) -c $< -o $@

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "Compiling all object files"
		@echo "Program ready ! :)"

%.o: %.c
		@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(RM) -r $(OBJSDIR)

fclean:
		@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
