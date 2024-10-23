/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:05:28 by alaakson          #+#    #+#             */
/*   Updated: 2024/10/23 14:55:29 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void check_tiles(t_game *game) 
{
    int height = game->map.rows;
    int width = game->map.columns;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char tile = game->map.map[i][j];
            if (tile != '0' && tile != '1' && tile != 'C' && tile != 'E' && tile != 'P') {
                printf("Invalid tile found at (%d, %d): '%c'. Expected '0', '1', 'C', 'E', or 'P'.\n", i, j, tile);
                map_error("Invalid tile found\n");
            }
        }
    }
}

int check_coins(t_game *game)
{
    int j;
    int i;
    int height;
    int width;
    int coin_found = 0;

    i = 1;
    height = game->map.rows;
    width = game->map.columns;
    while (i < height - 1)
    {
        j = 1;
        while (j < width - 1)
        {
            char tile = game->map.map[i][j];
            if (tile == 'C')
            {
                coin_found = 1;
            }
            j++;
        }
        i++;
    }
    if (!coin_found)
    {
        ft_printf("Error: No coins ('C') found on the map.\n");
        exit(EXIT_FAILURE);
    }
    return (1);
}

static char **create_temp_map(t_game *game)
{
    size_t i;
    char **temp_map;

    temp_map = (char **)malloc(sizeof(char *) * (game->win_height + 1));
    if (!temp_map)
        return (NULL);
    for (i = 0; i < game->win_height; i++)
    {
        temp_map[i] = ft_strdup(game->map.map[i]);
        if (!temp_map[i])
        {
            while (i > 0)
            {
                free(temp_map[--i]);
            }
            free(temp_map);
            return (NULL);
        }
    }
    temp_map[game->win_height] = NULL;
    return (temp_map);
}

int flood_fill(char **temp_map, size_t width, size_t height, size_t x, size_t y, int *exit_found, int *collectibles_remaining)
{
    // Out of bounds check
    if (x >= width || y >= height)
        return (0);

    // Check for walls or visited cells
    if (temp_map[y][x] == '1' || temp_map[y][x] == 'V')
        return (0);

    // Mark this cell as visited
    temp_map[y][x] = 'V';

    // If we find an exit
    if (temp_map[y][x] == 'E')
        *exit_found = 1;

    // If we find a collectible
    if (temp_map[y][x] == 'C')
        (*collectibles_remaining)--;

    // Recursively fill in all directions
    flood_fill(temp_map, width, height, x + 1, y, exit_found, collectibles_remaining); // Right
    flood_fill(temp_map, width, height, x - 1, y, exit_found, collectibles_remaining); // Left
    flood_fill(temp_map, width, height, x, y + 1, exit_found, collectibles_remaining); // Down
    flood_fill(temp_map, width, height, x, y - 1, exit_found, collectibles_remaining); // Up

    return (1);
}

int validate_path(t_game *game, char *map, size_t start_x, size_t start_y) 
{
    int collectables = 0;
    int exit_found = 0;
    char **temp = create_temp_map(game);

    if (!temp) 
    {
        ft_printf("Memory allocation failed\n");
        return (0);
    }
    if (!flood_fill(temp, game->win_width, game->win_height, start_x, start_y, &exit_found, &collectables))
    {
        ft_printf("No valid path available\n");
        free(map);
        //exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < game->win_height; i++) {
        free(temp[i]);
    }
    free(temp);

    return (collectables == game->collectible && exit_found);
}
