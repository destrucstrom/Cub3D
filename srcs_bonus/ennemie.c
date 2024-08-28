/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemie.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:33:48 by marvin            #+#    #+#             */
/*   Updated: 2024/08/07 14:33:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"
/*
void	chemin(int y, int x, t_en *en, int pose)
{
	if (y == en->end_y && x == en->end_x)
		return ;
	en->map[y][x] = pose;
	if (en->map[y - 1][x] != '1')
		if (en->map[y - 1][x] > pose)
			chemin(y - 1, x, en, pose + 1);
	if (en->map[y + 1][x] != '1')
		if (en->map[y + 1][x] > pose)
			chemin(y + 1, x, en, pose + 1);
	if (en->map[y][x - 1] != '1')
		if (en->map[y][x - 1] > pose)
			chemin(y, x - 1, en, pose + 1);
	if (en->map[y][x + 1] != '1')
		if (en->map[y][x + 1] > pose)
			chemin(y, x + 1, en, pose + 1);
}

void	*ennemie(void *arg)
{
	t_enm	*ennemies;
	t_en	*en;

	en = malloc(sizeof(t_en));
	ennemies = (t_enm *)arg;
	en->map = ft_strdup2(ennemies->cube->map);
	en->end_y = ennemies->cube->pos_y;
	en->end_x = ennemies->cube->pos_x;
	chemin(ennemies->pos_y, ennemies->pos_x, en, 1);
	printf("%i\n", ennemies->nbr);
	print_tab(en->map);
	//while (1)
	//{
	//	if (ennemies->cube->key->z == 1)
	//		return (NULL);
		//make_move_en(ennemies->cube, 0, 0.1, ennemies->nbr);
	//}
	return (NULL);
}
*/

void print_map_as_int(char **map) {
    int i = 0;
    int j;

    while (map[i]) { // On parcourt les lignes tant qu'on ne rencontre pas un pointeur NULL (\0)
        j = 0;
        while (map[i][j]) { // On parcourt les colonnes tant qu'on ne rencontre pas un \0
            // On convertit le caractère en entier en soustrayant '0'
            printf("%i ", map[i][j]);
            j++;
        }
        printf("\n"); // On passe à la ligne suivante après chaque ligne de la map
        i++;
    }
}

void	find_path(t_en *en)
{
	int y = en->end_y;
    int x = en->end_x;
    int dist = en->map[y][x];
    int path_index = 0;

    while (dist > 1)
	{
        if (y > 0 && en->map[y - 1][x] == dist - 1)
		{
            en->path[path_index++] = 'B'; // Bas
            y--;
        } else if ( en->map[y + 1][x] == dist - 1)
		{
            en->path[path_index++] = 'H'; // Haut
            y++;
        } else if (x > 0 && en->map[y][x - 1] == dist - 1)
		{
            en->path[path_index++] = 'D'; // Droite
            x--;
        } else if (en->map[y][x + 1] == dist - 1)
		{
            en->path[path_index++] = 'G'; // Gauche
            x++;
        } else
		{
			en->map[y][x] = '0';
			if (en->end_x == x && en->end_y == y)
			{
				en->path[0] = '\0';
				//en->erreur = 1;
				return ;
			}
			else
            	return (find_path(en));
        }
        dist--;
    }
	//path_index++;
    en->path[path_index] = '\0';
	free_tab(en->map);
}

void	bfs(int y, int x, t_en *en, int dist)
{
	if ((y == en->end_y && x == en->end_x))
	{
		en->erreur = 0;
		return ;
	}
	if (dist == 5)
		return ;
    if (en->map[y - 1][x] != '1' && en->map[y - 1][x] != 'C' && (en->map[y - 1][x] == '0' || en->map[y - 1][x] > dist + 1))// Mouvement vers le haut
	{
		en->map[y - 1][x] = dist + 1;
		bfs(y - 1, x, en, dist + 1);
	}
    if (en->map[y + 1][x] != '1' && en->map[y + 1][x] != 'C' && (en->map[y + 1][x] == '0' || en->map[y + 1][x] > dist + 1))// Mouvement vers le bas
	{
		en->map[y + 1][x] = dist + 1;
		bfs(y + 1, x, en, dist + 1);
	}
    if (en->map[y][x - 1] != '1' && en->map[y][x - 1] != 'C' && (en->map[y][x - 1] == '0' || en->map[y][x - 1] > dist + 1))// Mouvement vers la gauche
	{
		en->map[y][x - 1] = dist + 1;
		bfs(y, x - 1, en, dist + 1);
	}
    if (en->map[y][x + 1] != '1' && en->map[y][x + 1] != 'C' && (en->map[y][x + 1] == '0' || en->map[y][x + 1] > dist + 1))// Mouvement vers la droite
	{
		en->map[y][x + 1] = dist + 1;
		bfs (y, x + 1, en, dist + 1);
	}
}
int	where_go(t_en *en, t_enm *ennemies)
{
	en->map = ft_strdup2(ennemies->cube->map);
    en->end_y = ennemies->cube->pos_y;
    en->end_x = ennemies->cube->pos_x;
	en->map[(int)ennemies->pos_y][(int)ennemies->pos_x] = 1;
	en->map[(int)en->end_y][(int)en->end_x] = 50;
    bfs((int)ennemies->pos_y, (int)ennemies->pos_x, en, 1);
	if (en->erreur == 1)
		return (0);
	find_path(en);
	return(ft_strlen(en->path));
}

