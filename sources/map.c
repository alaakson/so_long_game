/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:36:49 by alaakson          #+#    #+#             */
/*   Updated: 2024/10/23 14:51:40 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*void	first_row(t_map *map, int fd)
{
	char	*line;
	char	*trimmed_line;

	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		map_error("Empty map file\n");
	}
	trimmed_line = ft_strtrim(line, "\n");
	map->columns = ft_strlen(trimmed_line);
	if (map->columns == 0)
	{
		free(trimmed_line);
		free(line);
		close(fd);
		map_error("Map has an empty row\n");
	}
	free(trimmed_line);
	free(line);
	map->rows = 1;
}

void	remaining_rows(t_map *map, int fd)
{
	char	*line;
	char	*trimmed_line;
	size_t	line_length;

	line = get_next_line(fd);
	while (line != NULL)
	{
		trimmed_line = ft_strtrim(line, "\n");
		line_length = ft_strlen(trimmed_line);
		if (line_length != map->columns)
		{
			free(trimmed_line);
			free(line);
			close(fd);
			map_error("Map row in consistent\n");
		}
		map->rows++;
		free(trimmed_line);
		free(line);
		line = get_next_line(fd);
	}
}*/

void first_row(t_map *map, int fd)
{
    char *line;
    char *trimmed_line;

    line = get_next_line(fd);
    if (!line)
    {
        close(fd);
        map_error("Empty map file\n");
    }

    // Allocate space for the first row
    trimmed_line = ft_strtrim(line, "\n");
    map->columns = ft_strlen(trimmed_line);
    if (map->columns == 0)
    {
        free(trimmed_line);
        free(line);
        close(fd);
        map_error("Map has an empty row\n");
    }

    // Allocate memory for the map
    map->map = (char **)malloc(sizeof(char *) * (map->rows + 1));
    if (!map->map)
    {
        free(trimmed_line);
        free(line);
        close(fd);
        map_error("Failed to allocate memory for map\n");
    }

    // Save the first row
    map->map[0] = ft_strdup(trimmed_line);  // Duplicate the first row into map->map[0]
    if (!map->map[0])
    {
        free(trimmed_line);
        free(line);
        close(fd);
        map_error("Failed to copy first row to map\n");
    }

    free(trimmed_line);
    free(line);
    map->rows = 1;
}

void remaining_rows(t_map *map, int fd)
{
    char *line;
    char *trimmed_line;
    size_t line_length;

    line = get_next_line(fd);
    while (line != NULL)
    {
        trimmed_line = ft_strtrim(line, "\n");
        line_length = ft_strlen(trimmed_line);
        if (line_length != map->columns)
        {
            free(trimmed_line);
            free(line);
            close(fd);
            map_error("Map row inconsistent\n");
        }

        // Reallocate memory for the new row
        map->map = realloc(map->map, sizeof(char *) * (map->rows + 1));
        if (!map->map)
        {
            free(trimmed_line);
            free(line);
            close(fd);
            map_error("Failed to allocate memory for map\n");
        }

        // Save the row into map->map
        map->map[map->rows] = ft_strdup(trimmed_line);
        if (!map->map[map->rows])
        {
            free(trimmed_line);
            free(line);
            close(fd);
            map_error("Failed to copy row to map\n");
        }

        map->rows++;
        free(trimmed_line);
        free(line);
        line = get_next_line(fd);
    }
}

void	build_map(t_map *map, const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Map not found\n");
		map_error("Map not found\n");
	}
	map->rows = 0;
	first_row(map, fd);    // Reads the first row of the map
	remaining_rows(map, fd);  // Reads the remaining rows
	close(fd);

	if (map->rows == 0)
	{
		ft_printf("Map file has no rows\n");
		map_error("Map file has no rows\n");
	}

	// Debugging print statement after loading the map
	ft_printf("Map loaded:\n");
	for (size_t i = 0; i < map->rows; i++) {  // Access map->map to print
		ft_printf("%s\n", map->map[i]);  // Print each row of the map
	}
	printf("from build_map: W = %zu, H = %zu\n", map->columns, map->rows);
}

void	*get_image_for_cell(t_game *game, char cell)
{
	static void	*image_lookup[255];

	image_lookup[256] = 0;
	if (image_lookup['1'] == NULL)
	{
		image_lookup['1'] = game->wall;
		image_lookup['0'] = game->floor;
		image_lookup['P'] = game->p_back;
		image_lookup['C'] = game->key;
		image_lookup['E'] = game->exit;
		image_lookup['\0'] = game->empty;
	}
	return (image_lookup[(unsigned char)cell]);
}

void	draw_map(t_game *game)
{
	size_t	y;
	size_t	x;
	void	*image;
	char	cell;

	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.columns)
		{
			cell = game->map.map[y][x];
			image = get_image_for_cell(game, cell);
			if (image)
				mlx_put_image_to_window(game->mlx, game->win, image,
					x * IMG_WIDTH, y * IMG_HEIGHT);
			x++;
		}
		y++;
	}
}
