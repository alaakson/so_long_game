/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:53:23 by alaakson          #+#    #+#             */
/*   Updated: 2024/10/23 14:35:53 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_hook(t_game *game)
{
	if (!game)
		return (EXIT_SUCCESS);
	ft_printf("You pressed exit.\nQuitting game now!\n");
	game->game_over = 1;
	game->game_finished = 1;
	finish_map(game);
	if (game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void print_map(t_game *game) 
{
    for (size_t row = 0; row < game->map.rows; row++) {
        for (size_t col = 0; col < game->map.columns; col++) {
            printf("%c", game->map.map[row][col]);
        }
        printf("\n");
    }
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	game = malloc(sizeof(t_game));
	if (!game)
	{
		ft_printf("Error allocating game\n");
		return (EXIT_FAILURE);
	}
	build_map(&game->map, argv[1]);
	load_map(game, argv[1]);
	check_tiles(game);
	check_coins(game);
	check_map_errors(game);
	validate_path(game, game->map.map[0], game->posx, game->posy);
	print_map(game);
	init(game);
	handle_map(game);
	map_and_win(game, game->posx, game->posy, game->p_front);
	update_display(game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, exit_hook, game);
	mlx_loop(game->mlx);
	finish_map(game);
	return (EXIT_SUCCESS);
}
