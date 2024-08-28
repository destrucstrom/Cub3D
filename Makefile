NAME = cub3d

SRCS_DIR = srcs/
BONUS_DIR = srcs_bonus/
MLX_DIR = minilibx-linux/
INCLUDE = includes/
INCLUDE_BONUS = includes_bonus

MLX_LIB = libmlx_Linux.a

CC = gcc -Wall -Wextra -Werror
CFLAGS = -LSD -g
MLX_FLAGS = -lX11 -lXext -lm

SRCS = main.c	\
	use.c	\
	gnl/get_next_line.c	\
	gnl/get_next_line_utils.c	\
	raycasting.c	\
	raycasting_utils.c \
	move.c	\
	interact.c	\
	tools.c	\
	map1.c	\
	map2.c	\
	map_fdraw.c	\
	map_init.c	\
	use2.c

SRCS_BONUS = main.c	\
	use.c	\
	gnl/get_next_line.c	\
	gnl/get_next_line_utils.c	\
	raycasting.c	\
	minimap.c	\
	raycasting_utils.c \
	move.c	\
	interact.c	\
	tools.c	\
	map1.c	\
	map2.c	\
	map_fdraw.c	\
	map_init.c	\
	use2.c \
	raycasting_doors.c \
	interact_bonus.c \
	uinit_asset_bonus.c \
	ennemie.c	\
	map_ennemies1.c	\
	tools_bonus.c

OBJECTS = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))
OBJ_BONUS = ${addprefix $(BONUS_DIR), $(SRCS_BONUS:.c=.o)}

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

all: mlx $(NAME)

mlx:
	make -sC $(MLX_DIR)

$(NAME): $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) $(MLX_DIR)$(MLX_LIB) $(MLX_FLAGS) -o $@ -I$(MLX_DIR) -I$(INCLUDE)

bonus: mlx $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(MLX_DIR)$(MLX_LIB) $(MLX_FLAGS) -o $(NAME) -I$(MLX_DIR) -I$(INCLUDE_BONUS)

clean:
		rm -rf $(OBJECTS) $(OBJ_BONUS)

fclean: clean
		rm -rf $(NAME)
		make clean -sC $(MLX_DIR)

re: fclean all

.PHONY: mlx