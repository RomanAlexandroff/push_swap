*This project has been created as part of the 42 curriculum by ccrucian and roaleksa.*

# push_swap

## Description

`push_swap` is a 42 curriculum project focused on sorting a list of integers using only two stacks and a limited set of stack operations.

The program receives a sequence of unique integers, stores them in stack A, and prints to standard output the operations needed to sort the values in ascending order. Stack B is used as temporary storage during the sorting process.

The goal of the project is not only to sort the numbers correctly, but also to do it using as few operations as possible.

This implementation includes:

- input parsing for both separated arguments and quoted strings
- validation for invalid characters, duplicate numbers, and integer overflow
- linked-list based stack management
- the full set of allowed `push_swap` operations
- three sorting strategies
- an adaptive strategy selector based on input disorder
- an optional benchmark mode

## Instructions

### Compilation

Compile the project with:

```bash
make
```

This creates the executable:

```bash
push_swap
```

The project is compiled with:

```bash
cc -Wall -Wextra -Werror
```

### Makefile targets

Available targets:

- `make`: compiles the project
- `make all`: compiles the project
- `make clean`: removes object files
- `make fclean`: removes object files and the executable
- `make re`: rebuilds the project from scratch
- `make norm`: runs Norminette
- `make test`: compiles with AddressSanitizer and runs a checker if available
- `make valgrind`: runs memory checks with Valgrind on Linux or leaks on macOS
- `make gdb`: starts GDB on Linux or LLDB on macOS

## Usage

Run the program with a list of integers:

```bash
./push_swap 4 2 1 3
```

You can also pass the values as a single quoted string:

```bash
./push_swap "4 2 1 3"
```

The program prints a sequence of operations:

```txt
pb
sa
pa
```

These operations can be passed to a checker program to verify that the stack is correctly sorted.

### Invalid input

If the input is invalid, the program prints:

```txt
Error
```

to standard error.

Examples of invalid input:

```bash
./push_swap 1 2 2
./push_swap 1 abc 3
./push_swap 2147483648
./push_swap --
```

The program rejects:

- non-numeric values
- duplicate integers
- values outside the `int` range
- malformed signs such as `+` or `-` without digits
- unknown flags

## Flags

This implementation supports optional flags.

### Strategy flags

```bash
./push_swap --simple 4 2 1 3
./push_swap --medium 4 2 1 3
./push_swap --complex 4 2 1 3
./push_swap --adaptive 4 2 1 3
```

Available strategies:

- `--simple`: uses the simple selection-based strategy
- `--medium`: uses the chunk-based strategy
- `--complex`: uses binary radix sort
- `--adaptive`: automatically chooses a strategy based on the disorder of the input

If no strategy flag is provided, the program uses adaptive mode by default.

If multiple strategy flags are provided, the last one is used.

### Benchmark flag

```bash
./push_swap --bench 4 2 1 3
```

The `--bench` flag prints benchmark information to standard error, including:

- detected disorder percentage
- selected strategy
- estimated complexity
- total number of operations
- number of times each operation was used

Example:

```bash
./push_swap --bench --adaptive 4 2 1 3
```

## Operations

The project implements the complete set of allowed `push_swap` operations.

### Swap

- `sa`: swap the first two elements of stack A
- `sb`: swap the first two elements of stack B
- `ss`: perform `sa` and `sb` at the same time

### Push

- `pa`: push the first element of stack B to stack A
- `pb`: push the first element of stack A to stack B

### Rotate

- `ra`: rotate stack A upward
- `rb`: rotate stack B upward
- `rr`: perform `ra` and `rb` at the same time

### Reverse rotate

- `rra`: rotate stack A downward
- `rrb`: rotate stack B downward
- `rrr`: perform `rra` and `rrb` at the same time

## Algorithm Explanation and Justification

This project implements three sorting strategies and one adaptive dispatcher.

The strategies were selected to handle different types of input efficiently. Small or nearly sorted inputs do not need a complex algorithm, while highly disordered inputs benefit from a more predictable sorting method.

### Disorder calculation

Before sorting, the program calculates how disordered the input is.

The disorder value is computed by comparing every pair of values in stack A. If a value appears before a smaller value, that pair is considered to be in the wrong order.

The final disorder score is:

```txt
wrong_pairs / total_pairs
```

This produces a value between `0.0` and `1.0`.

- `0.0` means the stack is already sorted
- values close to `0.0` mean the stack is almost sorted
- values close to `1.0` mean the stack is highly disordered

This value is used by the adaptive strategy to choose the most appropriate algorithm.

### Simple strategy

The simple strategy is a selection-sort adaptation for two stacks.

It repeatedly:

