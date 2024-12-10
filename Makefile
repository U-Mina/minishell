NAME = minishell

CFLAGS = -Wall -Wextra -Werror

SOURCES = 	minishell.c\
			lexer.c\
			parser.c
OBJECTS = $(SOURCES:.c=.o)
HEADER = minishell.h

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all : $(NAME)

$(NAME) : $(OBJECTS) $(LIBFT)
	cc $(CFLAGS) $(OBJECTS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

%.o: %.c $(HEADER)
	cc $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean : 
	rm -f $(OBJECTS)
	make clean -C $(LIBFT_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY : all clean fclean re