/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:15:06 by bashleig          #+#    #+#             */
/*   Updated: 2020/12/01 19:10:18 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float		scalar_mul(t_vector3 *v1, t_vector3 *v2)
{
	return (
	v1->x * v2->x +
	v1->y * v2->y +
	v1->z * v2->z);
}

t_sq_eq_sol square_equasion(float a, float b, float c)
{
	t_sq_eq_sol solution;

	solution.d = b * b - 4 * a * c;
	if (solution.d >= 0)
	{
		solution.x1 = - b + sqrt(solution.d) / (2 * a);
		solution.x2 = - b - sqrt(solution.d) / (2 * a);
	}
	return (solution);
}

int			minint(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

float		vect_len(t_vector3 v1)
{
	return (sqrt(scalar_mul(&v1, &v1)));
}
