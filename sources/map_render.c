/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:36:44 by alaakson          #+#    #+#             */
/*   Updated: 2024/09/23 14:45:36 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_sprite_to_window(t_game *game, void *sprite, size_t y, size_t x)
{
	mlx_put_image_to_window(game->mlx, game->win, sprite, x * 32, y * 32);
}

void	sprite_search(t_game *game, size_t y, size_t x)
{
	char	param;

	param = game->map.map[y][x];
	if (param == '1')
		put_sprite_to_window(game, game->wall, y, x);
	else if (param == '0')
		put_sprite_to_window(game, game->floor, y, x);
	else if (param == 'C')
		put_sprite_to_window(game, game->key, y, x);
	else if (param == 'E')
	{
		if (game->collectible == 0)
			put_sprite_to_window(game, game->exit, y, x);
		else
			put_sprite_to_window(game, game->closed_gate, y, x);
	}
	else if (param == 'P')
		put_sprite_to_window(game, game->player, y, x);
	else
		printf("Unknown map character: %c at (%zu, %zu)\n", param, y, x);
}

void	handle_map(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			sprite_search(game, y, x);
			x++;
		}
		y++;
	}
}

void	*load_image(t_game *game, const char *path)
{
	void	*image;

	image = mlx_xpm_file_to_image(game->mlx, (char *)path,
			&game->img_w, &game->img_h);
	if (!image)
	{
		finish_map(game);
		exit(EXIT_FAILURE);
	}
	return (image);
}
