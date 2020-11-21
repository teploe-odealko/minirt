/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_elements_parser.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:36:56 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/21 14:51:28 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