1. Finds the smallest value in stack A.
2. Updates node positions.
3. Rotates or reverse-rotates stack A to bring the smallest value to the top.
4. Pushes that value to stack B.
5. Repeats until stack A is empty.
6. Pushes all values back from stack B to stack A.

Because the smallest values are pushed first to B, pushing everything back to A rebuilds the stack in sorted order.

This strategy is simple and useful for inputs with low disorder, but it becomes expensive for larger or random inputs because it repeatedly scans the stack and may perform many rotations.

Estimated complexity:

```txt
O(n²)
```

### Medium strategy

The medium strategy is based on chunks.

First, each node receives a rank called `index`, based on its sorted position. The smallest value receives index `0`, the next smallest receives index `1`, and so on.

Then the algorithm divides the input into approximately `sqrt(n)` chunks.

For each chunk, the program:

1. Searches stack A for values whose indexes belong to the current chunk.
2. Chooses the closest matching value from either the top or the bottom of stack A.
3. Rotates stack A using the shortest direction.
4. Pushes the selected value to stack B.
5. Rotates stack B when useful to keep larger values easier to retrieve later.

After all chunks have been pushed to stack B, the program rebuilds stack A by repeatedly finding the largest index in B, moving it to the top, and pushing it back to A.

This strategy is a compromise between the simple strategy and radix sort. It reduces unnecessary scans and rotations while keeping the logic relatively easy to control.

Estimated complexity:

```txt
O(n√n)
```

### Complex strategy

The complex strategy uses binary radix sort.

Before sorting, all values are compressed into indexes from `0` to `n - 1`. This makes the algorithm independent from the original integer values, including negative numbers and very large or very small valid integers.

The algorithm then sorts the stack bit by bit.

For each bit position:

1. Read the selected bit of the index at the top of stack A.
2. If the bit is `1`, rotate stack A.
3. If the bit is `0`, push the element to stack B.
4. After one full pass through stack A, push everything from B back to A.
5. Continue with the next bit.

After all necessary bits have been processed, stack A is sorted.

Radix sort was selected for highly disordered inputs because it is predictable, stable for indexed values, and scales better than the simpler strategies.

Estimated complexity:

```txt
O(n log n)
```

### Adaptive strategy

The adaptive strategy is the default mode.

It chooses the sorting strategy based on the disorder score:

- disorder `< 0.2`: simple strategy
- disorder `>= 0.2` and `< 0.5`: medium strategy
- disorder `>= 0.5`: complex strategy

This makes the program flexible:

- nearly sorted inputs avoid unnecessary heavy sorting
- moderately mixed inputs use chunk sorting
- highly disordered inputs use radix sort

The adaptive strategy was chosen to balance operation count, implementation clarity, and behavior across different input patterns.

## Project Structure

Main files:

- `push_swap.c`: program entry point and strategy dispatcher
- `push_swap.h`: shared structures, constants, and function prototypes
- `create_stack.c`: stack creation and integer conversion
- `exceptions_handling.c`: input validation and memory cleanup
- `split_arguments.c`: argument splitting
- `split_arguments_utils.c`: helper functions for argument splitting
- `flags_handling.c`: command-line flag parsing
- `command_swap.c`: swap operations
- `command_push.c`: push operations
- `command_rotate.c`: rotate operations
- `command_reverse.c`: reverse rotate operations
- `simple_strategy.c`: selection-based sorting strategy
- `medium_strategy.c`: chunk-based sorting strategy
- `medium_strategy_utils.c`: helper functions for chunk sorting
- `complex_strategy.c`: binary radix sorting strategy
- `compute_disorder.c`: input disorder calculation
- `stack_calculations.c`: stack utility functions
- `benchmark_mode.c`: benchmark data management
- `benchmark_rendering.c`: benchmark output rendering

## Resources

Classic references and useful material:

- 42 push_swap subject
- C manual 
- GNU Make documentation: https://www.gnu.org/software/make/manual/
- Stack data structure: https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
- Sorting algorithms: GeeksforGeeks, https://en.wikipedia.org/wiki/Sorting_algorithm
- Selection sort: GeeksforGeeks, https://en.wikipedia.org/wiki/Selection_sort
- Radix sort: GeeksforGeeks, https://en.wikipedia.org/wiki/Radix_sort
- Big O notation: https://en.wikipedia.org/wiki/Big_O_notation

## AI Usage Disclosure

AI was used to help review the repository structure and write this README.

Specifically, AI was used for:

- summarizing the purpose of the project
- describing the behavior of the implemented source files
- explaining the selected algorithms
- testing some functions
- writing this README according to the required structure
- improving clarity and readability of the documentation
- norminette 

AI was not used as the source of the project logic itself. The algorithm descriptions in this README are based on the actual implementation found in the repository.