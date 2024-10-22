/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:05:28 by alaakson          #+#    #+#             */
/*   Updated: 2024/10/22 19:41:16 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_tiles(t_game *game)
{
    int j;
    int i;
    int height;
    int width;

    i = 1;
    height = game->map.rows;
    width = game->map.columns;
    while (i < height - 1)
    {
        j = 1;
        while (j < width - 1)
        {
            char tile;
            tile = game->map.map[i][j];
            if (tile != '0' && tile != '1' && tile != 'E' && tile != 'C'&& tile != 'P')
            {
                ft_printf("Tiles missing (%d, %d) is not '0', found '%c'\n", i , j, tile);
                exit(EXIT_FAILURE);
            }
        j++;
        }
        i++;
    }
    return (1);
}

int is_valid(t_game *game, size_t x, size_t y, char target)
{
    if (x >= game->map.columns || y >= game->map.rows)
        return 0;
    if (game->temp_map[y][x] != target)
        return 0;
    return 1;
}


void    flood_fill(t_game *game, size_t x, size_t y, char target, char replacement)
{
    if (!is_valid(game, x, y, target))
    {
        return ;
    }
    game->map.map[x][y] = replacement;
    if (x > 0)
        flood_fill(game, x + 1, y, target, replacement);
    if (y > 0)
        flood_fill(game, x, y - 1, target, replacement);
    flood_fill(game, x - 1, y, target, replacement);
    flood_fill(game, x, y + 1, target, replacement);
}

void validate_map_paths(t_game *game)
{
    size_t player_x;
    size_t player_y;
    size_t i;
    size_t j;
    
    player_x = game->posx;
    player_y = game->posy;
    allocate_map_memory(game);
    
    i = 0;
    while (i < game->map.rows)
    {
        j = 0;
        while (j < game->map.columns)
        {
            game->temp_map[i][j] = game->map.map[i][j];
            j++;
        }
        i++;
    }
    flood_fill(game, player_y, player_x, FLOOR, 'F');
    printf("Player Position: (%zu, %zu)\n", player_y, player_x);
    printf("Exit Position: (%zu, %zu)\n", game->exity, game->exitx);
    printf("Temp Map at Exit: %c\n", game->temp_map[game->exity][game->exitx]);
    if (game->temp_map[game->exity][game->exitx] != 'F') {
        show_error("No valid path to exit.");
    }
    free_map(game);
}
