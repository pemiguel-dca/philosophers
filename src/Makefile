#-*- Makefile -*-

#target : dependencies
#       action

CFLAGS = -Wall -Wextra -Werror
MAND = actions.c basics.c create.c main.c table.c utils.c utils2.c
OBJ_MAND = $(MAND:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ_MAND)
		cc $(CFLAGS) -g $(OBJ_MAND) -o $(NAME) -lpthread

clean:
		rm -rf $(OBJ_MAND)

fclean: clean
		rm -f $(NAME)

re : fclean all

run: all clean
	./philo 5 400 100 50 2

.PHONY: $(NAME)
