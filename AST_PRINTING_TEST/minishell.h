/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:23:28 by ewu               #+#    #+#             */
/*   Updated: 2025/01/17 16:45:36 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h> // for read()
# include <limits.h>
# include <readline/history.h> //readline()
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>

# include <termios.h>

//original_state
typedef struct s_minishell
{
	struct sigaction	sa[2];
	struct sigaction	old_sa[2];
	struct termios		old_term;
}			t_minishell;

typedef struct s_env_var
{
	char	*val;
	int		start;
	int		end;
	int		name_len;
	int		val_len;
}	t_env_var;

typedef enum e_tokentype
{
	WORD, //Will be disambiguated to Command_builtin, Command_binary, argument or filename in the parser
	COMMAND,
	ARGUMENT,
	ENV_VAR,
	QUOTE,
	REDIRECTION, //Will be disambiguated to input, output, append or heredoc
	PIPE,
	TOKEN_EOF
}						t_tokentype;

typedef enum e_redirtype
{
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND
}						t_redirtype;

typedef enum e_cmdtype
{
	COMMAND_BUILTIN,
	COMMAND_BINARY
}						t_cmdtype;

typedef struct s_token
{
	t_tokentype			type;
	char				*value;
	int					i_len;
}				t_token;

typedef struct s_tokenizer
{
	t_token	*tokens;
	int		capacity;
	int		grow;
	int		count;
}			t_tokenizer;

struct s_astnode;

//dont know what we need in this case
typedef struct s_pipe 
{
	struct s_astnode	*right;
	struct s_astnode	*left;

}				t_pipe;

typedef struct s_redir
{
	t_redirtype			type;
	int					fd;
	char				*left;
	struct s_astnode	*right;
}				t_redir;

typedef struct s_cmd
{
	t_cmdtype	type;
	int			arg_nb;
	char		**argv;
	char		*path;
	// int			*exit_status;
	// char		**env; //or wherever it is
}				t_cmd;

typedef union u_nodetype
{
	t_redir	*redir;
	t_cmd	*cmd;
	t_pipe	*pipe;
}			t_nodetype;

typedef struct s_astnode
{
	t_token		*token;
	t_nodetype	node_type;
}				t_astnode;

typedef struct s_data
{
	int					*exit_status;
	char				**env;
	int			heredoc_fd;
	int			fd[2];
	t_astnode			*ast_root;
}						t_data;

//gc_list
typedef struct s_gc_list
{
	void				*allocated;
	struct s_gc_list	*next;
}	t_gc_list;


//init and term
void		init_minishell(t_minishell	*minishell);
void		term_minishell(t_minishell	*minishell, int rv);

//gc
void		*gc_malloc(size_t size);
t_gc_list	**get_gc_list(void);
void		gc_malloc_error(void);
void		add_gc_list(void *new_alloc);
void		gc_free(void *free_ptr);
void		gc_clean(void);
char		*gc_strdup(const char *s1);
char		*gc_substr(char const *s, unsigned int start, size_t len);
char		*gc_strtrim(char const *s1, char const *set);

//lexer-tokenizer
t_token		*tokenizer(char *input);
t_tokenizer	*init_tokenizer(void);
int			grow_tokenizer(t_tokenizer *tokenizer);
void		create_token(t_tokenizer *tokenizer, char *input);
void		free_tokens(t_token *tokens);
void		make_eof_token(t_token *token);
void		make_word_token(t_token *token, char *input);
void		make_quote_token(t_token *token, char *input, char symbol);
void		make_redir_token(t_token *token, char *input);
void		make_pipe_token(t_token *token);
void		make_env_var_token(t_token *token, char *input);
char		*get_env_val(char *input, t_env_var *env_var, int i_start);
int			ft_isspace(char c);

//parser
t_astnode	*parse(t_token *tokens);
t_astnode	*create_astnode(t_token *token);
t_astnode	*parse_command(t_token *tokens, int *current_token);
char		**get_command_args(t_astnode *command_node, t_token *tokens, int *current_token);
t_cmdtype	get_command_type(char *command);
void		del_cmd_quotes(t_token *tokens, int *current_token);
t_astnode	*parse_pipe(t_token *tokens, int *current_token, t_astnode *left_node);
t_astnode	*parse_redirection(t_token *tokens, int *current_token, t_astnode *right_node);
t_redirtype	get_redir_type(char *redir);
void		free_double_pointer(char **str);
//void		free_ast(t_astnode *root);

//signal_handler
void		init_signal_inter(struct sigaction *sa, struct sigaction *old_sa);
void		signal_handler(int signum);
void		restore_signal(struct sigaction *old_sa);
//void		init_signal_exec(void);

//check
void		print_tokens(t_token *tokens);
void		print_ast(t_astnode* ast_node, int level);

#endif