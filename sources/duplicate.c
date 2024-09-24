/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:06:55 by alaakson          #+#    #+#             */
/*   Updated: 2024/09/24 11:31:15 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    duplicate_checker(t_game *game)
{
    size_t  i;
    size_t  j;
    game->start = 0;
    game->end = 0;
    
    if (!game->map.map || game->map.height == 0 || game->map.width == 0)
    {
        ft_printf("Error: Map data is missing or has invalid dimensions.\n");
        finish_map(game);
        exit(EXIT_FAILURE);
    }
    i = 0;
    while(i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            printf("Character at [%zu][%zu]: %c\n", i, j, game->map.map[i][j]);
            if (game->map.map[i][j] == PLAYER)
                    game->start++;
            else if (game->map.map[i][j] == MAP_EXIT)
                game->end++;
            j++;
        }
        i++;
    }
    ft_printf("Start count: %d\n", game->start);
    ft_printf("End count: %d\n", game->end);
    
    if (game->start != 1 || game->end != 1)
    {
        ft_printf("Error: Map must have one start and one end!\n");
        finish_map(game);
        exit(EXIT_FAILURE);
    }
}
