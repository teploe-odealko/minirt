/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:44:52 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/20 13:49:55 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef 		struct	s_coords
{
	float		x;
	float		y;
	float		z;
}				t_coords;

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
	int		w;
	int		h;
}				t_resolution;

typedef struct	s_ambient
{
	float	ratio;
	t_color	*color;
}				t_ambient;

typedef struct	s_camera
{
	t_vector3	*orient;
	t_coords	*coords;
	int			FOV;
}				t_camera;

typedef struct	s_light
{
	t_coords	*coords;
	float		bright;
	t_color		*color;
}				t_light;

typedef struct	s_sphere
{
	t_coords	*center;
	float		diameter;
	t_color		*color;
}				t_sphere;

typedef struct	s_plane
{
	t_vector3	*norm;
	t_coords	*coords;
	t_color		*color;
}				t_plane;

typedef struct	s_cylinder
{
	t_vector3	*norm;
	t_coords	*coords;
	t_color		*color;
	float		diameter;
	float		height;
}				t_cylinder;

typedef struct	s_trinangle
{
	t_coords	*p1;
	t_coords	*p2;
	t_coords	*p3;
	t_color		*color;
}				t_trinangle;

#endif