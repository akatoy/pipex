NAME = pipex

CC = clang
CFLAGS = -Wall -Wextra -Werror

INC = ./inc/pipex.h

SRC = \
	./src/pipex.c \
	./src/ft_split.c \
	./src/ft_strjoin.c \
	./src/ft_strlen.c \
	./src/ft_strnstr.c \

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re