/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:14:07 by marvin            #+#    #+#             */
/*   Updated: 2024/07/31 14:14:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_color(t_data *texture, int x, int y)
{
	char	*dst;

	if (!texture || !texture->addr)
	{
		return (0xFFFFFF);
	}
	if (x < 0)
		x = 0;
	if (x >= texture->width)
		x = texture->width - 1;
	if (y < 0)
		y = 0;
	if (y >= texture->height)
		y = texture->height - 1;
	dst = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	raycasting_draw(t_cube *cube)
{
	if (cube->side == 0)
		cube->perp_wall_dist = (cube->sidedist_x - cube->deltadist_x);
	else
		cube->perp_wall_dist = (cube->sidedist_y - cube->deltadist_y);
	cube->line_height = (int)(SCREEN_HEIGHT / cube->perp_wall_dist);
	cube->drawstart = -cube->line_height / 2 + SCREEN_HEIGHT / 2;
	if (cube->drawstart < 0)
		cube->drawstart = 0;
	cube->drawend = cube->line_height / 2 + SCREEN_HEIGHT / 2;
	if (cube->drawend >= SCREEN_HEIGHT)
		cube->drawend = SCREEN_HEIGHT - 1;
}

void	draw_background(t_cube *cube, int x)
{
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
		my_mlx_pixel_put(cube->img, x, y++, cube->c);
	while (y < SCREEN_HEIGHT)
		my_mlx_pixel_put(cube->img, x, y++, cube->f);
}

t_data	*raycasting_dirwall(t_cube *cube)
{
	t_data	*temp;

	if (cube->side == 0)
	{
		if (cube->raydir_x > 0)
			temp = &cube->assets[3];
		else
			temp = &cube->assets[2];
	}
	else
	{
		if (cube->raydir_y > 0)
			temp = &cube->assets[1];
		else
			temp = &cube->assets[0];
	}
	return (temp);
}
