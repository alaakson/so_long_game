/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:19:46 by alaakson          #+#    #+#             */
/*   Updated: 2024/05/08 13:48:29 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	chk;

	str = (unsigned char *) s;
	chk = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == chk)
			return ((void *) &str[i]);
		i++;
	}
	return (0);
}
