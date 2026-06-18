
NAME = push_swap

SRCS = src/push_swap.c src/benchmark_mode/benchmark_mode.c src/benchmark_mode/benchmark_rendering.c\
		src/operations_commands/command_push.c src/operations_commands/command_reverse.c\
		src/operations_commands/command_rotate.c src/operations_commands/command_swap.c\
		src/sorting_strategies/simple_strategy.c src/sorting_strategies/small_sort.c\
		src/sorting_strategies/medium_strategy.c src/sorting_strategies/medium_strategy_utils.c\
		src/sorting_strategies/complex_strategy.c src/user_input_parsing/create_stack.c\
		src/user_input_parsing/flags_handling.c src/user_input_parsing/split_arguments.c\
		src/user_input_parsing/split_arguments_utils.c src/utilities/compute_disorder.c\
		src/utilities/exceptions_handling.c src/utilities/stack_calculations.c

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

# change ARG by running like this: make test ARG="1 2 3" 
test:
	$(CC) $(SRCS) $(CFLAGS) $(DEBUG_FLAGS) -o $(NAME)
	@echo "Push_swap has been compiled."
	@echo "\nRunning the test...\n"
	@echo "Push_swap output:"
	@./$(NAME) $(ARG)
	@echo "\nRunning Checker:"
# use chmode on the program file if it fails to run
ifeq ($(UNAME),Darwin)
	@./$(NAME) --medium $(ARG) | ../checker_Mac $(ARG)
else
	@./$(NAME) --medium $(ARG) | ../checker_linux $(ARG)
endif
	@$(RM) $(NAME)
	@echo "\nTest is concluded.\n"

# this rule calls Valgrind or Leaks depending on the OS
valgrind:
ifeq ($(UNAME),Darwin)
	@echo "Using Leaks for memory checking."
	@$(CC) $(CFLAGS) $(SRCS) -g -o $(NAME)
	@leaks --atExit -- ./$(NAME) $(ARG) --bench --medium
	@$(RM) $(NAME)
	@$(RM) -r $(NAME).dSYM
else
	@echo "Using Valgrind for memory checking."
	@$(CC) $(CFLAGS) $(SRCS) -g -o $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --track-fds=yes --verbose ./$(NAME) --simple --bench $(ARG)
	@$(RM) $(NAME)
endif

# calls GDB or LLDB depending on the detected OS
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

# performs "git add + commit + push" of the branch you're CURRENTLY on
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

.PHONY: all norm test valgrind gdb git update clean fclean re
