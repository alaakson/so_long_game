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
