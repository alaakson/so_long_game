/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:54:29 by alaakson          #+#    #+#             */
/*   Updated: 2024/05/08 13:49:34 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = 0;
	if (dstsize != 0)
	{
		while (src[src_len] != '\0' && src_len < (dstsize -1))
		{
			dst[src_len] = src[src_len];
			src_len++;
		}
		dst[src_len] = '\0';
	}
	return (ft_strlen(src));
}
