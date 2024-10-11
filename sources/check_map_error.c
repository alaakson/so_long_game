#include "so_long.h"

int check_tiles(t_game *game)
{
    int j;
    int i;
    int height;
    int width;

    i = 1;
    width = game->map.rows;
    height = game->map.columns;
    while (i < width - 1)
    {
        j = 1;
        while (j < height - 1)
        {
            char    tile;
            tile = game->map.map[i][j];
            if (tile != '0' && tile != 'P' && tile != 'E' && tile != 'C' 
                && tile != '1')
            {
                ft_printf("Tiles missing here (%d, %d), found '%c'\n", i, j, tile);
                exit(EXIT_FAILURE);
            }
                j++;
        }
        i++;
    }
    return (1);
}

int check_coins(t_game *game)
{
    int j;
    int i;
    int height;
    int width;
    int coin_count = 0;

    i = 0;
    width = game->map.rows;
    height = game->map.columns;
    while (i < width)
    {
        j = 0;
        while (j < height)
        {
            char    tile;
            tile = game->map.map[i][j];
            if (tile == 'C')
                coin_count++;
            j++;
        }
        i++;
    } 
    if (coin_count == 0)
    {
        ft_printf("\nERROR!\nNo coins found on the map\n");
        exit(EXIT_FAILURE);
    }
    return (1);
}
