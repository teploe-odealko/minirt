/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:44:50 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/21 14:30:53 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				is_end(char	*s)
{
	while (*s && *s == ' ')
		s++;
	return (*s == '\0' ? 1 : 0);
}

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

// int			is_digit_in_bounds(int d, int bound_min, int bound_max)
// {
// 	if (d >= bound_min && d <= bound_max)
// 		return (1);
// 	return (0);
// }

int			is_digit_in_bounds(float d, float bound_min, float bound_max)
{
	if (d >= bound_min && d <= bound_max)
		return (1);
	return (0);
}

/*
returns 0 if everything is ok, 
5 if some parsing errors,
7 if rgb invalid
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

/*
- returns t_resolution pointer, if
everything is ok, and NULL otherwise
- sets errno
*/

void		*switcher(char *line, t_elements *elements)
{
	extern int	merrno;

	if (line[0] == 'R' && line[1] == ' ')
		return (resolution_parser(line+1, elements));
	else if (line[0] == 'A' && line[1] == ' ')
		return (ambient_parser(line+1, elements));
	else
	{
		merrno = 5;
		return (NULL);
	}
}

t_elements	*elements_creator(void)
{
	t_elements *elements;

	if (!(elements = malloc(sizeof(t_elements))))
		return (NULL);
	elements->ambient = malloc(sizeof(t_ambient));
	elements->resolution = malloc(sizeof(t_resolution));
	elements->camera_list = ft_lstnew(NULL);
	elements->cylinder_list = ft_lstnew(NULL);
	elements->light_list = ft_lstnew(NULL);
	elements->plane_list = ft_lstnew(NULL);
	elements->sphere_list = ft_lstnew(NULL);
	elements->square_list = ft_lstnew(NULL);
	elements->trinangle_list = ft_lstnew(NULL);
	if (!elements->ambient || !elements->resolution
	|| !elements->camera_list || !elements->cylinder_list
	|| !elements->light_list || !elements->plane_list
	|| !elements->sphere_list || !elements->square_list
	|| !elements->trinangle_list)
		return (NULL);
	return (elements);
}

/*
returns t_elements pointer with parsed info, if
everything is ok, and NULL otherwise
*/



t_elements	*parser(char *filename)
{
	int			fd;
	char		*line;
	t_elements	*elements;
	extern int	merrno;

	merrno = 0;
	if (!(elements = elements_creator()))
		return (errors_handler(2, elements));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (errors_handler(0, elements));
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (line == NULL || !line[0] || !line[1])
		{
			free(line);
			return (errors_handler(1, elements));
		}
		if (!(switcher(line, elements)))
		{
			free(line);
			return (errors_handler(merrno, elements));
		}
		free(line);
	}
	return (elements);
}
