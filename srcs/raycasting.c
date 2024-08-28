/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:29:23 by marvin            #+#    #+#             */
/*   Updated: 2024/07/29 16:29:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	raycasting_init1(t_cube *cube, int x)
{
	cube->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	cube->raydir_x = cube->dir_x + cube->plane_x * cube->camera_x;
	cube->raydir_y = cube->dir_y + cube->plane_y * cube->camera_x;
	cube->map_x = (int)cube->pos_x;
	cube->map_y = (int)cube->pos_y;
	cube->deltadist_x = fabs(1 / cube->raydir_x);
	cube->deltadist_y = fabs(1 / cube->raydir_y);
	cube->hit = 0;
}

void	raycasting_sidedist(t_cube *cube)
{
	if (cube->raydir_x < 0)
	{
		cube->step_x = -1;
		cube->sidedist_x = (cube->pos_x - cube->map_x) * cube->deltadist_x;
	}
	else
	{
		cube->step_x = 1;
		cube->sidedist_x = (cube->map_x + 1.0 - cube->pos_x)
			* cube->deltadist_x;
	}
	if (cube->raydir_y < 0)
	{
		cube->step_y = -1;
		cube->sidedist_y = (cube->pos_y - cube->map_y) * cube->deltadist_y;
	}
	else
	{
		cube->step_y = 1;
		cube->sidedist_y = (cube->map_y + 1.0 - cube->pos_y)
			* cube->deltadist_y;
	}
}

void	raycasting_hit(t_cube *cube)
{
	while (cube->hit == 0)
	{
		if (cube->sidedist_x < cube->sidedist_y)
		{
			cube->sidedist_x += cube->deltadist_x;
			cube->map_x += cube->step_x;
			cube->side = 0;
		}
		else
		{
			cube->sidedist_y += cube->deltadist_y;
			cube->map_y += cube->step_y;
			cube->side = 1;
		}
		if (cube->map[cube->map_y][cube->map_x] == '1')
			cube->hit = 1;
	}
}

void	raycast_putpix(t_cube *cube, t_raycasting *rc)
{
	rc->y = cube->drawstart - 1;
	if (cube->side == 0)
		rc->wallx = cube->pos_y + cube->perp_wall_dist * cube->raydir_y;
	else
		rc->wallx = cube->pos_x + cube->perp_wall_dist * cube->raydir_x;
	rc->wallx -= floor(rc->wallx);
	rc->temp = raycasting_dirwall(cube);
	rc->tex_x = (int)(rc->wallx * (double)(rc->temp->width));
	if ((cube->side == 0 && cube->raydir_x < 0)
		|| (cube->side == 1 && cube->raydir_y > 0))
		rc->tex_x = rc->temp->width - rc->tex_x - 1;
	while (++rc->y < cube->drawend)
	{
		rc->d = rc->y * 256 - SCREEN_HEIGHT * 128 + cube->line_height * 128;
		rc->tex_y = ((rc->d * rc->temp->height) / cube->line_height) / 256;
		rc->color = get_pixel_color(rc->temp, rc->tex_x, rc->tex_y);
		if (cube->side == 1)
			rc->color = (rc->color >> 1) & 8355711;
		my_mlx_pixel_put(cube->img, rc->x, rc->y, rc->color);
	}
}

void	raycasting(t_cube *cube)
{
	t_raycasting	rc;

	rc.x = -1;
	while (++rc.x < SCREEN_WIDTH)
	{
		raycasting_init1(cube, rc.x);
		raycasting_sidedist(cube);
		raycasting_hit(cube);
		raycasting_draw(cube);
		draw_background(cube, rc.x);
		raycast_putpix(cube, &rc);
	}
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img->img, 0, 0);
}
