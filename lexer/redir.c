/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by gduranti          #+#    #+#             */
/*   Updated: 2024/05/02 12:49:36 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_bool	check_if_last(char c, char *str, t_data *data)
{
	int		i;

	i = 1;
	if (str[i] && str[i] == c)
		i++;
	if (str[i] && ft_islimiter(str[i]) == TRUE)
		return (lexer_error("minishell: syntax error near unexpected token `",
				data, str[i]));
	while (str[i] && ft_isspace(str[i]) == TRUE)
		i++;
	if (str[i] == '\0')
		return (lexer_error(
				"minishell: syntax error near unexpected token `", data, c));
	else
		return (TRUE);
}

t_bool	redir_check(char *line, t_data *data)
{
	int		i;
	t_quote	quote;

	i = skip_spaces2(line);
	quote = (t_quote){FALSE, 0};
	while (line[i])
	{
		quote_start(&quote.open, line[i], &quote.type);
		if (quote.open == FALSE && ft_isinset(line[i], "<>") > 0)
			if (check_if_last(line[i], &line[i], data) == FALSE)
				return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	open_quote_check(char *line, char *new_quote)

{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		i++;
	}
	if (quote != 0)
	{
		*new_quote = quote;
		return (TRUE);
	}
	return (FALSE);
}
