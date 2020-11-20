/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:26:14 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/20 23:54:32 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "minirt.h"



void	parcer_checker(t_elements *elements)
{
	printf("R %d, %d", elements->resolution->w, elements->resolution->h);
}

int main(int argc, char *argv[])
{
	// void *mlx;

	// mlx = mlx_init();
	t_elements *elements;

	if (argc != 2)
	{
		errors_handler(4);
		return (-1);
	}
	if (!(elements = parser(argv[1])))
		return (-1);
	parcer_checker(elements);
	return (0);
}
