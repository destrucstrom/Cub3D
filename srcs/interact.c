/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:10:18 by marvin            #+#    #+#             */
/*   Updated: 2024/08/01 12:10:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	handle_key(int key, t_cube *cube)
{
	if (key == 65307)
		the_end(cube);
	if (key == 122)
		cube->key->z = 1;
	if (key == 113)
		cube->key->q = 1;
	if (key == 119)
		cube->key->w = 1;
	if (key == 115)
		cube->key->s = 1;
	if (key == 97)
		cube->key->a = 1;
	if (key == 100)
		cube->key->d = 1;
	return (0);
}

int	handle_key2(int key, t_cube *cube)
{
	if (key == 122)
		cube->key->z = 0;
	if (key == 113)
		cube->key->q = 0;
	if (key == 119)
		cube->key->w = 0;
	if (key == 115)
		cube->key->s = 0;
	if (key == 97)
		cube->key->a = 0;
	if (key == 100)
		cube->key->d = 0;
	return (0);
}

void	init_key(t_cube *cube)
{
	cube->key->w = 0;
	cube->key->s = 0;
	cube->key->a = 0;
	cube->key->d = 0;
	cube->key->q = 0;
	cube->key->z = 0;
	cube->key->mouse_x = 0;
	cube->key->mouse_y = 0;
	cube->key->old_x = 0;
	cube->size_mini = 10;
}

int	mouse(int x, int y, t_cube *cube)
{
	cube->key->mouse_x = x;
	cube->key->mouse_y = y;
	if (cube->key->old_x != 0)
	{
		if (cube->key->mouse_x < cube->key->old_x)
			rotate(cube, 0, 0.05);
		if (cube->key->mouse_x > cube->key->old_x)
			rotate(cube, 1, 0.05);
	}
	cube->key->old_x = cube->key->mouse_x;
	return (0);
}
