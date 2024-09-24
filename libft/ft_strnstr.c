/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:43:26 by alaakson          #+#    #+#             */
/*   Updated: 2024/05/08 13:49:54 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;
	size_t	h;

	n = 0;
	h = 0;
	if (needle[0] == 0)
		return ((char *)haystack);
	while (haystack[h] && h < len)
	{
		while (haystack[h + n] == needle[n] && haystack[h + n] && h + n < len)
		{
			n++;
			if (needle[n] == 0)
				return ((char *) haystack + h);
		}
		h++;
		n = 0;
	}
	return (0);
}
