/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:53:39 by alaakson          #+#    #+#             */
/*   Updated: 2024/09/27 11:58:40 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_map_errors(t_game *game, int error_flag)
{
	if (error_flag)
	{
		ft_printf("Too many exits or player positions!\n");
		finish_map(game);
		exit(EXIT_FAILURE);
	}
}

void	find_player_start(t_game *game, int *error_flag)
{
	size_t	row;
	size_t	col;
	int		player_count;

	row = 0;
	player_count = 0;
	while (row < game->map.rows)
	{
		col = 0;
		while (col < game->map.columns)
		{
			if (game->map.map[row][col] == 'P')
			{
				player_count++;
				if (player_count > 1)
					*error_flag = 1;
				game->posx = col;
				game->posy = row;
			}
			col++;
		}
		row++;
	}
}

void	find_exit(t_game *game, int *error_flag)
{
	size_t	row;
	size_t	col;
	int		exit_count;

	row = 0;
	exit_count = 0;
	while (row < game->map.rows)
	{
		col = 0;
		while (col < game->map.columns)
		{
			if (game->map.map[row][col] == 'E')
			{
				exit_count++;
				if (exit_count > 1)
					*error_flag = 1;
				game->exitx = col;
				game->exity = row;
			}
			col++;
		}
		row++;
	}
}

void	check_map_errors(t_game *game)
{
	int	error_flag;

	error_flag = 0;
	find_player_start(game, &error_flag);
	find_exit(game, &error_flag);
	handle_map_errors(game, error_flag);
}
