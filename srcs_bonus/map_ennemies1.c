/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ennemies1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:17:16 by marvin            #+#    #+#             */
/*   Updated: 2024/08/06 16:17:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

int	is_enemy_there(t_cube *cube, int x, int y)
{
	int	i;

	i = -1;
	while (++i < cube->nb_ennemy)
		if ((int)cube->ennemies[i]->pos_y == y && (int)cube->ennemies[i]->pos_x == x)
			return (1);
	return (0);		
}
