/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:01:32 by alaakson          #+#    #+#             */
/*   Updated: 2024/09/11 11:29:37 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		d;
	int		s;

	s = 0;
	d = 0;
	if (!s1 || !s2)
		return (NULL);
	dest = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1[s])
	{
		dest[d++] = s1[s++];
	}
	s = 0;
	while (s2[s])
	{
		dest[d++] = s2[s++];
	}
	dest[d] = '\0';
	return (dest);
}
