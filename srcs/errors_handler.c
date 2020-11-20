/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:04:40 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/20 23:02:30 by bashleig         ###   ########.fr       */
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
*/ 

/* always returns NULL */

void	*errors_handler(int errcode)
{
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
	return (NULL);
}
