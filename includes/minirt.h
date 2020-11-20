/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:32:20 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/20 21:02:43 by bashleig         ###   ########.fr       */
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


void				*errors_handler(int errcode);

typedef struct		s_elements
{
	t_resolution*	resolution;
	t_ambient*		ambient;
	t_list*			camera_list;
	t_list*			light_list;
	t_list*			plane_list;
	t_list*			sphere_list;
	t_list*			square_list;
	t_list*			cylinder_list;
	t_list*			trinangle_list;
}					t_elements;

t_elements			*parser(char *filesafdname);

#endif
