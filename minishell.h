/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:31:58 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/10 16:13:43 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>

//lexer
typedef enum e_tokentype
{
	WORD, //Will be disambiguated to Command_builtin, Command_binary, argument or filename in the parser
	COMMAND_BUILTIN,
	COMMAND_BINARY,
	ARGUMENT,
	REDIRECTION,
	PIPE,
	ENV_VAR,
	QUOTE,
	FILENAME,
	TOKEN_EOF
}	t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*value;
}	t_token;

//parser: AST building
//create a union to have different types of data depending on the type of node when including redirections and pipes
typedef struct s_astnode
{
	t_token				*token;
	struct s_astnode	*right;
	struct s_astnode	*left;
	struct s_astnode	*next_arg;
}	t_astnode;

//comprovations
void	print_tokens(t_token *tokens);
void	print_ast(t_astnode* ast_node, int level);

//lexer
t_token		*tokenizer(char *input);
int			count_token_max(char *input);
t_token		create_token(t_tokentype type, char *value);
char		*get_word(char *input);
char		*get_quote(char *input, char symbol);
void		free_tokens(t_token **tokens);
int			ft_isspace(char c);

//parser
t_astnode	*parse(t_token *tokens);
t_astnode	*parse_command(t_token *tokens, char **builtins, int *current_token);
void		add_arg_node(t_astnode *command_node, t_astnode *arg_node);
t_astnode	*parse_redirection(t_token *tokens, t_astnode *command_node, int *current_token);
t_astnode	*parse_pipe(t_token *tokens, char **builtins, int *current_token, t_astnode *left_node);
t_astnode	*create_astnode(t_token *token);
t_tokentype	get_command_type(char *command, char **builtins);
char		**check_builtins(void);
void		free_double_pointer(char **str);
//void		free_ast(t_astnode *root);

#endif