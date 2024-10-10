/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:32:22 by alaakson          #+#    #+#             */
/*   Updated: 2024/10/10 15:02:13 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_game *game)
{
	size_t	x;

	if (game->map.map)
	{
		x = 0;
		while (x < game->map.rows)
		{
			if (game->map.map[x])
			{
				free(game->map.map[x]);
				game->map.map[x] = NULL;
			}
			x++;
		}
		free(game->map.map);
		game->map.map = NULL;
	}
}

void	show_error(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

int	horizontalwall(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->map.columns)
	{
		if (game->map.map[0][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < game->map.columns)
	{
		if (game->map.map[game->map.rows - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	verticalwall(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->map.rows)
	{
		if (game->map.map[i][0] != '1' ||
			game->map.map[i][game->map.columns - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_walls(t_game *game)
{
	if (!verticalwall(game))
	{
		ft_printf("Error: Left or Right boundary wall missing\n");
		exit(EXIT_FAILURE);
	}
	if (!horizontalwall(game))
	{
		ft_printf("Error: Top or Bottom boundary wall missing\n");
		exit(EXIT_FAILURE);
	}
	return (1);
}
