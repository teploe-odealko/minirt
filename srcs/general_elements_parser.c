/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_elements_parser.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:36:56 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/30 16:44:19 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_resolution	*resolution_parser(char *line, t_elements *elements)
{
	extern int		merrno;

	elements->resolution->w = (int)moving_atoi(&line);
	elements->resolution->h = (int)moving_atoi(&line);
	if (elements->resolution->is_already_exist == 0
	&& is_digit_in_bounds(elements->resolution->h, 1, 2880)
	&& is_digit_in_bounds(elements->resolution->w, 1, 5120)
	&& is_end(line))
	{
		elements->resolution->is_already_exist = 1;
		return (elements->resolution);
	}
	merrno = 3;
	return (NULL);
}

t_ambient		*ambient_parser(char *line, t_elements *elements)
{
	extern int	merrno;

	elements->ambient->ratio = moving_atof(&line);
	if (!is_digit_in_bounds(elements->ambient->ratio, 0, 1)
	|| elements->ambient->is_already_exist == 1)
	{
		merrno = 6;
		return (NULL);
	}
	if ((merrno = parse_rgb(&line, &(elements->ambient)->color)) != 0)
		return (NULL);
	if (!is_end(line))
	{
		merrno = 12;
		return (NULL);
	}
	elements->ambient->is_already_exist = 1;
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
	if ((merrno = parse_coords(&line, &new_camera->coords)) != 0)
		return (NULL);
	if ((merrno = parse_norm_vector(&line, &new_camera->direction)) != 0)
		return (NULL);
	new_camera->FOV = moving_atoi(&line);
	if (!is_digit_in_bounds(new_camera->FOV, 0, 180) && (merrno = 10))
		return (NULL);
	if (!is_end(line) && (merrno = 11))
		return (NULL);
	if (!(new_node = ft_lstnew(new_camera)))
	{
		merrno = 2;
		return (NULL);
	}
	ft_lstadd_back(&(elements->camera_list), new_node);
	return (new_camera);
}

t_light			*light_parser(char *line, t_elements *elements)
{
	extern int	merrno;
	t_list		*new_node;
	t_light		*new_light;

	if (!(new_light = malloc(sizeof(t_light))))
	{
		merrno = 2;
		return (NULL);
	}
	if ((merrno = parse_coords(&line, &new_light->coords)) != 0)
		return (NULL);
	new_light->bright = moving_atof(&line);
	if (!is_digit_in_bounds(new_light->bright, 0, 1) && (merrno = 13))
		return (NULL);
	if ((merrno = parse_rgb(&line, &new_light->color)) != 0)
		return (NULL);
	if (!is_end(line) && (merrno = 14))
		return (NULL);
	if (!(new_node = ft_lstnew(new_light)))
	{
		merrno = 2;
		return (NULL);
	}
	ft_lstadd_back(&(elements->light_list), new_node);
	return (new_light);
}
