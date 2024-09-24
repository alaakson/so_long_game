/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:33:52 by alaakson          #+#    #+#             */
/*   Updated: 2024/05/08 13:49:13 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_strs(char const *s, char c);
static void			ft_next_str(char **next, unsigned int *len_str, char c);
static char			**ft_free(char **strs);

char	**ft_split(const char *s, char c)
{
	unsigned int	nb_strs;
	unsigned int	i;
	unsigned int	next_str_len;
	char			*next_str;
	char			**tab;

	nb_strs = ft_strs(s, c);
	i = 0;
	tab = (char **)malloc(sizeof(char *) *(nb_strs + 1));
	if (!tab || !s)
		return (NULL);
	next_str = (char *)s;
	next_str_len = 0;
	while (i < nb_strs)
	{
		ft_next_str(&next_str, &next_str_len, c);
		tab[i] = (char *)malloc(sizeof(char) * (next_str_len + 1));
		if (!tab[i])
			return (ft_free(tab));
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

static unsigned int	ft_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	n_str;
	int				substring;

	i = 0;
	n_str = 0;
	substring = 0;
	while (s[i])
	{
		if (s[i] != c && substring == 0)
		{
			substring = 1;
			n_str++;
		}
		else if (s[i] == c)
		{
			substring = 0;
		}
		i++;
	}
	return (n_str);
}

static void	ft_next_str(char **next, unsigned int *len_str, char c)
{
	unsigned int	i;

	*next += *len_str;
	*len_str = 0;
	i = 0;
	while (**next && **next == c)
		(*next)++;
	while ((*next)[i])
	{
		if ((*next)[i] == c)
			return ;
		(*len_str)++;
		i++;
	}
}

static char	**ft_free(char **strs)
{
	unsigned int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}
