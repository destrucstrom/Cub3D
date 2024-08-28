/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:08:32 by marvin            #+#    #+#             */
/*   Updated: 2024/08/01 14:08:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

int	find_player(t_test *test)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (test->map[i])
	{
		if (ft_strchr(test->map[i], '0') != NULL)
		{
			test->cord[0] = i;
			while (test->map[i][j] && test->map[i][j] != '\n'
				&& test->map[i][j] != '0')
				j++;
			test->cord[1] = j;
			return (1);
		}
		i++;
	}
	return (0);
}

int	find_player2(t_test *test)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (test->map[++i])
	{
		if (ft_strchr(test->map[i], 'N') != NULL
			|| ft_strchr(test->map[i], 'S') != NULL
			|| ft_strchr(test->map[i], 'E') != NULL
			|| ft_strchr(test->map[i], 'W') != NULL)
		{
			test->cord_bis[0] = i;
			while (test->map[i][j] && test->map[i][j] != '\n'
				&& test->map[i][j] != 'N' && test->map[i][j] != 'S'
				&& test->map[i][j] != 'E' && test->map[i][j] != 'W')
				j++;
			test->dir_temp = test->map[i][j];
			test->cord_bis[1] = j;
			return (1);
		}
	}
	return (0);
}

void	tester_map(t_test *test, int player_x, int player_y)
{
	test->map[player_y][player_x] = '1';
	if (player_y == 0 || test->map[player_y - 1][player_x] == ' ')
		test->erreur = 1;
	if (player_y == ft_strlen(test->map[player_y]) - 1
		|| test->map[player_y + 1][player_x] == ' ')
		test->erreur = 2;
	if (player_x == 0 || test->map[player_y][player_x - 1] == ' ')
		test->erreur = 3;
	if (test->map[player_y][player_x + 1] == ' ')
		test->erreur = 4;
	if (test->erreur != 0)
		return ;
	if (test->map[player_y - 1][player_x] != '1')
		tester_map(test, player_x, player_y - 1);
	if (test->map[player_y + 1][player_x] != '1')
		tester_map(test, player_x, player_y + 1);
	if (test->map[player_y][player_x - 1] != '1')
		tester_map(test, player_x - 1, player_y);
	if (test->map[player_y][player_x + 1] != '1')
		tester_map(test, player_x + 1, player_y);
	if (find_player(test) == 1)
		tester_map(test, test->cord[1], test->cord[0]);
}

int	verif_map(t_cube *cube)
{
	t_test	*test;

	test = malloc(sizeof(t_test));
	test->erreur = 0;
	test->map = ft_strdup2(cube->map);
	test->map = expende_tab(test->map);
	cube->nb_ennemy = find_ennemie(test);
	if (find_player2(test) != 0)
		tester_map(test, test->cord_bis[1], test->cord_bis[0]);
	else
		test->erreur = 5;
	if (test->erreur != 0)
		cube->error = ft_strdup("problem map");
	cube->pos_x = (double)test->cord_bis[1];
	cube->pos_y = (double)test->cord_bis[0];
	assign_dir(test->dir_temp, cube);
	free_tab(test->map);
	free(test);
	return (1);
}

void	parth_map2(t_cube *cube, int i, char **temp)
{
	int	j;

	while (temp[i])
	{
		j = 0;
		while (temp[i][j] && temp[i][j] != '\n'
			&& temp[i][j] != '1' && temp[i][j] != '0')
			j++;
		if (!temp[i])
		{
			if (cube->error == NULL)
				cube->error = ft_strdup("pas de map");
			return ;
		}
		if (temp[i][j] == '1' || temp[i][j] == '0')
		{
			recup_map(cube, i, temp);
			verif_map(cube);
			return ;
		}
		i++;
	}
}
