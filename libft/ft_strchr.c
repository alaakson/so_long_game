/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:55:44 by alaakson          #+#    #+#             */
/*   Updated: 2024/05/08 13:49:16 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			alpha;

	alpha = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == alpha)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == alpha)
		return ((char *) & s[i]);
	return (NULL);
}
