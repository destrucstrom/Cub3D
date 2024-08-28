/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:08:02 by marvin            #+#    #+#             */
/*   Updated: 2024/08/07 16:11:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include <pthread.h>
# include <string.h>

# define SCREEN_WIDTH 1600
# define SCREEN_HEIGHT 1200
# define MAX_OBJECTS 100

typedef struct s_cube	t_cube;

typedef struct s_tri_index
{
	int	m;
	int	j;
	int	k;
	int	l;
}	t_tri_index;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_data;

typedef struct s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	z;
	int	q;
	int	space;
	int	mouse_x;
	int	mouse_y;
	int	old_x;
}		t_key;

typedef struct s_raycasting
{
    double    sprite_x;
    double    sprite_y;
    double    inv_det;
    double    transform_x;
    double    transform_y;
    int        sprite_screen_x;
    int        sprite_height;
    int        draw_start_y;
    int        draw_end_y;
    int        sprite_width;
    int        draw_start_x;
    int        draw_end_x;
    int        stripe;
    int        x;
    int        y;
    unsigned int        color;
    int        tex_x;
    int        tex_y;
    int        d;
    double    wallx;
    t_data    *temp;
}        t_raycasting;

typedef struct s_enm
{
	pthread_t		threads;
	int				nbr;
	int				status;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			pos_player_x;
	double			pos_player_y;
	t_cube *cube;
}		t_enm;

typedef struct s_obj
{
	int		distance;
	int		map_x;
	int		map_y;
	char	type;
	t_data	*texture;
}		t_obj;


typedef struct s_cube
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		width;
	int		length;
	t_data	*img;
	t_key	*key;
	char	*error;
	int		cn;
	int		cs;
	int		ce;
	int		cw;
	int		cc;
	int		cf;
	char	*n;
	char	*s;
	char	*e;
	char	*w;
	int		f;
	int		c;
	char	*doors_assets[4];
	int		*assets_cd[4];
	t_data	assets[4];
	t_data	doors[4];
	double	pos_x;
	double	dir_x;
	double	plane_x;
	double	pos_y;
	double	dir_y;
	double	plane_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		drawstart;
	int		drawend;
	int		size_mini;
	int		act_doors_state;
	int		nb_ennemy;
	t_enm	**ennemies;
	t_data	assets_ennemies[1];
	t_obj	*rayc_obj;
}	t_cube;

typedef struct s_test
{
	char	**map;
	char	dir_temp;
	int		cord[2];
	int		cord_bis[2];
	int		erreur;
}	t_test;

typedef struct s_en
{
	char	**map;
	int		end_y;
	int		end_x;
	char	path[1000];
	int		erreur;
}	t_en;

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
int		ft_strlen(const char *s);

void	taille(t_cube *cube, int fd);
void	setmap(t_cube *cube, int fd);
int		check_map_format(char *s, char **av);
void	free_tab(char **tab);

int		the_end(t_cube *cube);

void	raycasting(t_cube *cube);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		get_pixel_color(t_data *texture, int x, int y);
void	raycasting_draw(t_cube *cube);
void	draw_background(t_cube *cube, int x);
t_data	*raycasting_dirwall(t_cube *cube);
void	raycasting_init1(t_cube *cube, int x);
void	raycasting_sidedist(t_cube *cube);

void	minimap(t_cube *cube);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	print_tab(char **s);

int		move(t_cube *cube);
void	rotate(t_cube *cube, int dir, double rotspd);

int		handle_key(int key, t_cube *cube);
int		handle_key2(int key, t_cube *cube);
void	init_key(t_cube *cube);
int		mouse(int x, int y, t_cube *cube);

void	divide_dir(char *dir, char *temp2, t_cube *cube);
int		rgb_to_hex(char **temp2, t_cube *cube);
void	parth_color(t_tri_index *ind, int i, char **temp, char **temp2);
void	recup_texture(t_cube *cube, char **temp, char *dir, t_tri_index	*dex);
void	recup_color(t_cube *cube, char **temp, char *dir, t_tri_index	*dex);

void	recup_map(t_cube *cube, int i, char **temp);
void	parth_map_nsew(t_cube *cube, char **temp, t_tri_index	*dex);
void	parth_map(t_cube *cube, char **temp);
void	setmap(t_cube *cube, int fd);
int		check_map_format(char *s, char **av);

int		find_player(t_test *test);
int		find_player2(t_test *test);
void	tester_map(t_test *test, int player_x, int player_y);
int		verif_map(t_cube *cube);
void	parth_map2(t_cube *cube, int i, char **temp);

int		verif_all(t_cube *cube);
void	verif_all2(t_cube *cube);
void	set_val(t_tri_index	*tri, char **tab);
void	assign_dir(char dir, t_cube *cube);
void	init_all(t_cube *cube);

char	*space(t_tri_index	*tri);
void	sdup(t_tri_index	*tri, char **temp, char **tab);
char	**expende_tab(char **tab);
char	**ft_strdup2(char **s);
char	***ft_strdup3(char ***s);
void	taille(t_cube *cube, int fd);
void	divide_dir2(char *dir, char **temp2, t_cube *cube);
int		the_end_error(t_cube *cube);

int		ft_atoi(const char *str);

void	raycasting_doors(t_cube *cube);
void	open_doors(t_cube *cube);
void	parth_map_nsew2(t_cube *cube, char **temp, t_tri_index	*dex);
int		find_ennemie(t_test *test);
void	init_ennemies(t_cube *cube);
void	tri_objects(t_obj *objects, int size);


void	make_move_en(t_cube *cube, int dir, double moveSpeed, int nb);
void	rotate_en(t_cube *cube, int dir, double rotspd, int nb);
void	mouv_en(t_cube *cube);

int		is_enemy_there(t_cube *cube, int x, int y);
#endif