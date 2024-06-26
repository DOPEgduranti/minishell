/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by gduranti          #+#    #+#             */
/*   Updated: 2024/05/02 12:49:36 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s2;
	unsigned char	*s1;

	s1 = (unsigned char *)src;
	s2 = (unsigned char *)dest;
	if (!src && !dest)
		return (0);
	if (dest > src)
		while (n--)
			s2[n] = s1[n];
	else
		while (n--)
			*(s2++) = *(s1++);
	return (dest);
}
