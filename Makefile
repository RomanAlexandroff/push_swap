NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werrorß 

SRCS = push_swap.c command_push.c command_reverse.c\
		command_rotate.c command_swap.c create_stack.c\
		exceptions_handling.c extract_values.c\
		sort_many_nodes.c sort_three_nodes.c\
		stack_calculations.c update_nodes.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "The project has been compiled."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean :
	@rm -f $(OBJS)
	@echo "Object files have been removed."

fclean : clean
	@rm -f $(NAME)
	@echo "Executable has been removed."

re : fclean all
	@echo "Rebuilding the project is complete."
