# The example file should compile with any C or C++ compiler that supports the C89 (ANSI C) standard or later, or C++11 or later.
# Try changing both the compiler and the standard and see how little you need to change to get it to compile.
CC=gcc
STD=c99

all: compile run

compile:
	@echo "Compiling..."
	@$(CC) -o example example.c -std=$(STD) -Wall -Wextra -Werror -Wpedantic -Wno-uninitialized -Wno-unused-function

run:
	@echo "Running..."
	@./example

update:
	@echo "Updating..."
	@git add .
	@git commit -m "Minor Update"
	@git push -u origin main