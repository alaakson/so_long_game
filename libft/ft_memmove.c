/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:13:39 by alaakson          #+#    #+#             */
/*   Updated: 2024/05/08 13:48:43 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*t_dst;
	char	*t_src;
	size_t	i;

	i = 0;
	t_src = (char *) src;
	t_dst = (char *) dst;
	if (!dst && !src)
		return (NULL);
	if (t_dst > t_src)
	{
		while (len-- > 0)
			t_dst[len] = t_src[len];
	}
	else
	{
		while (i < len)
		{
			t_dst[i] = t_src[i];
			i++;
		}
	}
	return (dst);
}
