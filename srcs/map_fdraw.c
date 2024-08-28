/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fdraw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:13:24 by marvin            #+#    #+#             */
/*   Updated: 2024/08/01 14:13:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	divide_dir(char *dir, char *temp2, t_cube *cube)
{
	if (ft_strchr(dir, 'N') != NULL && cube->cn == 0)
	{
		cube->n = ft_strdup(temp2);
		cube->cn++;
		return ;
	}
	if (ft_strchr(dir, 'S') != NULL && cube->cs == 0)
	{
		cube->s = ft_strdup(temp2);
		cube->cs++;
		return ;
	}
	if (ft_strchr(dir, 'E') != NULL && cube->ce == 0)
	{
		cube->e = ft_strdup(temp2);
		cube->ce++;
		return ;
	}
	if (ft_strchr(dir, 'W') != NULL && cube->cw == 0)
	{
		cube->w = ft_strdup(temp2);
		cube->cw++;
		return ;
	}
	cube->error = ft_strdup("plus de 1 pour une direction");
}

int	rgb_to_hex(char **temp2, t_cube *cube)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(temp2[0]);
	g = ft_atoi(temp2[1]);
	b = ft_atoi(temp2[2]);
	if (r >= 0 && r < 256 && g >= 0 && g < 256 && b >= 0 && b < 256)
		return ((r << 16) + (g << 8) + b);
	else
	{
		cube->error = ft_strdup("Error: invalid rgb");
		return (0);
	}
}

void	parth_color(t_tri_index *ind, int i, char **temp, char **temp2)
{
	ind->k = 0;
	while (temp[i][ind->j] && (temp[i][ind->j] == ' '
			|| temp[i][ind->j] == '	'))
		ind->j++;
	if (!temp[i][ind->j])
		return ;
	ind->l = ind->j;
	while (temp[i][ind->j] && temp[i][ind->j] != ' '
			&& temp[i][ind->j] != '	'
			&& temp[i][ind->j] != ',' && temp[i][ind->j++] != '\n')
		ind->k++;
	temp2[ind->m] = malloc(sizeof(char) * (ind->k + 1));
	ind->j = 0;
	while (temp[i][ind->l] && temp[i][ind->l] != ' '
			&& temp[i][ind->l] != '	' && temp[i][ind->l] != ','
			&& temp[i][ind->l] != '\n')
		temp2[ind->m][ind->j++] = temp[i][ind->l++];
	temp2[ind->m][ind->j] = '\0';
	ind->j = ind->l;
	while (temp[i][ind->j] && (temp[i][ind->j] == ' '
			|| temp[i][ind->j] == '	' || temp[i][ind->j] == ','))
		ind->j++;
	ind->m++;
}

void	recup_texture(t_cube *cube, char **temp, char *dir, t_tri_index	*dex)
{
	char		*temp2;
	t_tri_index	*acd;

	acd = malloc(sizeof(t_tri_index));
	acd->j = (dex->j + 2);
	acd->k = 0;
	while (temp[dex->l][acd->j] && (temp[dex->l][acd->j] == ' '
		|| temp[dex->l][acd->j] == '	'))
		acd->j++;
	if (!temp[dex->l][acd->j])
		return ;
	acd->l = acd->j;
	while (temp[dex->l][acd->j] && temp[dex->l][acd->j] != ' '
		&& temp[dex->l][acd->j] != '	' && temp[dex->l][acd->j++] != '\n')
		acd->k++;
	temp2 = malloc(sizeof(char) * (acd->k));
	acd->j = 0;
	while (temp[dex->l][acd->l] && temp[dex->l][acd->l] != ' '
		&& temp[dex->l][acd->l] != '	' && temp[dex->l][acd->l] != '\n')
		temp2[acd->j++] = temp[dex->l][acd->l++];
	temp2[acd->j - 1] = '\0';
	divide_dir(dir, temp2, cube);
	free(temp2);
	free(acd);
}

void	recup_color(t_cube *cube, char **temp, char *dir, t_tri_index	*dex)
{
	char		**temp2;
	t_tri_index	*ind;

	ind = malloc(sizeof(t_tri_index));
	ind->k = 0;
	ind->j = dex->j + 1;
	ind->m = 0;
	temp2 = malloc(sizeof(char *) * 4);
	temp2[3] = '\0';
	while (ind->m <= 2)
		parth_color(ind, dex->l, temp, temp2);
	divide_dir2(dir, temp2, cube);
	free_tab(temp2);
	free(ind);
}
