/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:23:28 by ewu               #+#    #+#             */
/*   Updated: 2025/01/11 15:28:26 by ipuig-pa         ###   ########.fr       */
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
	FILENAME,
	HEREDOC,
	DELIMITER,
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
}						t_token;

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
	int			*exit_status;
	char		**env; //or wherever it is
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

//gc_list
typedef struct s_gc_list
{
	void				*allocated;
	struct s_gc_list	*next;
}	t_gc_list;


//gc
void		*gc_malloc(size_t size);
t_gc_list	**get_gc_list(void);
void		gc_malloc_error(void);
void		add_gc_list(void *new_alloc);
void		gc_free(void *free_ptr);
void		gc_clean(void);

//lexer
t_token		*tokenizer(char *input);
int			count_token_max(char *input);
t_token		create_token(t_tokentype type, char *value);
char		*get_word(char *input);
char		*get_quote(char *input, char symbol);
void		free_tokens(t_token *tokens);
int			ft_isspace(char c);

//parser
t_astnode	*parse(t_token *tokens);
t_astnode	*create_astnode(t_token *token);
t_astnode	*parse_command(t_token *tokens, int *current_token);
char		**get_command_args(t_astnode *command_node, t_token *tokens, int *current_token);
t_cmdtype	get_command_type(char *command);
t_astnode	*parse_pipe(t_token *tokens, int *current_token, t_astnode *left_node);
t_astnode	*parse_redirection(t_token *tokens, int *current_token, t_astnode *right_node);
t_redirtype	get_redir_type(char *redir);
void		free_double_pointer(char **str);
//void		free_ast(t_astnode *root);

//check
void		print_tokens(t_token *tokens);
void		print_ast(t_astnode* ast_node, int level);

#endif