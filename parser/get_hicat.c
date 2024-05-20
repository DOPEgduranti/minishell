/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hicat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by gduranti          #+#    #+#             */
/*   Updated: 2024/05/02 15:53:59 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	get_command(int *off, char *str, t_parser *prs, t_data *data)
{
	int		i;
	t_quote	squote;

	(void)data;
	i = 0;
	squote = (t_quote){FALSE, 0};
	i = skip_spaces2(str);
	if (ft_islimiter(str[i]) == TRUE)
	{
		(*off)++;
		i++;
	}
	while (str[i] && (ft_islimiter(str[i]) == FALSE || squote.open == TRUE))
	{
		quote_start(&squote.open, str[i], &squote.type);
		prs->tmp = join_char(prs->tmp, str[i]);
		i++;
	}
	return (TRUE);
}

t_bool	get_inout(int *off, char *str, t_parser *prs, t_data *data)
{
	int			i;
	t_quote		squote;

	(void)data;
	squote = (t_quote){FALSE, 0};
	i = skip_spaces2(str);
	while (ft_islimiter(str[i]) == TRUE)
		(i)++;
	i += skip_spaces2(str + i);
	while (str[i])
	{
		quote_start(&squote.open, str[i], &squote.type);
		if ((ft_isspace(str[i]) == TRUE || ft_islimiter(str[i]) == TRUE)
			&& squote.open == FALSE)
			break ;
		prs->tmp = join_char(prs->tmp, str[i]);
		i++;
	}
	*off = i;
	*off += skip_spaces2(str + *off);
	if (str[*off] == '\0')
		return (TRUE);
	if (ft_islimiter(str[*off]) == FALSE)
		return (FALSE);
	return (TRUE);
}

char	*ft_reparsing(char *str, int i, t_data *data, t_quote squote)
{
	char		*tmp;
	char		*dst;
	t_curs		c;

	dst = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dst)
		return (free(str), ft_inputclear(&data->input), NULL);
	c.k = i;
	c.j = -1;
	while (c.k > 0 && (ft_islimiter(str[c.k]) == FALSE || squote.open == TRUE))
		quote_start(&squote.open, str[c.k--], &squote.type);
	if (c.k > 0 && ft_islimiter(str[c.k - 1]) == TRUE)
		c.k--;
	while (str[++c.j] && c.j < c.k)
		dst[c.j] = str[c.j];
	tmp = ft_strncpy(str, c.k, i);
	while (str[i] && (ft_islimiter(str[i]) == FALSE || squote.open == TRUE))
	{
		quote_start(&squote.open, str[i], &squote.type);
		dst[c.j++] = str[i++];
	}
	dst = ft_strjoin_2free(ft_input2str(&data->input),
			ft_newstrjoin(ft_strjoin_2free(dst, tmp), &str[i]));
	dst = ft_strtrimfree(dst, " \t\r\n\v\f", &i);
	return (free(str), ft_inputclear(&data->input), dst);
}

void	ft_cmdquote(char **str, int *offset)
{
	t_bool	ciccio;
	t_quote	qt;
	int		i;

	ciccio = TRUE;
	qt = (t_quote){FALSE, 0};
	i = 0;
	while (i < (int)ft_strlen(*str))
	{
		quote_start(&qt.open, (*str)[i], &qt.type);
		if (ft_isspace((*str)[i]) && qt.open == TRUE)
			ciccio = FALSE;
		i++;
	}
	if (ciccio == TRUE)
		*str = remove_quotes(*str, offset);
}
