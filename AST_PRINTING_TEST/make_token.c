/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:31:24 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/14 15:25:35 by ipuig-pa         ###   ########.fr       */
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
void	make_word_token(t_token *token, char *input)
{
	char	*word;
	int		word_len;

	token->type = WORD;
	word_len = 0;
	while (!ft_isspace(input[word_len]) && input[word_len] != '\0')
		word_len++;
	word = gc_malloc((word_len + 1) * sizeof(char));
	// if (!word)
	// 	gc_malloc_error();
	ft_strlcpy(word, input, word_len + 1);
	token->value = word;
	token->i_len = word_len;
}

//have in mind the handling of unclosed quotes????
//extracts a quote (delimited by quote_symbol (" or ')) from the input and fills the token variables according to this
void	make_quote_token(t_token *token, char *input, char symbol)
{
	char		*quote;
	int			quote_len;
	t_env_var	env_var;
	char		*env_var_val;

	quote_len = 0;
	quote_len++;
	env_var.val_len = 0;
	token->type = QUOTE;
	while (input[quote_len] != symbol && input[quote_len] != '\0')
	{
		if (symbol == '\"' && input[quote_len] == '$')
			env_var_val = get_env_val(input, &env_var, quote_len);
			// if (!env_var_val)
			// 	gc_malloc_error();
			// check if it was $?
		quote_len++;
	}
	quote_len++;
	//handle unclosed quotes here, as errors?!?!?
	// if (input[quote_len] != symbol)
	// 	handle_error();
	quote = gc_malloc((quote_len + env_var.val_len + 1) * sizeof(char));
	// if (!quote)
	// 	gc_malloc_error();
	if (env_var.val_len != 0)
	{
		ft_strlcpy(quote, input, env_var.start + 1);
		ft_strlcpy(quote + env_var.start, env_var_val, env_var.val_len + 1);
		ft_strlcpy(quote + env_var.start + env_var.val_len, input + env_var.end, quote_len - env_var.end + 1);
		gc_free(env_var_val);
	}
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

//include this function in libft??
//check if the passed character is an space
int	ft_isspace(char c)
{
	unsigned char	u_c;

	u_c = (unsigned char)c;
	if (u_c != c)
		return (0);
	if ((u_c >= 9 && u_c <= 13) || u_c == 32)
		return (1);
	return (0);
}
