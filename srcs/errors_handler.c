/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:04:40 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/21 14:06:00 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
-----Error code description-----
0 - errno
1 - parseing error
2 - memory allocation error
3 - resolution parse error
4 - wrong number of arguments
5 - parsing error
6 - invalid ambient light
7 - invalid rgb
*/ 
/* always returns NULL */



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

void	*errors_handler(int errcode, t_elements *elements)
{
	if (elements)
		destructor(elements);
	if (errcode == 0)
		perror("Error\n");
	else if (errcode == 1)
		ft_putstr_fd("Error\nParsing error\n", 2);
	else if (errcode == 2)
		ft_putstr_fd("Error\nMemory allocation error\n", 2);
	else if (errcode == 3)
		ft_putstr_fd("Error\nResolution parse error\n", 2);
	else if (errcode == 4)
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
	else if (errcode == 5)
		ft_putstr_fd("Error\nParsing error\n", 2);
	else if (errcode == 6)
		ft_putstr_fd("Error\ninvalid ambient light\n", 2);
	else if (errcode == 7)
		ft_putstr_fd("Error\nrgb light\n", 2);
	return (NULL);
}
