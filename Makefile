mainFileName = main
srcFiles = src/main.c src/employee.c src/help_lib.c
flags = -std=c11 -Wall -Wextra -Werror

all: main
main:
	@echo Compiling into $(mainFileName).exe
	@gcc $(flags) $(srcFiles) -o $(mainFileName)