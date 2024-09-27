/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:46:59 by alaakson          #+#    #+#             */
/*   Updated: 2024/09/26 11:43:43 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_images(t_game *game)
{
	if (game->p_back)
		mlx_destroy_image(game->mlx, game->p_back);
	if (game->p_front)
		mlx_destroy_image(game->mlx, game->p_front);
	if (game->p_left)
		mlx_destroy_image(game->mlx, game->p_left);
	if (game->p_right)
		mlx_destroy_image(game->mlx, game->p_right);
	if (game->empty)
		mlx_destroy_image(game->mlx, game->empty);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->key)
		mlx_destroy_image(game->mlx, game->key);
}

void	destroy_window(t_game *game)
{
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
}

void	destroy_mlx(t_game *game)
{
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	finish_map(t_game *game)
{
	if (!game)
		return ;
	if (game->game_finished)
		return ;
	game->game_finished = 1;
	destroy_images(game);
	destroy_window(game);
	destroy_mlx(game);
	free_map(game);
	free(game);
}
