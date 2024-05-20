/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by gduranti          #+#    #+#             */
/*   Updated: 2024/05/02 12:49:36 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_strdup(char *str, char **freestr)
{
	char	*tmp;

	tmp = ft_strdup(str);
	free(*freestr);
	return (tmp);
}

char	*ft_skipstring(int offset, char *str)
{
	char	*dst;

	dst = ft_strdup(str + offset);
	return (free(str), dst);
}
