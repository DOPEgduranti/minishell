/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accounting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by gduranti          #+#    #+#             */
/*   Updated: 2024/05/02 12:49:36 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	nbr_cmds(t_data *data)
{
	t_input	*tmp;
	int		i;

	i = 0;
	tmp = data->input;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->type == COMMAND || tmp->type == BUILT_IN)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	nbr_cmds_notb(t_data *data)
{
	t_input	*tmp;
	int		i;

	i = 0;
	tmp = data->input;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->type == COMMAND)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
