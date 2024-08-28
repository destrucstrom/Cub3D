/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_doors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:53:30 by marvin            #+#    #+#             */
/*   Updated: 2024/08/05 15:53:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

t_data	*obj_text_rec(t_cube *cube, char c)
{
	t_data	*temp;

	if (c == 'O')
		temp = &cube->doors[0];
	else if (c == 'C')
		temp = &cube->doors[3];
	else
		temp = &cube->assets_ennemies[0];
	return (temp);
}

int	raycasting_hit_d(t_cube *cube)
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
		if (cube->map[cube->map_y][cube->map_x] == 'C' || cube->map[cube->map_y][cube->map_x] == 'O')
		{
			cube->hit = 1;
			return (1);
		}
		if (is_enemy_there(cube, cube->map_x, cube->map_y))
		{
			cube->hit = 1;
			return (2);
		}
	}
	return (0);
}

int	find_ennemies(t_cube *cube, int x, int y)
{
	int	i;

	i = -1;
	while (++i < cube->nb_ennemy)
		if ((int)cube->ennemies[i]->pos_y == y && (int)cube->ennemies[i]->pos_x == x)
			return (i);
	return (-1);		
}

double	calcul_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void draw_enemy(t_cube *cube, t_raycasting *rc, int stripe)
{
	t_data	*texture;
	t_enm	*ennemy;

	texture = &cube->assets_ennemies[0];
	ennemy = cube->ennemies[find_ennemies(cube, cube->map_x, cube->map_y)];
	rc->sprite_x = ennemy->pos_x - cube->pos_x;
	rc->sprite_y = ennemy->pos_y - cube->pos_y;
	rc->inv_det = 1.0 / (cube->plane_x * cube->dir_y - cube->plane_y * cube->dir_x);
	rc->transform_x = rc->inv_det * (cube->dir_y * rc->sprite_x - cube->dir_x * rc->sprite_y);
	rc->transform_y = rc->inv_det * (-cube->plane_y * rc->sprite_x + cube->plane_x * rc->sprite_y);

	rc->sprite_screen_x = (int)(SCREEN_WIDTH / 2 * (1 + rc->transform_x / rc->transform_y));

	rc->sprite_height = abs((int)(SCREEN_HEIGHT / rc->transform_y));
	rc->draw_start_y = -rc->sprite_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->draw_start_y < 0)
		rc->draw_start_y = 0;
	rc->draw_end_y = rc->sprite_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->draw_end_y >= SCREEN_HEIGHT)
		rc->draw_end_y = SCREEN_HEIGHT - 1;
	rc->sprite_width = abs((int)(SCREEN_HEIGHT / rc->transform_y));
	rc->draw_start_x = stripe;
	rc->draw_end_x = stripe + 1;
	rc->tex_x = (int)(256 * (rc->draw_start_x - (-rc->sprite_width / 2 + rc->sprite_screen_x))
			* texture->width / rc->sprite_width) / 256;
	if (rc->transform_y > 0 && rc->draw_start_x >= 0 && rc->draw_start_x < SCREEN_WIDTH)
	{
		rc->y = rc->draw_start_y;
		while (rc->y < rc->draw_end_y)
		{
			rc->d = (rc->y) * 256 - SCREEN_HEIGHT * 128 + rc->sprite_height * 128;
			rc->tex_y = ((rc->d * texture->height) / rc->sprite_height) / 256;
			rc->color = get_pixel_color(texture, rc->tex_x, rc->tex_y);
			if (rc->color != 0x00d100ff)
				my_mlx_pixel_put(cube->img, rc->draw_start_x, rc->y, rc->color);
			rc->y++;
		}
	}
}


void	raycast_putpix_d(t_cube *cube, t_raycasting *rc, int cond)
{
	if (cond == 2)
		return (draw_enemy(cube, rc, rc->x));
	if (cond == 0)
		return ;
	rc->y = cube->drawstart - 1;
	if (cube->side == 0)
		rc->wallx = cube->pos_y + cube->perp_wall_dist * cube->raydir_y;
	else
		rc->wallx = cube->pos_x + cube->perp_wall_dist * cube->raydir_x;
	rc->wallx -= floor(rc->wallx);
	rc->temp = obj_text_rec(cube, cube->map[cube->map_y][cube->map_x]);
	rc->tex_x = (int)(rc->wallx * (double)(rc->temp->width));
	if ((cube->side == 0 && cube->raydir_x < 0)
		|| (cube->side == 1 && cube->raydir_y > 0))
		rc->tex_x = rc->temp->width - rc->tex_x - 1;
	while (++rc->y < cube->drawend)
	{
		rc->d = rc->y * 256 - SCREEN_HEIGHT * 128 + cube->line_height * 128;
		rc->tex_y = ((rc->d * rc->temp->height) / cube->line_height) / 256;
		rc->color = get_pixel_color(rc->temp, rc->tex_x, rc->tex_y);
		if (cond == 1 && rc->color != 0x00d100ff)
			my_mlx_pixel_put(cube->img, rc->x, rc->y, rc->color);
	}
}

int	rayc_rec(t_cube *cube, t_raycasting *rc)
{
	int	n;
	int	temp_mx;
	int	temp_my;
	int	temp_side;
	double	tmp_sd_distx;
	double	tmp_sd_disty;
	double	tmp_deltax;
	double	tmp_deltay;

	cube->hit = 0;
	n = raycasting_hit_d(cube);
	temp_mx = cube->map_x;
	temp_my = cube->map_y;
	temp_side = cube->side;
	tmp_sd_distx = cube->sidedist_x;
	tmp_sd_disty = cube->sidedist_y;
	tmp_deltax = cube->deltadist_x;
	tmp_deltay = cube->deltadist_y;
	if (n > 0)
	{
		rayc_rec(cube, rc);
		cube->map_x = temp_mx;
		cube->map_y = temp_my;
		cube->side = temp_side;
		cube->sidedist_x = tmp_sd_distx;
		cube->sidedist_y = tmp_sd_disty;
		cube->deltadist_x = tmp_deltax;
		cube->deltadist_y = tmp_deltay;
		raycasting_draw(cube);
		raycast_putpix_d(cube, rc, n);
	}
	return (n);
}

void	raycasting_doors(t_cube *cube)
{
	t_raycasting	rc;
	int				tp;

	rc.x = -1;
	while (++rc.x < SCREEN_WIDTH)
	{
		raycasting_init1(cube, rc.x);
		raycasting_sidedist(cube);
		tp = rayc_rec(cube, &rc);
		raycasting_draw(cube);
		raycast_putpix_d(cube, &rc, tp);
	}
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->img->img, 0, 0);
	minimap(cube);
}
