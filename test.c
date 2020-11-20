/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:15:20 by bashleig          #+#    #+#             */
/*   Updated: 2020/11/20 20:17:04 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "math.h"
#include "libft/libft.h"

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

int main()
{
	float f;

	char *s = "0.12345678912";
	f = ft_moving_atof(&s);
	printf("%.12f\n", f);
	printf("%.12f\n", 0.12345678912);
}