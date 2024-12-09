/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:31:24 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/09 13:00:25 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//lexer or tokenizer (lexic analysis). Creates and returns an allocated array of token structures, that store the type of the token (to be further disambiguated according to the token context) and the value itself. 
t_token	*tokenizer(char *input)
{
	int		max_token_num;
	int		current_token;
	t_token	*tokens;

	max_token_num = count_token_max(input);
	tokens = (t_token *)malloc((max_token_num + 1) * sizeof(t_token));
	if (!tokens)
		return (NULL);
	current_token = 0;
	while (*input != '\0')
	{
		while (ft_isspace(*input))
			input++;
		if (*input == '|')
			tokens[current_token] = create_token(PIPE, "|");
		else if (*input == '$')
			tokens[current_token] = create_token(ENV_VAR, get_word(input));//extracts the name of the environmental variable, still pending of extending the value of the env_variable
		else if (*input == '>' || *input == '<')
			tokens[current_token] = create_token(REDIRECTION, get_word(input));
		else if (*input == '\"' || *input == '\'')
			tokens[current_token] = create_token(QUOTE, get_quote(input, *input));
		else	//if (ft_isalpha(*input))
			tokens[current_token] = create_token(WORD, get_word(input));
		//check that really all the cases which are not the previous are words (commands, arguments or textfiles)
		input = input + ft_strlen(tokens[current_token].value);
		current_token++;
	}
	tokens[current_token] = create_token(TOKEN_EOF, NULL);
	return (tokens);
}

//counts an returns the maximum possible number of tokens in the string (the number of space-separated items)
int	count_token_max(char *input)
{
	char	**split;
	int		token_num;

	token_num = 0;
	split = ft_split(input, ' ');
	while (split[token_num] != NULL)
	{
		free(split[token_num]);
		token_num++;
	}
	free(split);
	return (token_num);
}

//creates a token and assigns the type and the value as set by the arguments. Returns the token.
t_token	create_token(t_tokentype type, char *value)
{
	t_token	token;

	token.type = type;
	//handle error when value is NULL(but it is not EOF) -> free previously allocated tokens and t
	// if (!value && type != EOF)
	// {
	// 	handle_error ();
	// 	return ();
	// }
	token.value = value;
	return (token);
}

//extracts a word (delimited by spaces) from the input and returns a pointer to the allocated string
char	*get_word(char *input)
{
	char	*word;
	int		word_len;

	word_len = 0;
	while (!ft_isspace(input[word_len]) && input[word_len] != '\0')
		word_len++; 
	word = malloc((word_len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, input, word_len + 1);
	return (word);
}

//extracts a quote (delimited by quote_symbol (" or ')) from the input and returns a pointer to the allocated string. 
//Possibility to somehow join with get_word, managing with space as the required symbol?? have in mind the handling of unclosed quotes
char	*get_quote(char *input, char symbol)
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
	quote = malloc((quote_len + 1) * sizeof(char));
	if (!quote)
		return (NULL);
	ft_strlcpy(quote, input, quote_len + 1);
	return (quote);
}

//to use after tokens have been used. Frees each allocated value in the token structure array and frees the whole array
void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while ((*tokens)[i].type != TOKEN_EOF)
	{
		if ((*tokens)[i].type != PIPE)
			free((*tokens)[i].value);
		i++;
	}
	free(*tokens);
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
