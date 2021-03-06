NAME = system

DIRSRC = ./srcs/
DIROBJ = ./.obj/

SRC  = 	main.cpp\
		annexe.cpp\
		checkInput.cpp\
		System.cpp\
		SystemSolver.cpp\
		SystemExceptions.cpp\
		Rule.cpp\

OBJ = $(SRC:.cpp=.o)

DIROBJS = $(addprefix $(DIROBJ), $(OBJ))

HEADERS =	-I  ./headers/\
			-I ~/.brew/Cellar/boost/1.57.0/include/

CC = clang++
CFLAGS= -Wall -Werror -Wextra -std=c++11

all: $(NAME)

$(NAME): $(DIROBJS)
	@$(CC) $(CFLAGS) -o $@ $^
	@printf 'Compiling %s : [\033[32mDONE\033[0m]\n' '$(NAME)'

$(DIROBJ)%.o: $(DIRSRC)%.cpp
	@mkdir -p $(DIROBJ)
	@$(CC) $(CFLAGS) -c $^ $(HEADERS) -o $@
	@printf 'Compiling %s: [\033[32mDONE\033[0m]\n' '$^'

clean:
	@rm -rf $(DIROBJ)
	@printf 'Clean %s : [\033[32mDONE\033[0m]\n' '$(NAME)'

fclean: clean
	@rm -rf $(NAME)
	@printf 'Fclean %s : [\033[32mDONE\033[0m]\n' '$(NAME)'

re : fclean all

test: $(NAME)
	@./$(NAME) misc/4x4.txt

.PHONY: all clean fclean re