/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:31:58 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/31 11:21:54 by ipuig-pa         ###   ########.fr       */
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

//gc_list
typedef struct s_gc_list
{
	void				*allocated;
	struct s_gc_list	*next;
}	t_gc_list;

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
void		print_tokens(t_token *tokens);
void		print_ast(t_astnode* ast_node, int level);

//handle error
void		handle_error(t_gc_list *gc_list);

//garbage collector
t_gc_list	*gc_list_init(t_gc_list *gc_list);
void		*gc_malloc(size_t size, t_gc_list *gc_list);
void		*add_gc_list(void *new_alloc, t_gc_list *gc_list);
void		gc_free(void *free_ptr, t_gc_list *gc_list);
void		gc_clean(t_gc_list *gc_list);

//lexer
t_token		*tokenizer(char *input, t_gc_list *gc_list);
int			count_token_max(char *input);
t_token		create_token(t_tokentype type, char *value, t_gc_list *gc_list);
char		*get_word(char *input, t_gc_list *gc_list);
char		*get_quote(char *input, char symbol, t_gc_list *gc_list);
void		free_tokens(t_token *tokens, t_gc_list *gc_list); //think if it can be done just with gc_clean
int			ft_isspace(char c);

//parser
t_astnode	*parse(t_token *tokens, t_gc_list *gc_list);
t_astnode	*parse_command(t_token *tokens, char **builtins, int *current_token, t_gc_list *gc_list);
void		add_arg_node(t_astnode *command_node, t_astnode *arg_node);
t_astnode	*parse_redirection(t_token *tokens, t_astnode *command_node, int *current_token,  t_gc_list *gc_list);
t_astnode	*parse_pipe(t_token *tokens, char **builtins, int *current_token, t_astnode *left_node, t_gc_list *gc_list);
t_astnode	*create_astnode(t_token *token, t_gc_list *gc_list);
t_tokentype	get_command_type(char *command, char **builtins);
char		**check_builtins(t_gc_list *gc_list);
void		free_double_pointer(char **str);
//void		free_ast(t_astnode *root);

#endif