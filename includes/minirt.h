/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:32:20 by bashleig          #+#    #+#             */
/*   Updated: 2020/12/01 01:52:35 by bashleig         ###   ########.fr       */
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
#include <mlx.h>




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


void				*errors_handler(int errcode, t_elements *elements);
t_elements			*parser(char *filesafdname);
t_resolution		*resolution_parser(char *line, t_elements *elements);
t_ambient			*ambient_parser(char *line, t_elements *elements);
t_camera			*camera_parser(char *line, t_elements *elements);
t_light				*light_parser(char *line, t_elements *elements);
t_sphere			*sphere_parser(char *line, t_elements *elements);


#endif
