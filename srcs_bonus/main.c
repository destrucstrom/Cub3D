/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:20:23 by marvin            #+#    #+#             */
/*   Updated: 2024/07/22 16:20:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

void	load_img(t_cube	*cube, int i, char *asset, t_data *tab)
{
	int	width;
	int	height;

	tab[i].img = mlx_xpm_file_to_image(cube->mlx_ptr,
			asset, &width, &height);
	if (!tab[i].img)
		exit(EXIT_FAILURE);
	tab[i].addr = mlx_get_data_addr(tab[i].img,
			&tab[i].bits_per_pixel, &tab[i].line_length,
			&tab[i].endian);
	tab[i].width = width;
	tab[i].height = height;
}

void	load_textures(t_cube *cube)
{
	load_img(cube, 0, cube->n, cube->assets);
	load_img(cube, 1, cube->s, cube->assets);
	load_img(cube, 2, cube->w, cube->assets);
	load_img(cube, 3, cube->e, cube->assets);
	load_img(cube, 0, "./assets/door_open.xpm", cube->doors);
	load_img(cube, 1, "./assets/door_open_s.xpm", cube->doors);
	load_img(cube, 2, "./assets/door_open_e.xpm", cube->doors);
	load_img(cube, 3, "./assets/door_close.xpm", cube->doors);
	load_img(cube, 0, "./assets/psycho.xpm", cube->assets_ennemies);
}

void	init_cube(t_cube *cube, t_data *img, t_key *key)
{
	cube->mlx_ptr = mlx_init();
	cube->img = img;
	cube->key = key;
	cube->win_ptr = mlx_new_window(cube->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Cub3D");
	cube->img->img = mlx_new_image(cube->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	cube->img->addr = mlx_get_data_addr(cube->img->img,
			&cube->img->bits_per_pixel,
			&cube->img->line_length, &cube->img->endian);
	cube->dir_x = 0;
	cube->plane_x = 0;
	cube->dir_y = 0;
	cube->plane_y = 0;
}

void	load_game_resources(t_cube *cube, char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	taille(cube, fd);
	close(fd);
	fd = open(map_path, O_RDONLY);
	setmap(cube, fd);
	close(fd);
	init_ennemies(cube);
	init_key(cube);
	load_textures(cube);
}

int	main(int ac, char **av)
{
	t_cube	cube;
	t_data	img;
	t_key	key;

	if (ac != 2 || !check_map_format(av[1], av))
		return (write(2, "Error: Invalid input\n", 21), 0);
	init_cube(&cube, &img, &key);
	load_game_resources(&cube, av[1]);
	raycasting(&cube);
	mlx_hook(cube.win_ptr, 2, (1L << 0), handle_key, &cube);
	mlx_hook(cube.win_ptr, 3, (1L << 1), handle_key2, &cube);
	mlx_hook(cube.win_ptr, 6, (1L << 6), mouse, &cube);
	mlx_hook(cube.win_ptr, 17, (1L << 17), the_end, &cube);
	mlx_loop_hook(cube.mlx_ptr, move, &cube);
	mlx_loop(cube.mlx_ptr);
	return (0);
}
