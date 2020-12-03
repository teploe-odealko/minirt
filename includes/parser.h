/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:44:52 by bashleig          #+#    #+#             */
/*   Updated: 2020/12/01 18:47:28 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct	s_vector3
{
	float		x;
	float		y;
	float		z;
}				t_vector3;

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
}				t_color;

typedef struct	s_resolution
{
	int		is_already_exist;
	int		w;
	int		h;
}				t_resolution;

typedef struct	s_ambient
{
	int		is_already_exist;
	float	ratio;
	t_color	color;
}				t_ambient;

typedef struct	s_camera
{
	t_vector3	direction;
	t_vector3	coords;
	float		FOV;
}				t_camera;

typedef struct	s_light
{
	t_vector3	coords;
	float		bright;
	t_color		color;
}				t_light;

typedef struct	s_sphere
{
	char        type;
	t_color		color;
	t_vector3	center;
	float		diameter;
}				t_sphere;

typedef struct	s_plane
{
	char        type;
	t_color		color;
	t_vector3	norm;
	t_vector3	coords;
}				t_plane;

typedef struct	s_cylinder
{
	char        type;
	t_color		color;
	t_vector3	norm;
	t_vector3	coords;
	float		diameter;
	float		height;
}				t_cylinder;

typedef struct	s_trinangle
{
	t_color		color;
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	p3;
}				t_trinangle;
int				parse_rgb(char **line, t_color *color);
int				parse_coords(char **line, t_vector3 *coords);
int				parse_norm_vector(char **line, t_vector3 *vector3);
int				is_end(char	*s);
float			moving_atof(char **str);
int				moving_atoi(char **str);

#endif