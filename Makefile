
NAME = push_swap

SRCS = push_swap.c command_push.c command_reverse.c\
		command_rotate.c command_swap.c create_stack.c\
		exceptions_handling.c extract_values.c\
		sort_many_nodes.c sort_three_nodes.c\
		stack_calculations.c update_nodes.c
OBJS = $(SRCS:.c=.o)

ARG ?= "4 67 3 87 23 -234"
CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -fsanitize=address
RM = rm -f
COMMIT_MSG ?= Auto-commit from Makefile

# Detect the Operating System
UNAME := $(shell uname -s)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "The project has been compiled."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

norm:
	@echo "\n\n========== RUNNING NORMINETTE ==========\n\n"
	@norminette -R CheckForbiddenSourceHeader || true
	@echo "\n\n========= THE RESULTS END HERE =========\n\n"

#change ARG by running like this: make test ARG="1 2 3" 
test:
	$(CC) $(SRCS) $(CFLAGS) $(DEBUG_FLAGS) -o $(NAME)
	@echo "Push_swap has been compiled."
	@echo "\nRunning the test...\n"
	@echo "Push_swap output:"
	@./$(NAME) $(ARG)
	@echo "\nRunning Checker:"
# use chmode on the program file if it fails to run
ifeq ($(UNAME),Darwin)
	@./$(NAME) $(ARG) | ../checker_Mac $(ARG)
else
	@./$(NAME) $(ARG) | ../checker_linux $(ARG)
endif
	@$(RM) $(NAME)
	@echo "\nTest is concluded.\n"

#this rule calls Valgrind or Leaks depending on the OS
valgrind:
ifeq ($(UNAME),Darwin)
	@echo "Using Leaks for memory checking."
	@$(CC) $(CFLAGS) $(SRCS) -g -o $(NAME)
	@leaks --atExit -- ./$(NAME) $(ARG)
	@$(RM) $(NAME)
	@$(RM) -r $(NAME).dSYM
else
	@echo "Using Valgrind for memory checking."
	@$(CC) $(CFLAGS) $(SRCS) -g -o $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --track-fds=yes --verbose ./$(NAME) $(ARG)
	@$(RM) $(NAME)
endif

#calls GDB or LLDB depending on the detected OS
gdb:
ifeq ($(UNAME),Darwin)
	@echo "Using LLDB."
	@$(CC) $(CFLAGS) $(SRCS) -g -o $(NAME)
	@lldb ./$(NAME) $(ARG)
	@$(RM) $(NAME)
	@$(RM) -r $(NAME).dSYM
else
	@echo "Using GDB."
	@$(CC) $(CFLAGS) $(SRCS) -g -o $(NAME)
	@gdb -iex "set auto-load safe-path $(CURDIR)" ./$(NAME) $(ARG)
	@$(RM) $(NAME)
endif

git:
	@if [ -n "$$(git status --porcelain)" ]; then \
		echo "The following changes will be added + commited + pushed"; \
		echo "(M = modified, ? = untracked, D = deleted, ! = ignored):\n"; \
		git status --porcelain; \
		echo ""; \
		read -p "Commit message (press \"Enter\" to send default or \"Ctrl+C\" to cancel): " msg; \
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

.PHONY: all norm test valgrind gdb git clean fclean re
