/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:36:40 by alaakson          #+#    #+#             */
/*   Updated: 2024/10/22 19:44:51 by alaakson         ###   ########.fr       */
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

void allocate_main_map_memory(t_game *game)
{
    size_t i;

    game->map.map = malloc(game->map.rows * sizeof(char *));
    if (!game->map.map)
        show_error("Memory allocation failed for map.");

    i = 0;
    while (i < game->map.rows)
    {
        game->map.map[i] = malloc(game->map.columns * sizeof(char));
        if (!game->map.map[i])
            show_error("Memory allocation failed for map row.");
        i++;
    }
}

void allocate_temp_map_memory(t_game *game)
{
    size_t i;

    game->temp_map = malloc(game->map.rows * sizeof(char *));
    if (!game->temp_map)
        show_error("Memory allocation failed for temp_map.");

    i = 0;
    while (i < game->map.rows)
    {
        game->temp_map[i] = malloc(game->map.columns * sizeof(char));
        if (!game->temp_map[i])
        {
            while (i > 0)
            {
                free(game->temp_map[i - 1]);
                i--;
            }
            free(game->temp_map);
            show_error("Memory allocation failed for temp_map row.");
        }
        i++;
    }
}


void	allocate_map_memory(t_game *game)
{
	allocate_temp_map_memory(game);
	allocate_main_map_memory(game);
}


/*void	process_map_line(t_game *game, char *line, size_t row)
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
}*/

void process_map_line(t_game *game, char *line, size_t row)
{
    size_t line_len;

    line_len = ft_strlen(line);
    if (line_len > 0 && line[line_len - 1] == '\n')
        line_len--;
    
    // Check for player and exit positions
    for (size_t col = 0; col < line_len; col++)
    {
        if (line[col] == 'P')
        {
            game->posx = col; // Set player's x position
            game->posy = row; // Set player's y position
        }
        else if (line[col] == 'E')
        {
            game->exitx = col; // Set exit's x position
            game->exity = row; // Set exit's y position
        }
    }

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
	read_map(game, file_path);
}
