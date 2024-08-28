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

#include "../includes/cube3d.h"

void	load_img(t_cube	*cube, int i, char *asset)
{
	int	width;
	int	height;

	cube->assets[i].img = mlx_xpm_file_to_image(cube->mlx_ptr,
			asset, &width, &height);
	if (!cube->assets[i].img)
		exit(EXIT_FAILURE);
	cube->assets[i].addr = mlx_get_data_addr(cube->assets[i].img,
			&cube->assets[i].bits_per_pixel, &cube->assets[i].line_length,
			&cube->assets[i].endian);
	cube->assets[i].width = width;
	cube->assets[i].height = height;
}

void	load_textures(t_cube *cube)
{
	load_img(cube, 0, cube->n);
	load_img(cube, 1, cube->s);
	load_img(cube, 2, cube->w);
	load_img(cube, 3, cube->e);
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
