NAME		=	woody_woodpacker

SRC			=	woody_woodpacker.c

OBJ         =   $(SRCS:.cpp=.o)

CC          =   gcc -Wall -Wextra -Werror

RM          =   rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) -o $(NAME)
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all