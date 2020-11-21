/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_elements_parser.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:36:56 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/21 16:19:39 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// TODO: resolution & ambient могут быть в списке только один раз: добавить проверку на это
t_resolution	*resolution_parser(char *line, t_elements *elements)
{
	extern int		merrno;

	elements->resolution->w = (int)moving_atof(&line);
	elements->resolution->h = (int)moving_atof(&line);
	if (elements->resolution->h <= 0 
	|| elements->resolution->w <= 0
	|| !is_end(line))
	{
		merrno = 3;
		return (NULL);
	}
	return (elements->resolution);
}


t_ambient		*ambient_parser(char *line, t_elements *elements)
{
	extern int	merrno;

	elements->ambient->ratio = moving_atof(&line);
	if (!is_digit_in_bounds(elements->ambient->ratio, 0, 1))
	{
		merrno = 6;
		return (NULL);
	}
	if ((merrno = parse_rgb(&line, &(elements->ambient)->color)) != 0)
		return (NULL);
	return (elements->ambient);
}

t_camera		*camera_parser(char *line, t_elements *elements)
{
	extern int	merrno;
	t_list		*new_node;
	t_camera	*new_camera;

	if (!(new_camera = malloc(sizeof(t_camera))))
	{
		merrno = 2;
		return (NULL);
	}
	if ((merrno = parse_rgb(&line, &new_camera->coords)) != 0)
		return (NULL);
	new_node = ft_lstnew(new_camera);
	return (elements->ambient);
}

