NAME = philosiphers
SRC = main.c daily_routine.c   p_libs.c parse_args.c habits.c

CFLAGS = -Wall -Wextra -Werror -g3
CC = gcc
OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)



clean:
	@rm -f *.o

fclean: clean 
	@rm -f $(NAME) 
	@rm -f push_swap
	
re: fclean all

