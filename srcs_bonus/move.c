/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:06:52 by marvin            #+#    #+#             */
/*   Updated: 2024/08/01 12:06:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

double	calcul_newposx(int dir, t_cube *cube, double moveSpeed)
{
	if (dir == 0)
		return (cube->pos_x + cube->dir_x * moveSpeed);
	else
		return (cube->pos_x - cube->dir_x * moveSpeed);
}

double	calcul_newposy(int dir, t_cube *cube, double moveSpeed)
{
	if (dir == 0)
		return (cube->pos_y + cube->dir_y * moveSpeed);
	else
		return (cube->pos_y - cube->dir_y * moveSpeed);
}

void	make_move(t_cube *cube, int dir, double moveSpeed)
{
	double	hitbox_size;
	double	newpos_x;
	double	newpos_y;

	hitbox_size = 0.1;
	newpos_x = calcul_newposx(dir, cube, moveSpeed);
	newpos_y = calcul_newposy(dir, cube, moveSpeed);
	if (cube->map[(int)(cube->pos_y)][(int)(newpos_x + hitbox_size)] != '1'
		&& cube->map[(int)(cube->pos_y)][(int)(newpos_x - hitbox_size)] != '1'
		&& cube->map[(int)(cube->pos_y + hitbox_size)][(int)(newpos_x)] != '1'
		&& cube->map[(int)(cube->pos_y - hitbox_size)][(int)(newpos_x)] != '1'
		&& cube->map[(int)(cube->pos_y)][(int)(newpos_x + hitbox_size)] != 'C'
		&& cube->map[(int)(cube->pos_y)][(int)(newpos_x - hitbox_size)] != 'C'
		&& cube->map[(int)(cube->pos_y + hitbox_size)][(int)(newpos_x)] != 'C'
		&& cube->map[(int)(cube->pos_y - hitbox_size)][(int)(newpos_x)] != 'C')
	{
		cube->pos_x = newpos_x;
	}
	if (cube->map[(int)(newpos_y + hitbox_size)][(int)(cube->pos_x)] != '1' &&
		cube->map[(int)(newpos_y - hitbox_size)][(int)(cube->pos_x)] != '1' &&
		cube->map[(int)(newpos_y)][(int)(cube->pos_x + hitbox_size)] != '1' &&
		cube->map[(int)(newpos_y)][(int)(cube->pos_x - hitbox_size)] != '1' &&
		cube->map[(int)(newpos_y + hitbox_size)][(int)(cube->pos_x)] != 'C' &&
		cube->map[(int)(newpos_y - hitbox_size)][(int)(cube->pos_x)] != 'C' &&
		cube->map[(int)(newpos_y)][(int)(cube->pos_x + hitbox_size)] != 'C' &&
		cube->map[(int)(newpos_y)][(int)(cube->pos_x - hitbox_size)] != 'C')
	{
		cube->pos_y = newpos_y;
	}
}

void	rotate(t_cube *cub, int dir, double rotspd)
{
	double	old_dir_x;
	double	old_plane_x;

	if (dir == 1)
	{
		old_dir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(rotspd) - cub->dir_y * sin(rotspd);
		cub->dir_y = old_dir_x * sin(rotspd) + cub->dir_y * cos(rotspd);
		old_plane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(rotspd) - cub->plane_y * sin(rotspd);
		cub->plane_y = old_plane_x * sin(rotspd) + cub->plane_y * cos(rotspd);
	}
	else
	{
		old_dir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(-rotspd) - cub->dir_y * sin(-rotspd);
		cub->dir_y = old_dir_x * sin(-rotspd) + cub->dir_y * cos(-rotspd);
		old_plane_x = cub->plane_x;
		cub->plane_x = cub->plane_x
			* cos(-rotspd) - cub->plane_y * sin(-rotspd);
		cub->plane_y = old_plane_x * sin(-rotspd) + cub->plane_y * cos(-rotspd);
	}
}

int	move(t_cube *cube)
{
	if (cube->key->w == 1 || cube->key->z == 1)
		make_move(cube, 0, 0.1);
	if (cube->key->s == 1)
		make_move(cube, 1, 0.1);
	if (cube->key->a == 1 || cube->key->q == 1)
		rotate(cube, 0, 0.1);
	if (cube->key->d == 1)
		rotate(cube, 1, 0.1);
	if (cube->key->space == 1)
		open_doors(cube);
	raycasting(cube);
	return (0);
}
