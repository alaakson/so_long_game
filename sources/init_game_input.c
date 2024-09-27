/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:36:33 by alaakson          #+#    #+#             */
/*   Updated: 2024/09/27 11:56:52 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_collectibles(t_game *game)
{
	size_t	row;
	size_t	col;

	game->collectible = 0;
	row = 0;
	while (row < game->map.rows)
	{
		col = 0;
		while (col < game->map.columns)
		{
			if (game->map.map[row][col] == 'C')
				game->collectible++;
			col++;
		}
		row++;
	}
	ft_printf("Total collectibles to pick up!: %d\n", game->collectible);
}

void	init(t_game *game)
{
	int	win_width;
	int	win_height;

	win_width = IMG_WIDTH * game->map.columns;
	win_height = IMG_HEIGHT * game->map.rows;
	game->game_finished = 0;
	game->collectible = 0;
	game->collectible_check = 0;
	game->num_exit = 0;
	game->num_player = 0;
	game->exit_reach = 0;
	game->map_validity = 0;
	game->steps = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		show_error("Failed to initialize mlx.\n");
	if (win_width <= 0 || win_height <= 0)
		exit(EXIT_FAILURE);
	game->win = mlx_new_window(game->mlx, win_width, win_height, "So Long");
	if (!game->win)
		show_error("Failed to open window.\n");
	sprite_init(game);
	count_collectibles(game);
	check_map_errors(game);
}

void	sprite_init(t_game *game)
{
	game->p_front = load_image(game, FRONT);
	game->p_left = load_image(game, LEFT);
	game->p_right = load_image(game, RIGHT);
	game->p_back = load_image(game, BACK);
	game->floor = load_image(game, TILE);
	game->wall = load_image(game, VGG);
	game->key = load_image(game, COL);
	game->exit = load_image(game, EXIT);
	game->empty = load_image(game, EMPTY);
	game->closed_gate = load_image(game, C_GATE);
}
