/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:40:45 by marvin            #+#    #+#             */
/*   Updated: 2024/08/01 14:40:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	verif_all(t_cube *cube)
{
	if (cube->cn == 0 || cube->cs == 0 || cube->ce == 0
		|| cube->cw == 0 || cube->cc == 0 || cube->cf == 0)
		return (1);
	return (0);
}

void	verif_all2(t_cube *cube)
{
	if (cube->cn == 0 || cube->cs == 0 || cube->ce == 0
		|| cube->cw == 0 || cube->cc == 0 || cube->cf == 0)
		if (cube->error == NULL)
			cube->error = ft_strdup("not enough element");
}

void	set_val(t_tri_index	*tri, char **tab)
{
	tri->l = 0;
	tri->m = 0;
	while (tab[tri->l])
	{
		if (tri->m < ft_strlen(tab[tri->l]))
			tri->m = ft_strlen(tab[tri->l]);
		tri->l++;
	}
	tri->m++;
	tri->j = 0;
	tri->k = 0;
}

void	assign_dir(char dir, t_cube *cube)
{
	if (dir == 'N')
	{
		cube->dir_y = -1;
		cube->plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		cube->dir_y = 1;
		cube->plane_x = -0.66;
	}
	else if (dir == 'W')
	{
		cube->dir_x = -1;
		cube->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		cube->dir_x = 1;
		cube->plane_y = 0.66;
	}
}

void	init_all(t_cube *cube)
{
	cube->cc = 0;
	cube->ce = 0;
	cube->cf = 0;
	cube->cn = 0;
	cube->cw = 0;
	cube->cs = 0;
	cube->c = 0;
	cube->e = NULL;
	cube->f = 0;
	cube->n = NULL;
	cube->w = NULL;
	cube->s = NULL;
	cube->map = NULL;
	cube->error = NULL;
}