void *ennemie(void *arg)
{
    t_enm *ennemies;
    t_en *en;
	int i;

    ennemies = (t_enm *)arg;
    en = malloc(sizeof(t_en));
	en->erreur = 1;
	while (en->erreur == 1)
	{
		i = where_go(en, ennemies);
		usleep(400000);
	}
	while (i > -1)
	{
		if (ennemies->cube->pos_x != ennemies->pos_player_x || ennemies->cube->pos_y != ennemies->pos_player_y)
		{
			en->erreur = 1;
			while (en->erreur == 1)
			{
				i = where_go(en, ennemies);
				usleep(5000);
			}
			ennemies->pos_player_x = ennemies->cube->pos_x;
			ennemies->pos_player_y = ennemies->cube->pos_y;
		}
    	if (en->path[i] == 'H')
    	    make_move_en(ennemies->cube, 0, 1, ennemies->nbr);
    	else if (en->path[i] == 'B')
    	    make_move_en(ennemies->cube, 1, 1, ennemies->nbr);
		else if (en->path[i] == 'G')
    	    make_move_en(ennemies->cube, 2, 1, ennemies->nbr);
		else if (en->path[i] == 'D')
    	    make_move_en(ennemies->cube, 3, 1, ennemies->nbr);
		/*if (i == 0)
		{
			printf("dead\n");
			break;
		}*/
		//usleep(500000);
		i--;
	}
	printf("dead\n");
    free(en);

    return NULL;
}

void	mouv_en(t_cube *cube)
{
	int nb;

	nb = 0;
	//pthread_create(&cube->ennemies[nb]->threads, NULL, ennemie, cube->ennemies[nb]);
	while (nb < cube->nb_ennemy)
	{
		pthread_create(&cube->ennemies[nb]->threads, NULL, ennemie, cube->ennemies[nb]);
		nb++;
	}
	//make_move_en(cube, 0, 0.1, nb); //z
	//make_move_en(cube, 1, 0.1, nb); //s
	//rotate_en(cube, 0, 0.1, nb); //q
	//rotate_en(cube, 1, 0.1, nb); // d
}


double	calcul_newposx_en(int dir, t_cube *cube, double moveSpeed, int nb)
{
	if (dir == 0)
		return (cube->ennemies[nb]->pos_x);
	else if (dir == 1)
		return (cube->ennemies[nb]->pos_x);
	else if (dir == 2)
		return (cube->ennemies[nb]->pos_x - moveSpeed);
	else
		return (cube->ennemies[nb]->pos_x + moveSpeed);
}

double	calcul_newposy_en(int dir, t_cube *cube, double moveSpeed, int nb)
{
	if (dir == 0)
		return (cube->ennemies[nb]->pos_y - moveSpeed);
	else if (dir == 1)
		return (cube->ennemies[nb]->pos_y + moveSpeed);
	else if (dir == 2)
		return (cube->ennemies[nb]->pos_y);
	else
		return (cube->ennemies[nb]->pos_y);
}

void	make_move_en(t_cube *cube, int dir, double moveSpeed, int nb)
{
	double	newpos_x;
	double	newpos_y;
	int		i;

	i = 0;
	newpos_x = calcul_newposx_en(dir, cube, moveSpeed, nb);
	newpos_y = calcul_newposy_en(dir, cube, moveSpeed, nb);
	
	while (cube->ennemies[i])
	{
		if (i == nb)
			i++;
		if (!cube->ennemies[i])
			return ;
		while(cube->ennemies[i]->pos_x == newpos_x && cube->ennemies[i]->pos_y == newpos_y)
			usleep(6000);
		i++;
	}
	if (cube->map[(int)(cube->ennemies[nb]->pos_y)][(int)(newpos_x)] != '1'
		&& cube->map[(int)(cube->ennemies[nb]->pos_y)][(int)(newpos_x)] != 'C')
		cube->ennemies[nb]->pos_x = newpos_x;
	if (cube->map[(int)(newpos_y)][(int)(cube->ennemies[nb]->pos_x)] != '1'
		&& cube->map[(int)(newpos_y)][(int)(cube->ennemies[nb]->pos_x)] != 'C')
		cube->ennemies[nb]->pos_y = newpos_y;
	else
		printf("problem\n");
	usleep(400000);
}

void	rotate_en(t_cube *cube, int dir, double rotspd, int nb)
{
	double	old_dir_x;

	if (dir == 1)
	{
		old_dir_x = cube->ennemies[nb]->dir_x;
		cube->ennemies[nb]->dir_x = cube->ennemies[nb]->dir_x * cos(rotspd) - cube->ennemies[nb]->dir_y * sin(rotspd);
		cube->ennemies[nb]->dir_y = old_dir_x * sin(rotspd) + cube->ennemies[nb]->dir_y * cos(rotspd);
	}
	else
	{
		old_dir_x = cube->ennemies[nb]->dir_x;
		cube->ennemies[nb]->dir_x = cube->ennemies[nb]->dir_x * cos(-rotspd) - cube->ennemies[nb]->dir_y * sin(-rotspd);
		cube->ennemies[nb]->dir_y = old_dir_x * sin(-rotspd) + cube->ennemies[nb]->dir_y * cos(-rotspd);
	}
}