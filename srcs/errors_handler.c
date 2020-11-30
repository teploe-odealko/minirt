/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:04:40 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/30 16:57:55 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
-----Error code description-----
0 - errno
1 - parsing error
2 - memory allocation error
3 - resolution parse error
4 - wrong number of arguments
5 - parsing error
6 - invalid ambient light
7 - invalid rgb
8 - invalid coords
9 - invalid vector
10 - invalid camera FOV
11 - camera parsing error
12 - ambirnt parsing error
13 - invalid light brightness
14 -  light parsing error
15 -  invalid sphere diameter
16 - sphere parsing error
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
	if (elements->camera_list)
		ft_lstclear(&(elements->camera_list), &free_struct);
	if (elements->cylinder_list)
		ft_lstclear(&(elements->cylinder_list), &free_struct);
	if (elements->light_list)
		ft_lstclear(&(elements->light_list), &free_struct);
	if (elements->plane_list)
		ft_lstclear(&(elements->plane_list), &free_struct);
	if (elements->sphere_list)
		ft_lstclear(&(elements->sphere_list), &free_struct);
	if (elements->square_list)
		ft_lstclear(&(elements->square_list), &free_struct);
	if (elements->trinangle_list)
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
		ft_putstr_fd("Error\nrgb invalid\n", 2);
	else if (errcode == 8)
		ft_putstr_fd("Error\ncoords invalid\n", 2);
	else if (errcode == 9)
		ft_putstr_fd("Error\ninvalid vector\n", 2);
	else if (errcode == 10)
		ft_putstr_fd("Error\ninvalid camera FOVr\n", 2);
	else if (errcode == 11)
		ft_putstr_fd("Error\ncamera parsing error\n", 2);
	else if (errcode == 12)
		ft_putstr_fd("Error\nambirnt parsing error\n", 2);
	else if (errcode == 13)
		ft_putstr_fd("Error\ninvalid light brightness\n", 2);
	else if (errcode == 14)
		ft_putstr_fd("Error\nlight parsing error\n", 2);
	else if (errcode == 15)
		ft_putstr_fd("Error\ninvalid sphere diameter\n", 2);
	else if (errcode == 16)
		ft_putstr_fd("Error\nsphere parsing error\n", 2);

	else if (errcode == 13)
		ft_putstr_fd("Error\ninvalid light brightness\n", 2);
	else if (errcode == 13)
		ft_putstr_fd("Error\ninvalid light brightness\n", 2);
	else if (errcode == 13)
		ft_putstr_fd("Error\ninvalid light brightness\n", 2);
	else if (errcode == 13)
		ft_putstr_fd("Error\ninvalid light brightness\n", 2);
	else if (errcode == 13)
		ft_putstr_fd("Error\ninvalid light brightness\n", 2);
	else if (errcode == 13)
		ft_putstr_fd("Error\ninvalid light brightness\n", 2);

	return (NULL);
}
