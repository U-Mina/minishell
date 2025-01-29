NAME = minishell

CFLAGS = -Wall -Wextra -Werror
READLINE_FLAGS = -lreadline

SRC_DIR = src
OBJ_DIR = obj

VPATH =	$(SRC_DIR):$(SRC_DIR)/mini_manager:$(SRC_DIR)/token:$(SRC_DIR)/parse_ast:$(SRC_DIR)/exec:\
		$(SRC_DIR)/builtins:$(SRC_DIR)/signals:$(SRC_DIR)/gc:$(SRC_DIR)/error:$(SRC_DIR)/utils:$(SRC_DIR)/expand_env

SOURCES =	minishell.c\
			tokenizer.c\
			token_make.c\
			ft_isspace.c\
			ft_issep.c\
			parser.c\
			parse_cmd.c\
			parse_pipe.c\
			parse_redir.c\
			init_node.c\
			quote_utils.c\
			free_ast.c\
			expand_env.c\
			executor.c\
			exec_cmd.c\
			exec_cmd_binary.c\
			exec_cmd_builtin.c\
			exec_pipe.c\
			exec_redir.c\
			exec_redir_heredoc.c\
			exec_redir_in.c\
			exec_redir_out.c\
			cd.c\
			echo.c\
			env_utils.c\
			env_utils2.c\
			env_utils3.c\
			env.c\
			exit.c\
			export.c\
			export_only.c\
			export_args.c\
			hepler_utils.c\
			pwd.c\
			unset.c\
			gc_itoa.c\
			gc_list_utils.c\
			gc_malloc_free.c\
			gc_split.c\
			gc_strdup.c\
			gc_strjoin.c\
			gc_strtrim.c\
			gc_substr.c\
			init.c\
			reset.c\
			term.c\
			signal_handler.c\
			error_exit.c\
			handle_error.c

OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJECTS) $(LIBFT)
	cc $(CFLAGS) $(OBJECTS) -L$(LIBFT_DIR) -lft $(READLINE_FLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	cc $(CFLAGS) -I$(LIBFT_DIR) -Iinc -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean : 
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY : all clean fclean re