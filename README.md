*This project has been created as part of the 42 curriculum by roaleksa.*

# Push Swap

<br>

## Table of Contents

- [Description](#description)
- [Detailed Algorithm Description](#detailed-algorithm-description)
- [Instructions](#instructions)
- [Usage](#usage)
- [Operations](#operations)
- [Project Structure](#project-structure)
- [Function Overview](#function-overview)
- [Resources](#resources)
- [AI Usage Disclosure](#ai-usage-disclosure)

<br>

## Description

Push Swap is a 42 school project whose goal is to sort a list of integers using only two stacks and a limited set of stack operations. The program must produce a valid sequence of moves that sorts the input values in ascending order. Efficiency is essential: the solution should minimize the number of operations used to sort the data.

This repository contains a C implementation of the Push Swap solver. The input is parsed into a linked-stack representation, validated for duplicates and integer range, then sorted using stack operations only.

---

<br>

## Detailed Algorithm Description

### Stack representation

Stacks are represented as doubly linked lists of `t_node` structures. Each node contains:

- `value`: the integer stored in the node
- `node_position`: its index inside the stack
- `node_before` / `node_after`: pointers to adjacent nodes
- `destination`: target node in stack A for a node in stack B
- `solving_cost`: estimated cost to move the node into position
- `top_half_flag`: indicates whether the node is in the top half of its stack
- `next_to_solve`: marks which node in stack B should be moved next

### Operations

All operations update the head pointers of stack A and stack B, and print the corresponding instruction string to standard output. The supported operations are implemented as separate command functions.

### Input parsing and validation

Input is accepted in two forms:

- multiple command-line arguments: `./push_swap 2 1 3`
- a single quoted string: `./push_swap "2 1 3"`

For the single-string form, `extract_values()` splits the string into separate token strings.

Validation is performed in `create_stack_safely()`:

- `characters_check()` ensures each token contains only digits and an optional leading sign
- the value is converted with a custom `ft_atod()` and verified to fit in `INT_MIN..INT_MAX`
- `duplicates_check()` ensures every number is unique
- valid values are appended to stack A in the original order

If validation fails, the program prints `Error` to standard error and exits.

### Sorting approach

The sorting logic is divided by input size:

- `2` elements: one swap if needed
- `3` elements: `sort_three()` locates the largest element and rotates or reverses to place it, then swaps if necessary
- `> 3` elements: `sort_many()` uses a greedy insertion strategy

The general strategy for larger datasets is:

1. Push all but three elements from stack A to stack B using `pb`
2. Sort the remaining three elements in stack A with `sort_three()`
3. Reinsert elements from stack B into stack A one by one
   - `update_nodes()` computes a destination node in A for each B node
   - each B node is assigned a rotation cost based on its position and its destination position
   - `next_to_solve` selects the B node with minimal total cost
   - `solve_node()` rotates A and B so the selected node and its destination reach the top with minimal moves
   - `pa` pushes the selected node back to stack A
4. At the end, rotate stack A until the lowest value is on top

This is a cost-driven insertion algorithm rather than a radix or chunk sorting algorithm.

### Handling of small vs large datasets

- For `2` elements: the program calls `swap_a()` directly
- For `3` elements: the specialized `sort_three()` routine sorts the stack using at most two operations
- For larger inputs: the algorithm pushes all but three elements to stack B, sorts the remaining three in A, then reinserts B elements based on computed rotation costs

---

<br>

## Instructions

### Compilation

The project is built using the provided `Makefile`. The executable produced is `push_swap`.

Available targets:

- `all`: compile the project and create `push_swap`
- `norm`: run `norminette -R CheckForbiddenSourceHeader` to check formatting rules
- `test`: compile with address sanitizer, run `./push_swap` with the `ARG` variable, then validate using an external checker in `../checker_Mac` or `../checker_linux`
- `valgrind`: compile with debug symbols and run either `leaks` on macOS or `valgrind` on Linux
- `git`: add, commit, and push repository changes if the working tree is dirty
- `clean`: remove object files (`*.o`)
- `fclean`: remove object files and the executable `push_swap`
- `re`: run `fclean` then `all`

### Build details

- Compiler: `cc`
- Compiler flags: `-Wall -Wextra -Werror`
- Debug flags: `-fsanitize=address` (used by `make test`)
- Object files: generated from every `.c` source file in the repository

### Build commands

```bash
make
```

or

```bash
make all
```

To remove all object files:

```bash
make clean
```

To remove the executable and object files:

```bash
make fclean
```

To rebuild from scratch:

```bash
make re
```

---

<br>

## Usage

Run the program with a list of integer arguments:

```bash
./push_swap 2 1 3 6 5 8
```

Or with a single quoted string of values:

```bash
./push_swap "2 1 3 6 5 8"
```

The program prints a sequence of stack operations to standard output. For example, valid output might include:

```bash
pb
sa
pa
```

This output represents the moves the program uses to sort the input.

### Checker program

The repository does not include a checker program. The `Makefile` references an external checker in `../checker_Mac` or `../checker_linux` for the `test` target. If you have a compatible checker available outside this repository, use `make test ARG="..."`.

---

<br>

## Operations

The following operations are implemented in this project:

- `sa`: swap the first two elements of stack A
- `sb`: swap the first two elements of stack B
- `ss`: perform `sa` and `sb` simultaneously
- `pa`: push the top element from stack B to stack A
- `pb`: push the top element from stack A to stack B
- `ra`: rotate stack A upward
- `rb`: rotate stack B upward
- `rr`: perform `ra` and `rb` simultaneously
- `rra`: reverse rotate stack A downward
- `rrb`: reverse rotate stack B downward
- `rrr`: perform `rra` and `rrb` simultaneously

---

<br>

## Project Structure

```text
.
├── Makefile
├── README.md
├── command_push.c
├── command_reverse.c
├── command_rotate.c
├── command_swap.c
├── create_stack.c
├── exceptions_handling.c
├── extract_values.c
├── push_swap.c
├── sort_many_nodes.c
├── sort_three_nodes.c
├── stack_calculations.c
└── update_nodes.c
```

---

<br>

## Function Overview

### Parsing and validation

- `extract_values()`: splits a single string argument into tokens
- `create_stack_safely()`: validates values and builds stack A
- `characters_check()`: verifies token syntax
- `duplicates_check()`: ensures values are unique
- `free_argv_mem()`: frees memory allocated by `extract_values()` when needed
- `free_and_exit()`: prints `Error` and exits on invalid input

### Stack operations

- `swap_a()`, `swap_b()`, `swap_both()`
- `push_to_a()`, `push_to_b()`
- `rotate_a()`, `rotate_b()`, `rotate_both()`
- `reverse_a()`, `reverse_b()`, `reverse_both()`

### Sorting logic

- `sort_three()`: sorts three values in stack A
- `sort_many()`: sorts larger inputs by sending elements to stack B and reinserting them
- `ensure_top()`: brings a node to the top of its stack using rotation direction
- `push_to_a()`: moves the selected node back to stack A during reinsertion

### Stack utilities

- `get_last_node()`: returns the last node in a stack
- `get_lowest_value()`: finds the smallest value in a stack
- `find_next_to_solve()`: locates the best candidate in stack B
- `get_stack_length()`: counts nodes in a stack
- `is_sorted()`: checks whether stack A is already sorted
- `position_update()`: assigns index and half position flags
- `solving_cost_update()`: computes the rotation cost for each B node
- `next_to_solve_update()`: selects the B node with minimal cost
- `update_nodes()`: refreshes stack metadata before each reinsertion

---

<br>

## Resources

- 42 subject
- Algorithm resources on sorting and stack-based sorting
- C documentation
- Head First C — David Griffiths & Dawn Griffiths

---

<br>

## AI usage disclosure

- AI was NOT used to write the project code
- AI was used to help generate Doxygen-style documentation comments
- AI was used to assist in writing this README
- The README was not generated exclusively by AI

---

*Last updated: May 2026*
