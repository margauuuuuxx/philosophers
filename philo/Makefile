NAME	= philo
INCS	= includes
CC		= cc 
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -f

SRCS	= srcs/actions.c srcs/init.c srcs/main.c \
		 srcs/parsing.c srcs/routine.c srcs/safe.c srcs/utils.c srcs/utils2.c
OBJSDIR	= objects
OBJS	= $(SRCS:srcs/%.c=$(OBJSDIR)/%.o)

#CFLAGS_SANITIZE = -fsanitize=address -g3

all:	$(NAME)

$(OBJSDIR)/%.o: srcs/%.c
		@mkdir -p $(OBJSDIR)/srcs
		@$(CC) $(CFLAGS) -I $(INCS) -c $< -o $@ #-fsanitize=address -g3

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) #-fsanitize=address -g3
		@echo "Compiling all object files"
		@echo "Program ready ! :)"

clean:
		@$(RM) -r $(OBJSDIR)

fclean: clean
		@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re