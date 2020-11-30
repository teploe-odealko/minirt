/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:28:41 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/30 16:51:49 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static int		numlen(long long nb)
// {
// 	int	len;

// 	len = 0;
// 	if (nb)
// 		return (1);
// 	while (nb > 0)
// 	{
// 		nb /= 10;
// 		len++;
// 	}
// 	return (len);
// }


/*
returns:
- 0 if everything is ok, 
- 5 if some parsing errors,
- 7 if rgb invalid
*/
int			parse_rgb(char **line, t_color *color)
{
	while(**line == ' ')
		(*line)++;	
	if (!ft_isdigit(**line))
		return (5);
	color->r = moving_atoi(line);
	if (**line == ',')
		(*line)++;
	if (!ft_isdigit(**line))
		return (5);
	color->g = moving_atoi(line);
	if (**line == ',')
		(*line)++;
	if (!ft_isdigit(**line))
		return (5);
	color->b = moving_atoi(line);
	if (is_digit_in_bounds(color->r, 0, 255)
	&& is_digit_in_bounds(color->g, 0, 255)
	&& is_digit_in_bounds(color->b, 0, 255))
		return (0);
	return (7);
}

int			parse_coords(char **line, t_coords *coords)
{
	while(**line == ' ')
		(*line)++;
	if (!ft_isdigit(**line) && (**line != '-' && !ft_isdigit(line[0][1])))
		return (8);
	coords->x = moving_atof(line);
	if (**line == ',')
		(*line)++;
	if (!ft_isdigit(**line) && (**line != '-' && !ft_isdigit(line[0][1])))
		return (8);
	coords->y = moving_atof(line);
	if (**line == ',')
		(*line)++;
	if (!ft_isdigit(**line) && (**line != '-' && !ft_isdigit(line[0][1])))
		return (8);
	coords->z = moving_atof(line);
	return (0);
}

int			parse_norm_vector(char **line, t_vector3 *vector3)
{
	while(**line == ' ')
		(*line)++;
	if (!ft_isdigit(**line))
		return (5);
	vector3->x = moving_atof(line);
	if (**line == ',')
		(*line)++;
	if (!ft_isdigit(**line))
		return (5);
	vector3->y = moving_atof(line);
	if (**line == ',')
		(*line)++;
	if (!ft_isdigit(**line))
		return (5);
	vector3->z = moving_atof(line);
	if (is_digit_in_bounds(vector3->x, 0, 1)
	&& is_digit_in_bounds(vector3->y, 0, 1)
	&& is_digit_in_bounds(vector3->z, 0, 1))
		return (0);
	return (9);
}