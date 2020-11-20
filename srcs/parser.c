/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:44:50 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/21 00:29:53 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		numlen(long long nb)
{
	int	len;

	len = 0;
	if (nb)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

double	ft_moving_atof_helper(char **str, double res)
{
	double	fraction;

	fraction = 0.1;
	if (*(*str) == '.')
	{
		(*str)++;
		while (*(*str) >= '0' && *(*str) <= '9')
		{
			res = res + (*(*str) - '0') * fraction;
			fraction *= 0.1;
			(*str)++;
		}
	}
	return (res);
}

float	ft_moving_atof(char **str)
{
	int		sign;
	double	res;

	sign = 1;
	res = 0;
	while (*(*str) == ' ' || *(*str) == '\t' || *(*str) == '\n' ||
		*(*str) == '\r' || *(*str) == '\v' || *(*str) == '\f')
		(*str)++;
	if (*(*str) == '-')
		sign = -1;
	if (*(*str) == '-' || *(*str) == '+')
		(*str)++;
	while (*(*str) >= '0' && *(*str) <= '9')
	{
		res = res * 10 + *(*str) - '0';
		(*str)++;
	}
	res = ft_moving_atof_helper(str, res);
	return (sign * res);
}

// int		ambient_parser(char *line)
// {
// 	t_resolution *ambient;

// 	ambient = malloc(sizeof(t_resolution));
// 	if (!ambient)
// 		errors_handler(2);
// 	ambient->w = ft_moving_atoi(line);
// 	ambient->h = ft_moving_atoi(line);
// 	if (ambient->h > 0 && ambient->w > 0)
// 		g_ambient = ambient;
// 	else
// 	{
// 		free(ambient);
// 		errors_handler(3);
// 	}
// }

/*
- returns t_resolution pointer, if
everything is ok, and NULL otherwise
- sets errno
*/
int				is_end(char	*s)
{
	while (*s && *s == ' ')
		s++;
	return (*s == '\0' ? 1 : 0);
}

t_resolution	*resolution_parser(char *line, t_elements *elements)
{
	extern int		merrno;

	elements->resolution->w = (int)ft_moving_atof(&line);
	elements->resolution->h = (int)ft_moving_atof(&line);
	if (elements->resolution->h <= 0 
	|| elements->resolution->w <= 0
	|| !is_end(line))
	{
		merrno = 3;
		return (NULL);
	}
	return (elements->resolution);
}

void		*switcher(char *line, t_elements *elements)
{
	extern int	merrno;

	if (line[0] == 'R' && line[1] == ' ')
		return (resolution_parser(line+1, elements));
	else
	{
		merrno = 5;
		return (NULL);
	}
	// else if (line[0] == 'A' && line[1] == ' ')
	// 	ambient_parser(line+1);
}

t_elements	*elements_creator(void)
{
	t_elements *elements;

	if (!(elements = malloc(sizeof(t_elements))))
		return (NULL);
	elements->ambient = malloc(sizeof(t_ambient));
	elements->resolution = malloc(sizeof(t_resolution));
	elements->camera_list = malloc(sizeof(t_list));
	elements->cylinder_list = malloc(sizeof(t_list));
	elements->light_list = malloc(sizeof(t_list));
	elements->plane_list = malloc(sizeof(t_list));
	elements->sphere_list = malloc(sizeof(t_list));
	elements->square_list = malloc(sizeof(t_list));
	elements->trinangle_list = malloc(sizeof(t_list));
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

void		free_struct(void *my_struct)
{
	free(my_struct);
}


//seg fault in destructor!!!!
void		destructor(t_elements *elements)
{
	free(elements->ambient);
	elements->ambient = NULL;
	free(elements->resolution);
	elements->resolution = NULL;
	ft_lstclear(&(elements->camera_list), &free_struct);
	ft_lstclear(&(elements->cylinder_list), &free_struct);
	ft_lstclear(&(elements->light_list), &free_struct);
	ft_lstclear(&(elements->plane_list), &free_struct);
	ft_lstclear(&(elements->sphere_list), &free_struct);
	ft_lstclear(&(elements->square_list), &free_struct);
	ft_lstclear(&(elements->trinangle_list), &free_struct);
	free(elements);
}

t_elements	*parser(char *filename)
{
	int			fd;
	char		*line;
	t_elements	*elements;
	extern int	merrno;

	merrno = 0;
	if (!(elements = elements_creator()))
		return (errors_handler(2));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (errors_handler(0));
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
			return (errors_handler(1));
		}
		if (!(switcher(line, elements)))
		{
			free(line);
			destructor(elements);
			return (errors_handler(merrno));
		}
		free(line);
	}
	return (elements);
}
