/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_finisher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:48:47 by alaakson          #+#    #+#             */
/*   Updated: 2024/09/24 11:00:32 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_game_on_enter(int keycode, t_game *game)
{
	if (keycode == 65293 || keycode == 113 || keycode == 65307)
	{
		ft_printf("Closing the game now...\n");
		mlx_loop_end(game->mlx);
	}
	return (0);
}

void	game_complete(t_game *game, size_t new_x, size_t new_y)
{
	ft_printf("Congratulations! You've collected all items!\n");
	ft_printf("Game completed in %d steps!\n", game->steps);
	ft_printf("Press Enter, Q or ESC keys to close the game...\n");
	mlx_put_image_to_window(game->mlx, game->win, game->empty,
		game->posx * IMG_WIDTH, game->posy * IMG_HEIGHT);
	game->map.map[game->posy][game->posx] = '0';
	game->posx = new_x;
	game->posy = new_y;
	game->map.map[new_y][new_x] = 'P';
	draw_map(game);
	mlx_key_hook(game->win, close_game_on_enter, game);
}

void	map_error(char *s)
{
	ft_printf("Error\n");
	ft_printf("%s\n", s);
	exit (1);
}
