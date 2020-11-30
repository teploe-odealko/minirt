/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 14:09:52 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/30 14:12:46 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				is_end(char	*s)
{
	while (*s && *s == ' ')
		s++;
	return (*s == '\0' ? 1 : 0);
}

static double	moving_atof_helper(char **str, double res)
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

float			moving_atof(char **str)
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
	res = moving_atof_helper(str, res);
	return (sign * res);
}

int				moving_atoi(char **str)
{
	int		sign;
	int		res;

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
	return (sign * res);
}
