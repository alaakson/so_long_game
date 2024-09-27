/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:36:24 by alaakson          #+#    #+#             */
/*   Updated: 2024/09/27 11:52:25 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_and_win(t_game *game, size_t new_x, size_t new_y, void *new_image)
{
	if (game->map.map[new_y][new_x] == '0'
	|| game->map.map[new_y][new_x] == 'C')
	{
		if (game->map.map[new_y][new_x] == 'C')
		{
			game->collectible--;
			ft_printf("Items remaining: %d\n", game->collectible);
		}
		game->steps++;
		ft_printf("Steps taken: %d\n", game->steps);
		mlx_put_image_to_window(game->mlx, game->win, game->empty,
			game->posx * IMG_WIDTH, game->posy * IMG_HEIGHT);
		game->map.map[game->posy][game->posx] = '0';
		game->posx = new_x;
		game->posy = new_y;
		game->map.map[new_y][new_x] = 'P';
		if (new_image)
		{
			mlx_put_image_to_window(game->mlx, game->win,
				new_image, game->posx * IMG_WIDTH, game->posy * IMG_HEIGHT);
		}
		draw_map(game);
	}
}

void	handle_vertical_movement(t_game *game, int direction)
{
	size_t	new_x;
	size_t	new_y;
	void	*new_image;

	new_x = game->posx;
	new_y = game->posy;
	new_image = NULL;
	if (direction == KEY_UP && new_y > 0)
	{
		new_y--;
		new_image = game->p_back;
	}
	else if (direction == KEY_DOWN && new_y < game->map.rows - 1)
	{
		new_y++;
		new_image = game->p_front;
	}
	else
	{
		return ;
	}
	if (game->map.map[new_y][new_x] == 'E' && game->collectible == 0)
		game_complete(game, new_x, new_y);
	map_and_win(game, new_x, new_y, new_image);
}

void	handle_horizontal_movement(t_game *game, int direction)
{
	size_t	new_x;
	size_t	new_y;
	void	*new_image;

	new_x = game->posx;
	new_y = game->posy;
	new_image = NULL;
	if (direction == KEY_LEFT && new_x > 0)
	{
		new_x--;
		new_image = game->p_left;
	}
	else if (direction == KEY_RIGHT && new_x < game->map.columns -1)
	{
		new_x++;
		new_image = game->p_right;
	}
	else
	{
		return ;
	}
	if (game->map.map[new_y][new_x] == 'E' && game->collectible == 0)
		game_complete(game, new_x, new_y);
	map_and_win(game, new_x, new_y, new_image);
}

int	key_hook(int keycode, t_game *game)
{
	if (game->game_over)
		return (1);
	if (keycode == 65307 || keycode == 113)
	{
		ft_printf("Quitting game!\n");
		game->game_over = 1;
		game->game_finished = 1;
		exit(EXIT_SUCCESS);
	}
	if (keycode == KEY_UP || keycode == KEY_DOWN)
	{
		handle_vertical_movement(game, keycode);
	}
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		handle_horizontal_movement(game, keycode);
	}
	if ((keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT
			|| keycode == KEY_RIGHT) && !game->game_over)
	{
		update_display(game);
	}
	return (1);
}

void	update_display(t_game *game)
{
	char	steps_text[50];

	if (game->game_over)
		return ;
	if (!game->mlx)
	{
		ft_printf("Warning: Mlx library not initialized\n");
		return ;
	}
	if (!game->win)
	{
		ft_printf("Warning: Attempted to update display with no window.\n");
		return ;
	}
	mlx_clear_window(game->mlx, game->win);
	draw_map(game);
	snprintf(steps_text, sizeof(steps_text), "Steps: %d", game->steps);
	mlx_string_put(game->mlx, game->win, 30, 20, 0xFFFFFF, steps_text);
}
