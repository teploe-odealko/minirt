/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:28:41 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/21 14:34:49 by bashleig         ###   ########.fr       */
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
