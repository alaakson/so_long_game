/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:53:23 by alaakson          #+#    #+#             */
/*   Updated: 2024/09/27 10:44:32 by alaakson         ###   ########.fr       */
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
		ft_printf("Failed to allocate memory for game\n");
		return (EXIT_FAILURE);
	}
	build_map(&game->map, argv[1]);
	load_map(game, argv[1]);
	checkwalls(game);
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
