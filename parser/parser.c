/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by gduranti          #+#    #+#             */
/*   Updated: 2024/05/02 15:36:27 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	get_name(char *str, t_parser *prs, t_data *data, int *off)
{
	t_bool		check;

	check = TRUE;
	if (prs->tmp_type == COMMAND || prs->tmp_type == BUILT_IN)
		check = get_command(off, str, prs, data);
	else if (prs->tmp_type == HEREDOC || prs->tmp_type == INPUT
		|| prs->tmp_type == APPEND || prs->tmp_type == TRUNC)
		check = get_inout(off, str, prs, data);
	return (check);
}

char	*get_path(t_parser *prs, t_data *data, int *offset)
{
	char	*tmp_path;
	int		i;

	i = 0;
	if (prs->tmp == NULL)
		return (NULL);
	tmp_path = NULL;
	if (prs->tmp_type == COMMAND)
	{
		while (prs->tmp[i] != 32 && prs->tmp[i] != '\0')
		{
			tmp_path = join_char(tmp_path, prs->tmp[i]);
			i++;
		}
		if (find_first(tmp_path, '/') != -1)
			return (tmp_path);
		else
			return (path_execve(tmp_path, data->envp, data));
	}
	else if (prs->tmp_type != HEREDOC && prs->tmp_type != BUILT_IN)
		return (refactor_path(prs->tmp, data, 0, offset));
	return (ft_strdup(prs->tmp));
}

t_bool	parse_temp_data(t_parser *prs, t_data *data, int *offset)
{
	char	*tmp;

	if (prs->tmp_type == COMMAND)
		ft_cmdquote(&prs->tmp, offset);
	else
	{
		tmp = ft_strdup(prs->tmp);
		free(prs->tmp);
		prs->tmp = ft_strncpy_noquote(tmp,
				0, ft_strlen(tmp), (t_quote){FALSE, 0});
	}
	if (ft_isbuiltin(prs->tmp) == TRUE)
		prs->tmp_type = BUILT_IN;
	if (prs->tmp && prs->tmp[0] == ' ')
		ft_error(prs->tmp, NO_PATH, 127, data);
	prs->tmp_path = get_path(prs, data, offset);
	if (prs->tmp_path == NULL)
		ft_error(prs->tmp, NO_PATH, 127, data);
	ft_inputadd_back(&data->input, ft_inputnew(*prs));
	return (TRUE);
}

t_bool	check_pippe(char **str, t_parser *prs, t_data *data)
{
	if (prs->tmp_type != PIPPE)
		return (FALSE);
	ft_inputadd_back(&data->input, ft_inputnew
		((t_parser){"|", "[pipe]", PIPPE}));
	*str = ft_skipstring(i_skip_pippe(*str, 0), *str);
	return (TRUE);
}

t_bool	parser(char *str, t_data *data, int offset, t_parser prs)
{
	while (str)
	{
		prs.tmp_type = ft_file_type(str, &offset);
		if (check_pippe(&str, &prs, data) == TRUE)
			continue ;
		if (!get_name(str, &prs, data, &offset))
		{
			str = ft_reparsing(str, offset, data, (t_quote){FALSE, 0});
			free_parser(&prs);
			continue ;
		}
		offset += skip_spaces2(str + offset);
		prs.tmp = ft_strtrimfree(prs.tmp, " \t\r\n\v\f", &offset);
		if (!prs.tmp)
		{
			str = ft_skipstring(offset, str);
			continue ;
		}
		str = cut_pars_str(str, prs.tmp);
		if (parse_temp_data(&prs, data, &offset) == FALSE)
			return (free(prs.tmp), free(str), FALSE);
		free_parser(&prs);
	}
	ft_inputadd_back(&data->input, ft_inputnew((t_parser){NULL, NULL, 69}));
	return (free(str), TRUE);
}
