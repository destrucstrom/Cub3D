/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:14:40 by marvin            #+#    #+#             */
/*   Updated: 2024/08/07 10:34:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

int	the_end(t_cube *cube)
{
	int	i;

	i = 0;
	//while (i < cube->nb_ennemy)
	//{
	//	pthread_join(cube->ennemies[i]->threads, NULL);
	//	i++;
	//}
	free_tab(cube->map);
	free(cube->error);
	free(cube->n);
	free(cube->s);
	free(cube->e);
	free(cube->w);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(cube->mlx_ptr, cube->assets[i].img);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(cube->mlx_ptr, cube->doors[i].img);
	mlx_destroy_image(cube->mlx_ptr, cube->img->img);
	mlx_destroy_window(cube->mlx_ptr, cube->win_ptr);
	if (cube->mlx_ptr)
		mlx_destroy_display(cube->mlx_ptr);
	mlx_loop_end(cube->mlx_ptr);
	free(cube->mlx_ptr);
	free(cube->ennemies);
	exit(0);
}

char	**ft_strdup2(char **s)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	dest[i] = NULL;
	while (s[j])
	{
		dest[j] = ft_strdup(s[j]);
		j++;
	}
	return (dest);
}

char	***ft_strdup3(char ***s)
{
	char	***dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	dest = malloc(sizeof(char **) * (i + 1));
	dest[i] = NULL;
	while (s[j])
	{
		dest[j] = ft_strdup2(s[j]);
		j++;
	}
	return (dest);
}

void	taille(t_cube *cube, int fd)
{
	char	*temp;

	cube->length = 1;
	cube->width = 0;
	temp = get_next_line(fd);
	while (temp[cube->width] != '\n')
		cube->width++;
	cube->width--;
	while (temp != NULL)
	{
		free(temp);
		temp = NULL;
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		cube->length++;
	}
	free(temp);
}

void	divide_dir2(char *dir, char **temp2, t_cube *cube)
{
	if (ft_strchr(dir, 'F') != NULL && cube->cf == 0)
	{
		cube->f = rgb_to_hex(temp2, cube);
		cube->cf++;
		return ;
	}
	if (ft_strchr(dir, 'C') != NULL && cube->cc == 0)
	{
		cube->c = rgb_to_hex(temp2, cube);
		cube->cc++;
		return ;
	}
	cube->error = ft_strdup("plus de 1 pour une direction");
}
