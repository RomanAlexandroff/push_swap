
NAME = push_swap

SRCS = push_swap.c benchmark_mode.c command_push.c command_reverse.c\
		command_rotate.c command_swap.c compute_disorder.c create_stack.c\
		exceptions_handling.c flags_handling.c medium_strategy.c\
		simple_strategy.c sort_many_nodes.c sort_three_nodes.c\
		split_arguments.c stack_calculations.c update_nodes.c\
		complex_strategy.c adaptive_strategy.c
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
	@leaks --atExit -- ./$(NAME) --medium $(ARG)
	@$(RM) $(NAME)
	@$(RM) -r $(NAME).dSYM
else
	@echo "Using Valgrind for memory checking."
	@$(CC) $(CFLAGS) $(SRCS) -g -o $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --track-fds=yes --verbose ./$(NAME) $(ARG)
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

# pulls new updates from GitHub, helps update feature branches
update:
	@clear
	@echo "============================================================"
	@echo "                 GIT UPDATE WORKFLOW"
	@echo "============================================================"
	@echo ""
	@echo "Checking for uncommitted changes..."
	@if ! git diff --quiet || ! git diff --cached --quiet; then \
		echo ""; \
		echo "ERROR: You have uncommitted changes."; \
		echo "Please commit or stash them before running this rule."; \
		echo ""; \
		git status; \
		exit 1; \
	fi
	@echo "Working tree is clean."
	@echo ""

	@CURRENT_BRANCH=$$(git branch --show-current); \
	echo "Current branch: $$CURRENT_BRANCH"; \
	echo ""; \
	echo "Fetching latest updates from GitHub..."; \
	git fetch origin; \
	echo ""; \
	echo "Switching to the refactor branch..."; \
	git checkout refactor; \
	echo ""; \
	echo "Merging latest updates from origin/refactor into local refactor..."; \
	git merge origin/refactor; \
	echo ""; \
	echo "============================================================"; \
	echo "LOCAL BRANCHES"; \
	echo "============================================================"; \
	git branch; \
	echo ""; \
	echo "You may now choose a feature branch to update"; \
	echo "with the newest changes from the refactor branch."; \
	echo "Please, do not use this rule to update main branch."; \
	echo ""; \
	echo "OPTIONS:"; \
	echo "- You can press ENTER without typing anything to skip this step."; \
	echo "- You can run this rule multiple times if you want to update"; \
	echo "  several feature branches."; \
	echo ""; \
	printf "Enter branch name to update: "; \
	read FEATURE_BRANCH; \
	echo ""; \
	if [ -z "$$FEATURE_BRANCH" ]; then \
		echo "No feature branch selected."; \
		echo "Skipping feature branch update."; \
		echo ""; \
		echo "Returning to original branch: $$CURRENT_BRANCH"; \
		git checkout $$CURRENT_BRANCH; \
		echo ""; \
		echo "============================================================"; \
		echo "FINAL STATUS"; \
		echo "============================================================"; \
		echo "Current branch:"; \
		git branch --show-current; \
		exit 0; \
	fi; \
	if ! git show-ref --verify --quiet refs/heads/$$FEATURE_BRANCH; then \
		echo "ERROR: Branch '$$FEATURE_BRANCH' does not exist."; \
		echo ""; \
		echo "Returning to original branch: $$CURRENT_BRANCH"; \
		git checkout $$CURRENT_BRANCH; \
		exit 1; \
	fi; \
	echo "Switching to branch: $$FEATURE_BRANCH"; \
	git checkout $$FEATURE_BRANCH; \
	echo ""; \
	echo "Merging latest changes from refactor into $$FEATURE_BRANCH..."; \
	echo ""; \
	if git merge refactor; then \
		echo ""; \
		echo "============================================================"; \
		echo "MERGE SUCCESSFUL"; \
		echo "============================================================"; \
		echo "Branch '$$FEATURE_BRANCH' is now updated."; \
	else \
		echo ""; \
		echo "============================================================"; \
		echo "MERGE CONFLICT DETECTED"; \
		echo "============================================================"; \
		echo ""; \
		echo "Git could not merge automatically."; \
		echo ""; \
		echo "HOW TO RESOLVE USING VS CODE:"; \
		echo ""; \
		echo "1. Open VS Code in the repository using this command:"; \
		echo "      code ."; \
		echo ""; \
		echo "2. Open the files marked with conflicts (with "!" next to their names)."; \
		echo ""; \
		echo "3. VS Code will show sections like:"; \
		echo ""; \
		echo "      <<<<<<< HEAD"; \
		echo "      your code"; \
		echo "      ======="; \
		echo "      incoming code"; \
		echo "      >>>>>>> refactor"; \
		echo ""; \
		echo "4. Use the VS Code buttons:"; \
		echo "      - Accept Current Change"; \
		echo "      - Accept Incoming Change"; \
		echo "      - Accept Both Changes"; \
		echo ""; \
		echo "5. Edit the code until the conflict is resolved."; \
		echo ""; \
		echo "6. Save the files."; \
		echo ""; \
		echo "7. Mark conflicts as resolved:"; \
		echo "      git add <filename>"; \
		echo ""; \
		echo "8. Complete the merge:"; \
		echo "      git commit"; \
		echo ""; \
		echo "9. Push updated branch to GitHub:"; \
		echo "      git push"; \
		echo ""; \
		echo "IMPORTANT:"; \
		echo "Do NOT run this Makefile rule again"; \
		echo "until the merge conflict is fully resolved."; \
	fi; \
	echo ""; \
	echo "============================================================"; \
	echo "FINAL STATUS"; \
	echo "============================================================"; \
	echo "Current branch:"; \
	git branch --show-current

clean :
	@$(RM) $(OBJS)
	@echo "Object files have been removed."

fclean : clean
	@$(RM) $(NAME)
	@echo "Executable has been removed."

re : fclean all
	@echo "Rebuilding the project is complete."

.PHONY: all norm test valgrind gdb git update clean fclean re
