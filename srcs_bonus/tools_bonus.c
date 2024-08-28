/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:44:37 by marvin            #+#    #+#             */
/*   Updated: 2024/08/07 13:44:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

int	verif_tri_obj(t_obj *objects, int size)
{
	int	i;

	i = -1;
	while (++i < size - 1)
	{
		if (objects[i].distance < objects[i + 1].distance)
			return (0);
	}
	return (1);
}

void	tri_objects(t_obj *objects, int size)
{
	int		i;
	t_obj	temp;

	while (!verif_tri_obj(objects, size))
	{
		i = -1;
		while (++i < size - 1)
		{
			if (objects[i].distance < objects[i + 1].distance)
			{
				temp = objects[i];
				objects[i] = objects[i + 1];
				objects[i + 1] = temp;
			}
		}
	}
}
