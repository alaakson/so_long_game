/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaakson <alaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:35 by alaakson          #+#    #+#             */
/*   Updated: 2024/10/10 15:02:39 by alaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>

# define IMG_HEIGHT 32
# define IMG_WIDTH 32

# define BACK "sources/sprites/back.xpm"
# define LEFT "sources/sprites/left.xpm"
# define RIGHT "sources/sprites/right.xpm"
# define FRONT "sources/sprites/front.xpm"
# define TILE "sources/sprites/floor.xpm"
# define VGG "sources/sprites/wall.xpm"
# define EXIT "sources/sprites/exit.xpm"
# define COL "sources/sprites/item.xpm"
# define C_GATE "sources/sprites/closed_gate.xpm"
# define EMPTY "sources/sprites/empty.xpm"

# define WALL '1'
# define FLOOR '0'
# define KEY 'C'
# define PLAYER 'P'
# define MAP_EXIT 'E'

# define KEY_UP 119
# define KEY_LEFT 97
# define KEY_DOWN 115
# define KEY_RIGHT 100
# define KEY_Q				113
# define KEY_ESC  			65307

typedef struct s_map
{
	char	**map;
	int		item;
	size_t	x;
	size_t	y;
	size_t	rows;
	size_t	columns;
	size_t	width;
	size_t	height;	
}	t_map;

typedef struct t_game
{
	int		resx;
	int		resy;
	int		steps;
	size_t	posy;
	size_t	posx;
	int		collectible;
	int		collectible_check;
	int		num_player;
	int		num_exit;
	int		map_validity;
	int		exit_reach;
	void	*mlx;
	void	*win;
	void	*p_front;
	void	*p_left;
	void	*p_right;
	void	*p_back;
	void	*empty;
	void	*exit;
	void	*wall;
	void	*closed_gate;
	void	*key;
	void	*floor;
	void	*player;
	char	**temp_map;
	int		img_h;
	int		img_w;
	size_t	win_width;
	size_t	win_height;
	int		game_over;
	int		game_finished;
	int		start;
	int		end;
	size_t	exity;
	size_t	exitx;
	t_map	map;
}	t_game;

void	handle_vertical_movement(t_game *game, int direction);
void	handle_horizontal_movement(t_game *game, int direction);
void	finish_map(t_game *game);
int		horizontalwall(t_game *game);
int		verticalwall(t_game *game);
void	show_error(const char *msg);
void	initialize_map(t_game *game, const char *file_path);
void	free_map(t_game *game);
int		key_hook(int keycode, t_game *game);
void	sprite_init(t_game *game);
void	initialize_map_memory(t_game *game, size_t rows, size_t columns);
void	load_map(t_game *game, const char *file_path);
void	init(t_game *game);
void	build_map(t_map *map, const char *file_path);
void	handle_map(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		check_walls(t_game *game);
void	map_and_win(t_game *game, size_t new_x, size_t new_y, void *new_image);
int		check_images_loaded(t_game *game);
void	draw_map(t_game *game);
void	print_map(t_game *game);
void	update_display(t_game *game);
void	is_map_done(t_game *game, size_t new_x, size_t new_y);
int		close_game_on_enter(int keycode, t_game *game);
void	game_complete(t_game *game, size_t new_x, size_t new_y);
void	*load_image(t_game *game, const char *path);
void	map_error(char *s);
void	handle_map_errors(t_game *game, int error_flag);
void	check_map_errors(t_game *game);
int		check_tiles(t_game *game);

#endif
