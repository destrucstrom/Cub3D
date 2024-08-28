/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:02:27 by marvin            #+#    #+#             */
/*   Updated: 2024/08/06 10:02:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

void	open_doors(t_cube *cube)
{
	int	mapY;
	int	mapX;

	mapX = (int)cube->pos_x;
	mapY = (int)cube->pos_y;
	if (cube->act_doors_state == 1)
	{
		if (cube->map[mapY][mapX + 1] == 'C')
			cube->map[mapY][mapX + 1] = 'O';
		else if (cube->map[mapY][mapX + 1] == 'O')
			cube->map[mapY][mapX + 1] = 'C';
		if (cube->map[mapY][mapX - 1] == 'C')
			cube->map[mapY][mapX - 1] = 'O';
		else if (cube->map[mapY][mapX - 1] == 'O')
			cube->map[mapY][mapX - 1] = 'C';
		if (cube->map[mapY - 1][mapX] == 'C')
			cube->map[mapY - 1][mapX] = 'O';
		else if (cube->map[mapY - 1][mapX] == 'O')
			cube->map[mapY - 1][mapX] = 'C';
		if (cube->map[mapY + 1][mapX] == 'C')
			cube->map[mapY + 1][mapX] = 'O';
		else if (cube->map[mapY + 1][mapX] == 'O')
			cube->map[mapY + 1][mapX] = 'C';
	}
	cube->act_doors_state = 0;
}
