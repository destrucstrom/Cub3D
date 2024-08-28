/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:56:28 by marvin            #+#    #+#             */
/*   Updated: 2024/08/06 09:41:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

void	print_square(int x, int y, t_cube *cube, int color)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < cube->size_mini)
	{
		while (j < cube->size_mini)
		{
			my_mlx_pixel_put(cube->img, (y * cube->size_mini) + j,
				(x * cube->size_mini) + i, color);
			j++;
		}
		j = 1;
		i++;
	}
}

void	minimap(t_cube *cube)
{
	int	i;
	int	j;
	int	pose;
	int	pose2;

	i = 0;
	j = 0;
	pose = SCREEN_HEIGHT / 15;
	pose2 = SCREEN_WIDTH / 15;
	while (cube->map[i])
	{
		while (cube->map[i][j] && cube->map[i][j] != '\n')
		{
			if (cube->map[i][j] == '1')
				print_square(i + pose, j + pose2, cube, 0x0000FF);
			if (cube->map[i][j] == 'C')
				print_square(i + pose, j + pose2, cube, 0xFF0000);
			if (cube->map[i][j] == '5')
				print_square(i + pose, j + pose2, cube, 0x850009);
			j++;
		}
		j = 0;
		i++;
	}
	i = -1;
	while (i++ < cube->nb_ennemy - 1)
		print_square(cube->ennemies[i]->pos_y + pose, cube->ennemies[i]->pos_x + pose2, cube, 0xFFFF);
	print_square(cube->pos_y + pose, cube->pos_x + pose2, cube, 0xFF00FF);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img->img, 0, 0);
}
