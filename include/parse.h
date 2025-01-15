/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:01:34 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/15 17:01:34 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

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

struct s_astnode;

// heredoc_fd is specially for heredoc<<
// heredoc need a tmp fd to hold the content, 
//and then call dup2(heredoc_fd, STDIN_FILENO(0))
typedef struct s_redir
{
	t_redirtype			type;
	int					heredoc_fd;
	char				*left; // the filename
	struct s_astnode	*right;
}						t_redir;

typedef struct s_cmd
{
	t_cmdtype	type;
	int			arg_nb;
	char		**argv;
	char		*path;
	int			*exit_status; //still here???
	char		**env; // or wherever it is
}				t_cmd;

// dont know what we need in this case
typedef struct s_pipe
{
	struct s_astnode	*right;
	struct s_astnode	*left;

}						t_pipe;

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
	int			fd[2];
}				t_astnode;

// parser
t_astnode	*parse(t_token *tokens);
t_astnode	*create_astnode(t_token *token);
t_astnode	*parse_command(t_token *tokens, int *current_token);
char		**get_command_args(t_astnode *command_node, t_token *tokens, int *current_token);
t_cmdtype	get_command_type(char *command);
t_astnode	*parse_pipe(t_token *tokens, int *current_token, t_astnode *left_node);
t_astnode	*parse_redirection(t_token *tokens, int *current_token, t_astnode *right_node);
t_redirtype	get_redir_type(char *redir);
void		free_tokens(t_token *tokens);
void		free_double_pointer(char **str);
void		free_ast(t_astnode *ast_node);

# endif