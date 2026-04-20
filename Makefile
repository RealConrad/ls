NAME	= ft_ls

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCDIR	= srcs
OBJDIR	= objs
INCDIR	= includes

SRCS	= $(SRCDIR)/main.c \
		  $(SRCDIR)/parse_args.c \
		  $(SRCDIR)/args_array.c \
		  $(SRCDIR)/execute.c \
		  $(SRCDIR)/utils.c \
		  $(SRCDIR)/error.c \
		  $(SRCDIR)/format_long_output.c

OBJS	= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/ft_ls.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re