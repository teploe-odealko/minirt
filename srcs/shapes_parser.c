/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:41:47 by bashleig          #+#    #+#             */
/*   Updated: 2020/12/01 22:14:58 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere		*sphere_parser(char *line, t_elements *elements)
{
	extern int	merrno;
	t_list		*new_node;
	t_sphere	*new_shape;

	if (!(new_shape = (t_sphere*)malloc(sizeof(t_sphere))))
	{
		merrno = 2;
		return (NULL);
	}
	if ((merrno = parse_coords(&line, &new_shape->center)) != 0)
		return (NULL);
	new_shape->diameter = moving_atof(&line);
	if (new_shape->diameter < 0 && (merrno = 15))
		return (NULL);
	if ((merrno = parse_rgb(&line, &new_shape->color)) != 0)
		return (NULL);
	if (!is_end(line) && (merrno = 16))
		return (NULL);
	if (!(new_node = ft_lstnew(new_shape)))
	{
		merrno = 2;
		return (NULL);
	}
	ft_lstadd_back(&(elements->sphere_list), new_node);
	return (new_shape);
}
