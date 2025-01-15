/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_make.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:31:24 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/15 16:48:28 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fills the token variables according to a EOF token type
void	make_eof_token(t_token *token)
{
	token->type = TOKEN_EOF;
	token->value = NULL;
	token->i_len = 1;
}

//extracts a word (delimited by spaces) from the input and fills the token variables according to this
void	make_word_token(t_token *token, char *input, int *exit_status)
{
	char		*word;
	int			word_len;
	t_env_var	env_var;

	word_len = 0;
	env_var.val_len = 0;
	token->type = WORD;
	while (!ft_isspace(input[word_len]) && input[word_len] != '\0')
	{
		if (input[word_len] == '$')
			get_env_val(input, &env_var, word_len, exit_status);
			//check error??
		word_len++;
	}
	word = gc_malloc((word_len + env_var.val_len + 1) * sizeof(char));
	// if (!word)
	// 	gc_malloc_error();
	if (env_var.val_len != 0)
		comb_lit_env(word, input, &env_var);
	else
		ft_strlcpy(word, input, quote_len + 1);
	token->value = word;
	token->i_len = word_len;
}

//have in mind the handling of unclosed quotes????
//extracts a quote (delimited by quote_symbol (" or ')) from the input and fills the token variables according to this
void	make_quote_token(t_token *token, char *input, char symbol, int *exit_status)
{
	char		*quote;
	int			quote_len;
	t_env_var	env_var;

	quote_len = 1;
	env_var.val_len = 0;
	token->type = QUOTE;
	while (input[quote_len] != symbol && input[quote_len] != '\0')
	{
		if (symbol == '\"' && input[quote_len] == '$')
			get_env_val(input, &env_var, quote_len, exit_status);
			//check error??
		quote_len++;
	}
	if (input[quote_len] == symbol)
		quote_len++;
	//handle unclosed quotes here, as errors?!?!?
	// if (input[quote_len] != symbol)
	// 	handle_error();
	quote = gc_malloc((quote_len + env_var.val_len + 1) * sizeof(char));
	// if (!quote)
	// 	gc_malloc_error();
	if (env_var.val_len != 0)
		comb_lit_env(quote, input, &env_var);
	else
		ft_strlcpy(quote, input, quote_len + 1);
	token->value = quote;
	token->i_len = quote_len;
}

//extracts a redirection operator from the input and fills the token variables according to this
void	make_redir_token(t_token *token, char *input)
{
	char	*redir;
	int		redir_len;
	char	symbol;

	token->type = REDIRECTION;
	redir_len = 1;
	symbol = *input;
	if (input[redir_len] == symbol)
		redir_len++;
	redir = gc_malloc((redir_len + 1) * sizeof(char));
	// if (!redir)
	// 	gc_malloc_error();
	ft_strlcpy(redir, input, redir_len + 1);
	token->value = redir;
	token->i_len = redir_len;
}

//be aware of input checking. What do we expect / not exect after pipe??
//extracts a pip operator from the input and fills the token variables according to this
void	make_pipe_token(t_token *token)
{
	char	*pipe;

	pipe = gc_malloc(2 * sizeof(char));
	// if (!redir)
	// 	gc_malloc_error();
	ft_strlcpy(pipe, "|", 2);
	token->type = PIPE;
	token->value = pipe;
	token->i_len = 1;
}
