/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:31:24 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/11 13:48:57 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//lexer or tokenizer (lexic analysis). Creates and returns an allocated array of token structures, that store the type of the token (to be further disambiguated according to the token context) and the value itself. 
t_token	*tokenizer(char *input, t_gc_list *gc_list)
{
	int		max_token_num;
	int		current_token;
	t_token	*tokens;

	max_token_num = count_token_max(input);
	tokens = (t_token *)gc_malloc((max_token_num + 1) * sizeof(t_token), gc_list);
	if (!tokens)
		handle_error(gc_list);
	current_token = 0;
	while (*input != '\0')
	{
		while (ft_isspace(*input))
			input++;
		if (*input == '|')
			tokens[current_token] = create_token(PIPE, "|", gc_list);
		else if (*input == '$') // Pending of somehow handling $?
			tokens[current_token] = create_token(ENV_VAR, get_word(input, gc_list), gc_list);//extracts the name of the environmental variable, still pending of extending the value of the env_variable
		else if (*input == '>' || *input == '<')
			tokens[current_token] = create_token(REDIRECTION, get_redir(input, gc_list), gc_list);
		else if (*input == '\"' || *input == '\'')
			tokens[current_token] = create_token(QUOTE, get_quote(input, *input, gc_list), gc_list);
		else if (*input == '\0')
			break ;
		else//if (ft_isalpha(*input))
			tokens[current_token] = create_token(WORD, get_word(input, gc_list), gc_list);
		//check that really all the cases which are not the previous are words (commands, arguments or textfiles)
		input = input + ft_strlen(tokens[current_token].value);
		current_token++;
	}
	tokens[current_token] = create_token(TOKEN_EOF, NULL, gc_list);
	return (tokens);
}

//creates a token and assigns the type and the value as set by the arguments. Returns the token.
t_token	create_token(t_tokentype type, char *value, t_gc_list *gc_list)
{
	t_token	token;

	token.type = type;
	//handle error when value is NULL(but it is not EOF) -> free previously allocated tokens and t
	if (!value && type != TOKEN_EOF)
		handle_error(gc_list);
	token.value = value;
	return (token);
}

//extracts a word (delimited by spaces) from the input and returns a pointer to the allocated string
char	*get_word(char *input, t_gc_list *gc_list)
{
	char	*word;
	int		word_len;

	word_len = 0;
	while (!ft_isspace(input[word_len]) && input[word_len] != '\0')
		word_len++;
	word = gc_malloc((word_len + 1) * sizeof(char), gc_list);
	if (!word)
		return (NULL);
	ft_strlcpy(word, input, word_len + 1);
	return (word);
}

//extracts a quote (delimited by quote_symbol (" or ')) from the input and returns a pointer to the allocated string. 
//Possibility to somehow join with get_word, managing with space as the required symbol?? have in mind the handling of unclosed quotes
char	*get_quote(char *input, char symbol, t_gc_list *gc_list)
{
	char	*quote;
	int		quote_len;

	quote_len = 0;
	quote_len++;
	while (input[quote_len] != symbol && input[quote_len] != '\0')
		quote_len++;
	quote_len++;
	//handle unclosed quotes here, as errors?!?!?
	// if (input[quote_len] != symbol)
	// 	handle_error();
	quote = gc_malloc((quote_len + 1) * sizeof(char), gc_list);
	if (!quote)
		return (NULL);
	ft_strlcpy(quote, input, quote_len + 1);
	return (quote);
}

//extracts a redirection operator from the input and returns a pointer to the allocated string
char	*get_redir(char *input, t_gc_list *gc_list)
{
	char	*redir;
	int		redir_len;
	char	symbol;

	redir_len = 1;
	if (input[redir_len] == symbol)
		redir_len++;
	redir = gc_malloc((redir_len + 1) * sizeof(char), gc_list);
	//handle gc_malloc fail
	if (!redir)
		return (NULL);
	ft_strlcpy(redir, input, redir_len + 1);
	return (redir);
}

//to use after tokens have been used. Frees each allocated value in the token structure array and frees the whole array
void	free_tokens(t_token *tokens, t_gc_list *gc_list)
{
	int	i;

	i = 0;
	while (tokens[i].type != TOKEN_EOF)
	{
		if (tokens[i].type != PIPE)
			gc_free(tokens[i].value, gc_list);
		i++;
	}
	gc_free(tokens, gc_list);
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
