NAME = so_long

SRC_DIR = sources
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_PATH = mlx

CC = cc
AR = ar

INCLUDES = -Iincludes -I$(MLX_PATH) -I/usr/include
MLX_FLAGS = -L$(MLX_PATH) -lmlx -L/usr/lib/X11 -lXext -lX11
CFLAGS = -g -Wall -Wextra -Werror
OBJ_DIR = objects

SRC = $(wildcard $(SRC_DIR)/*.c)
OFILES = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT) $(PRINT_LIB) $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) $(PRINT_LIB) $(LIBFT) $(MLX_FLAGS) -o $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -f $(OFILES)
	@make -C $(LIBFT_DIR) clean
	@echo "Cleaning object files"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "All is cleaned"

re: fclean all

.PHONY: all clean fclean re