#-*- Makefile -*-

#target : dependencies
#       action

CFLAGS = -Wall -Wextra -Werror
MAND = actions.c basics.c create.c main.c table.c utils.c
OBJ_MAND = $(MAND:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ_MAND)
		cc $(CFLAGS) -g $(OBJ_MAND) -o $(NAME) -lpthread -lrt

clean:
		rm -rf $(OBJ_MAND)

fclean: clean
		rm -f $(NAME)

re : fclean all

.PHONY: $(NAME)
