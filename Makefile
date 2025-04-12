NAME		= ft_ls
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I./include

SRCS 		= src/main.c src/parser.c

# Convert source files into object files
OBJS 		= $(SRCS:.c=.o)

# Default target
all: $(NAME)

# Link all object files to create executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Pattern rule for compiling .c files into .o files
src/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
