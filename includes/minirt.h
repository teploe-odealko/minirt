/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:32:20 by bashleig          #+#    #+#             */
/*   Updated: 2020/12/01 19:12:37 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include "parser.h"
# include <math.h>
#include "mlx.h"



#define MAX_INT 2147483647
int					merrno;
typedef struct		s_elements
{
	t_resolution*	resolution;
	t_ambient*		ambient;
	t_color			backgound_color;
	t_list*			camera_list;
	t_list*			light_list;
	t_list*			plane_list;
	t_list*			sphere_list;
	t_list*			square_list;
	t_list*			cylinder_list;
	t_list*			trinangle_list;
}					t_elements;

typedef struct		s_mlx
{
	void	*mlx;
	void	*win_ptr;
	void	*img_ptr;
	int		*img_data;
	int		x;
	int		y;
	int		bpp;
	int		size_line;
	int		endian;
}					t_mlx;

typedef struct	s_sq_eq_sol
{
	float	d;
	float	x1;
	float	x2;
}				t_sq_eq_sol;


void				*errors_handler(int errcode, t_elements *elements);
void				destructor(t_elements *elements);
t_elements			*parser(char *filesafdname);
t_resolution		*resolution_parser(char *line, t_elements *elements);
t_ambient			*ambient_parser(char *line, t_elements *elements);
t_camera			*camera_parser(char *line, t_elements *elements);
t_light				*light_parser(char *line, t_elements *elements);
t_sphere			*sphere_parser(char *line, t_elements *elements);
float				scalar_mul(t_vector3 *v1, t_vector3 *v2);
float				vect_len(t_vector3 v1);
t_sq_eq_sol 		square_equasion(float a, float b, float c);
int					minint(int a, int b);
#endif
