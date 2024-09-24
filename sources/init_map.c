/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:36:40 by alaakson          #+#    #+#             */
/*   Updated: 2024/09/24 11:52:17 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_map_rows(t_game *game, const char *file_path)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Failed to open map file\n");
		exit(EXIT_FAILURE);
	}
	game->map.rows = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->map.rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (game->map.rows == 0)
	{
		ft_printf("Error: Map file is empty\n");
		exit(EXIT_FAILURE);
	}
}

void	allocate_map_memory(t_game *game)
{
	game->map.map = malloc(game->map.rows * sizeof(char *));
	if (!game->map.map)
	{
		ft_printf("Memory allocation failed for map\n");
		exit(EXIT_FAILURE);
	}
}

void	process_map_line(t_game *game, char *line, size_t row)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line_len--;
	if (row == 0)
		game->map.columns = line_len;
	else if (line_len != game->map.columns)
	{
		ft_printf("Error: Map is not rectangular\n");
		free(line);
		exit(EXIT_FAILURE);
	}
	game->map.map[row] = ft_strdup(line);
	if (!game->map.map[row])
	{
		ft_printf("Memory allocation failed for map row\n");
		free(line);
		exit(EXIT_FAILURE);
	}
	free(line);
}

void	read_map(t_game *game, const char *file_path)
{
	int		fd;
	char	*line;
	size_t	row;

	row = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Failed to open map file\n");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_map_line(game, line, row);
		row++;
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		exit(EXIT_FAILURE);
	if (row == 0)
		exit(EXIT_FAILURE);
}

void	load_map(t_game *game, const char *file_path)
{
	count_map_rows(game, file_path);
	allocate_map_memory(game);
	read_map(game, file_path);
}
