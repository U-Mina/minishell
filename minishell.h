/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:31:58 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/09 12:35:24 by ipuig-pa         ###   ########.fr       */
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

//lexer
t_token		*tokenizer(char *input);
int			count_token_max(char *input);
t_token		create_token(t_tokentype type, char *value);
char		*get_word(char *input);
char		*get_quote(char *input, char symbol);
char		*get_env_var(char *input);
void		free_tokens(t_token **tokens);
int			ft_isspace(char c);
#endif