/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:50:37 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/15 16:50:37 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
	t_tokentype	type;
	char		*value;
}				t_token;

typedef struct s_tokenizer
{
	t_token	*tokens;
	int		capacity;
	int		grow;
	int		count;
}			t_tokenizer;

// Will be disambiguated to Command_builtin, Command_binary,
//argument or filename in the parser
typedef enum e_tokentype
{
	WORD, 
	COMMAND,
	ARGUMENT,
	QUOTE,
	REDIRECTION, // Will be disambiguated to input, output, append or heredoc
	PIPE,
	TOKEN_EOF
}			t_tokentype;

typedef struct s_env_var
{
	char	*val;
	int		start;
	int		end;
	int		name_len;
	int		val_len;
}			t_env_var;

// lexer-tokenizer
t_token		*tokenizer(char *input, int *exit_status);
t_tokenizer	*init_tokenizer(void);
int			grow_tokenizer(t_tokenizer *tokenizer);
void		create_token(t_tokenizer *tokenizer, char *input, int *exit_status);
void		make_eof_token(t_token *token);
void		make_word_token(t_token *token, char *input, int *exit_status);
void		make_quote_token(t_token *token, char *input, char symbol, int *exit_status);
void		make_redir_token(t_token *token, char *input);
void		make_pipe_token(t_token *token);
char		*get_env_val(char *input, t_env_var *env_var, int i_start, int *exit_status);
void		comb_lit_env(char *lit, char *input, t_env_var *env_var);
int			ft_isspace(char c);

#endif