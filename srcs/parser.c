/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:44:50 by bashleig          #+#    #+#             */
/*   Updated: 2020/12/01 22:12:42 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	else if (line[0] == 'c' && line[1] == ' ')
		return (camera_parser(line+1, elements));
	else if (line[0] == 'l' && line[1] == ' ')
		return (light_parser(line+1, elements));
	else if (line[0] == 's' && line[1] == 'p')
		return (sphere_parser(line+2, elements));
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
	elements->ambient->is_already_exist = 0;
	elements->resolution = malloc(sizeof(t_resolution));
	elements->resolution->is_already_exist = 0;
	elements->backgound_color.r = 0;
	elements->backgound_color.g = 0;
	elements->backgound_color.b = 0;
	elements->camera_list = NULL;
	elements->light_list = NULL;
	elements->plane_list = NULL;
	elements->sphere_list = NULL;
	elements->square_list = NULL;
	elements->cylinder_list = NULL;
	elements->trinangle_list = NULL;
	if (!elements->ambient || !elements->resolution)
		return (NULL);
	return (elements);
}

/*
returns t_elements pointer with parsed info, if
everything is ok, and NULL otherwise
*/
// BUG last row in the file dosent handle
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
