/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:36:49 by alaakson          #+#    #+#             */
/*   Updated: 2024/09/24 12:12:20 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	first_row(t_map *map, int fd)
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
	first_row(map, fd);
	remaining_rows(map, fd);
	close(fd);
	if (map->rows == 0)
	{
		ft_printf("Map file has no rows\n");
		map_error("Map file has no rows\n");
	}
	printf("from build_map: W = %zu, H = %zu\n", map->columns, map->rows);
}

void	*get_image_for_cell(t_game *game, char cell)
{
	static void	*image_lookup[256];

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

void	print_map(t_game *game)
{
	size_t	y;
	size_t	x;

	if (game->map.map == NULL)
	{
		ft_printf("Map data is not available\n");
		return ;
	}
	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.columns)
		{
			ft_printf("%c", game->map.map[y][x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}
