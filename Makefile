
NAME = push_swap

SRCS = push_swap.c command_push.c command_reverse.c\
		command_rotate.c command_swap.c create_stack.c\
		exceptions_handling.c extract_values.c\
		sort_many_nodes.c sort_three_nodes.c\
		stack_calculations.c update_nodes.c
OBJS = $(SRCS:.c=.o)

ARG ?= "4 67 3 87 23 -234 0"
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "The project has been compiled."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# change ARG by running like this: make test ARG="1 2 3" 
test:
	@make -C ../push_swap_tester
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "Push_swap has been compiled."
	@echo "\nRunning the test...\n"
	@echo "Push_swap output:"
	@./$(NAME) $(ARG)
	@echo "\nRunning Checker:"
	@./$(NAME) $(ARG) | ./checker $(ARG)
	@$(RM) $(NAME)
	@$(RM) checker
	@echo "\nTest is concluded.\n"

norm:
	@echo "\n\n========== RUNNING NORMINETTE ==========\n\n"
	@norminette -R CheckForbiddenSourceHeader
	@echo "\n\n========= THE RESULTS END HERE =========\n\n"

git:
	@if [ -n "$$(git status --porcelain)" ]; then \
		read -p "Commit message: " msg; \
		if [ -z "$$msg" ]; then \
			msg="$(COMMIT_MSG)"; \
		fi; \
		echo "Committing with message: $$msg"; \
		git add .; \
		git commit -m "$$msg"; \
		git push; \
	else \
		echo "No changes detected."; \
	fi

clean :
	@$(RM) $(OBJS)
	@echo "Object files have been removed."

fclean : clean
	@$(RM) $(NAME)
	@echo "Executable has been removed."

re : fclean all
	@echo "Rebuilding the project is complete."

.PHONY: all norm git clean fclean re