/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:06:00 by marvin            #+#    #+#             */
/*   Updated: 2024/08/06 16:09:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

void	recup_map(t_cube *cube, int i, char **temp)
{
	int	j;

	j = i;
	while (temp[j] && (ft_strchr(temp[j], '1') || ft_strchr(temp[j], '0')))
		j++;
	cube->map = malloc(sizeof(char *) * ((j - i) + 1));
	j = 0;
	while (temp[i] && (ft_strchr(temp[i], '1') != NULL
			|| ft_strchr(temp[i], '0') != NULL))
		cube->map[j++] = ft_strdup(temp[i++]);
	cube->map[j] = '\0';
}

void	parth_map_nsew(t_cube *cube, char **temp, t_tri_index	*dex)
{
	if (temp[dex->l][dex->j] && temp[dex->l][dex->j + 1]
		&& temp[dex->l][dex->j + 2])
	{
		if (temp[dex->l][dex->j] == 'N' && temp[dex->l][dex->j + 1] == 'O'
			&& temp[dex->l][dex->j + 2] == ' ')
			recup_texture(cube, temp, "N", dex);
		else if (temp[dex->l][dex->j] == 'S' && temp[dex->l][dex->j + 1] == 'O'
			&& temp[dex->l][dex->j + 2] == ' ')
			recup_texture(cube, temp, "S", dex);
		else if (temp[dex->l][dex->j] == 'W' && temp[dex->l][dex->j + 1] == 'E'
			&& temp[dex->l][dex->j + 2] == ' ')
			recup_texture(cube, temp, "W", dex);
		else if (temp[dex->l][dex->j] == 'E' && temp[dex->l][dex->j + 1] == 'A'
			&& temp[dex->l][dex->j + 2] == ' ')
			recup_texture(cube, temp, "E", dex);
		parth_map_nsew2(cube, temp, dex);
	}
	if (temp[dex->l][dex->j] && temp[dex->l][dex->j + 1])
	{
		if (temp[dex->l][dex->j] == 'C' && temp[dex->l][dex->j + 1] == ' ')
			recup_color(cube, temp, "C", dex);
		else if (temp[dex->l][dex->j] == 'F' && temp[dex->l][dex->j + 1] == ' ')
			recup_color(cube, temp, "F", dex);
	}
}

void	parth_map(t_cube *cube, char **temp)
{
	t_tri_index	*dex;

	dex = malloc(sizeof(t_tri_index));
	dex->l = 0;
	while (temp[dex->l] && verif_all(cube) != 0)
	{
		dex->j = 0;
		while (temp[dex->l][dex->j] && temp[dex->l][dex->j] != '\n'
			&& (temp[dex->l][dex->j] == ' ' || temp[dex->l][dex->j] == '	'))
			dex->j++;
		parth_map_nsew(cube, temp, dex);
		dex->l++;
	}
	verif_all2(cube);
	parth_map2(cube, dex->l, temp);
	if (cube->error != NULL)
	{
		printf("Error : %s\n", cube->error);
		free(dex);
		free_tab(temp);
		the_end_error(cube);
	}
	free(dex);
}

void	setmap(t_cube *cube, int fd)
{
	int		k;
	char	**temp;

	k = 0;
	temp = malloc(sizeof(char *) * (cube->length + 1));
	temp[cube->length] = '\0';
	init_all(cube);
	while (k < cube->length)
	{
		temp[k] = get_next_line(fd);
		k++;
	}
	parth_map(cube, temp);
	free_tab(temp);
}

int	check_map_format(char *s, char **av)
{
	int	l;
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
		return (0);
	close(fd);
	l = ft_strlen(s);
	if (l < 4)
		return (0);
	if (s[l - 1] != 'b' || s[l - 2] != 'u' || s[l - 3] != 'c'
		|| s[l - 4] != '.')
		return (0);
	return (1);
}
