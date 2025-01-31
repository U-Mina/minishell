/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_make.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:31:24 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/31 17:27:04 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fills the token variables according to a EOF token type
int	make_eof_token(t_token *token)
{
	token->type = TOKEN_EOF;
	token->value = NULL;
	token->quote = false;
	return (1);
}

//extracts a word (delimited by spaces or separator characters) from the input
//and fills the token variable value according to this
int	make_word_token(t_token *token, char *input)
{
	char		*word;
	int			word_len;

	word_len = 0;
	token->type = WORD;
	while (!ft_isspace(input[word_len]) && !ft_issep(input[word_len]) && \
													input[word_len] != '\0')
	{
		if (input[word_len] == '\"' || input[word_len] == '\'')
		{
			if (quote_len(input, word_len) > 1)
				word_len = word_len + quote_len(input, word_len);
		}
		word_len++;
	}
	word = gc_malloc((word_len + 1) * sizeof(char));
	if (!word)
		return (0);
	ft_strlcpy(word, input, word_len + 1);
	token->value = word;
	token->quote = false;
	return (1);
}

//extracts a redirection operator from the input and 
//fills the token variable value according to this
int	make_redir_token(t_token *token, char *input)
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
	if (!redir)
		return (0);
	ft_strlcpy(redir, input, redir_len + 1);
	token->value = redir;
	token->quote = false;
	return (1);
}

//extracts a pipe operator from the input and
//fills the token variable value according to this
int	make_pipe_token(t_token *token)
{
	char	*pipe;

	pipe = gc_malloc(2 * sizeof(char));
	if (!pipe)
		return (0);
	ft_strlcpy(pipe, "|", 2);
	token->type = PIPE;
	token->value = pipe;
	token->quote = false;
	return (1);
}
