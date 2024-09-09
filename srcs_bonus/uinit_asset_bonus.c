/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uinit_asset_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:02:08 by marvin            #+#    #+#             */
/*   Updated: 2024/09/09 11:30:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

void	divide_dir3(char *dir, char *temp2, t_cube *cube)
{
	if (ft_strchr(dir, '1') != NULL && cube->assets_cd[0] == 0)
	{
		cube->doors_assets[0] = ft_strdup(temp2);
		cube->assets_cd[0]++;
		return ;
	}
	if (ft_strchr(dir, '2') != NULL && cube->assets_cd[1] == 0)
	{
		cube->doors_assets[1] = ft_strdup(temp2);
		cube->assets_cd[1]++;
		return ;
	}
	if (ft_strchr(dir, '3') != NULL && cube->assets_cd[2] == 0)
	{
		cube->doors_assets[2] = ft_strdup(temp2);
		cube->assets_cd[2]++;
		return ;
	}
	if (ft_strchr(dir, '4') != NULL && cube->assets_cd[3] == 0)
	{
		cube->doors_assets[3] = ft_strdup(temp2);
		cube->assets_cd[3]++;
		return ;
	}
	cube->error = ft_strdup("more than 1 texture for each door");
}

void	recup_texture2(t_cube *cube, char **temp, char *dir, t_tri_index *dex)
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
	divide_dir3(dir, temp2, cube);
	free(temp2);
	free(acd);
}

void	parth_map_nsew2(t_cube *cube, char **temp, t_tri_index	*dex)
{
	if (temp[dex->l][dex->j] == 'D' && temp[dex->l][dex->j + 1] == '1'
		&& temp[dex->l][dex->j + 2] == ' ')
		recup_texture2(cube, temp, "1", dex);
	else if (temp[dex->l][dex->j] == 'D' && temp[dex->l][dex->j + 1] == '2'
		&& temp[dex->l][dex->j + 2] == ' ')
		recup_texture2(cube, temp, "2", dex);
	else if (temp[dex->l][dex->j] == 'D' && temp[dex->l][dex->j + 1] == '3'
		&& temp[dex->l][dex->j + 2] == ' ')
		recup_texture2(cube, temp, "3", dex);
	else if (temp[dex->l][dex->j] == 'D' && temp[dex->l][dex->j + 1] == '4'
		&& temp[dex->l][dex->j + 2] == ' ')
		recup_texture2(cube, temp, "4", dex);
}

int	find_ennemie(t_test *test)
{
	int	i;
	int	j;
	int ennemie;

	i = 0;
	ennemie = 0;
	while (test->map[i])
	{
		j = 0;
		if (ft_strchr(test->map[i], 'M') != NULL)
		{
			while (test->map[i][j] && test->map[i][j] != '\n')
			{
				if (test->map[i][j] == 'M')
				{
					ennemie++;
				}
				j++;
			}
		}
		i++;
	}
	return (ennemie);
}

void	init_ennemies(t_cube *cube)
{
	int	i;
	int	j;
	int en;

	i = 0;
	en = 0;
	pthread_mutex_init(&cube->mutex_enemies, NULL);
	cube->ennemies = malloc((cube->nb_ennemy + 1) * sizeof(t_enm *));
	cube->ennemies[cube->nb_ennemy] = '\0';
	while (cube->map[i])
	{
		j = 0;
		if (ft_strchr(cube->map[i], 'M') != NULL)
		{
			while (cube->map[i][j] && cube->map[i][j] != '\n')
			{
				if (cube->map[i][j] == 'M' && en < cube->nb_ennemy)
				{
					cube->ennemies[en] = malloc(sizeof(t_enm));
					cube->ennemies[en]->cube = cube;
					cube->ennemies[en]->dir_x = -1;
					cube->ennemies[en]->dir_y = 0.0;
					cube->ennemies[en]->pos_x = j;
					cube->ennemies[en]->pos_y = i;
					cube->ennemies[en]->nbr = en;
					cube->ennemies[en]->pos_player_x = cube->ennemies[en]->cube->pos_x;
					cube->ennemies[en]->pos_player_y = cube->ennemies[en]->cube->pos_y;
					en++;
				}
				j++;
			}
		}
		i++;
	}
	mouv_en(cube);
}
