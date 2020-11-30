/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:26:14 by bashleig          #+#    #+#             */
/*   Updated: 2020/12/01 02:13:29 by bashleig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minirt.h"


void	camera_printer(void* camera_void)
{
	t_camera* camera = (t_camera*)camera_void;
	printf("camera coords: %f, %f, %f\n",
	camera->coords.x,
	camera->coords.y,
	camera->coords.z);
	printf("camera vector: %f, %f, %f\n",
	camera->direction.x,
	camera->direction.y,
	camera->direction.z);
	printf("camera FOV: %d\n", camera->FOV);
}

void	sphere_printer(void* my_struct)
{
	t_sphere* casted = (t_sphere*)my_struct;
	printf("sphere center: %f, %f, %f\n",
	casted->center.x,
	casted->center.y,
	casted->center.z);
	printf("sphere diam: %f\n", casted->diameter);
	printf("sphere rgb: %d, %d, %d\n",
	casted->color.r,
	casted->color.g,
	casted->color.b);
}

void	light_printer(void* my_struct)
{
	t_light* casted = (t_light*)my_struct;
	printf("light coords: %f, %f, %f\n",
	casted->coords.x,
	casted->coords.y,
	casted->coords.z);
	printf("light brightness: %f\n", casted->bright);
	printf("light rgb: %d, %d, %d\n",
	casted->color.r,
	casted->color.g,
	casted->color.b);
}

void	parcer_printer(t_elements *elements)
{
	printf("R %d, %d\n", elements->resolution->w, elements->resolution->h);
	printf("A %f, %d,%d,%d\n", elements->ambient->ratio,
	elements->ambient->color.r,
	elements->ambient->color.g,
	elements->ambient->color.b);
	ft_lstiter(elements->camera_list, &camera_printer);
	ft_lstiter(elements->light_list, &light_printer);
	ft_lstiter(elements->sphere_list, &sphere_printer);
}


// corss and ESC - exit
// if res >, then current res
// camera switch by button press
// use images of minilibx


//danger !!! could returns NULL
t_coords	*canvas_to_viewport(float x, float y, t_elements *elements)
{
	t_coords *d;

	if(!(d = malloc(sizeof(t_coords))))
		return (d);
	d->x = (x - elements->resolution->w / 2) / elements->resolution->w;
	d->y = (y - elements->resolution->h / 2) / elements->resolution->h;
	d->z = 1;
    return (d);
}

float		scalar_mul(t_vector3 *v1, t_vector3 *v2)
{
	return (
	v1->x * v2->x +
	v1->y * v2->y +
	v1->z * v2->z);
}

typedef struct	s_sq_eq_sol
{
	float	d;
	float	x1;
	float	x2;
}				t_sq_eq_sol;


//malloc
t_sq_eq_sol *square_equasion(float a, float b, float c)
{
	t_sq_eq_sol *solution;

	if (!(solution = malloc(sizeof(t_sq_eq_sol))))
		return (NULL);
	solution->d = b * b - 4 * a * c;
	if (solution->d >= 0)
	{
		solution->x1 = - b + sqrt(solution->d) / (2 * a);
		solution->x2 = - b - sqrt(solution->d) / (2 * a);
	}
	return (solution);
}

void		*intersect_sphere(t_sphere *sphere, t_vector3 *d, t_vector3 *oc)
{
	float		a;
	float		b;
	float		c;
	t_sq_eq_sol	*solution;

	a = scalar_mul(d, d);
	b = 2 * scalar_mul(oc, d);
	c = scalar_mul(oc, oc) - pow(sphere->diameter / 2, 2);
	solution = square_equasion(a, b, c);
	return (solution);
}


//danger !!! could returns NULL
t_color		*trace_ray(t_coords *camera_coords, t_coords *v, int min, int max, t_elements *elements)
{
	t_list		*sp_list;
	// t_sphere	*closest_sphere;
	t_vector3	*oc;
	t_sq_eq_sol	*solution;

	sp_list = elements->sphere_list;
	while (sp_list)
	{
		if (!(oc = malloc(sizeof(t_vector3))))
			return (NULL);
		oc->x = camera_coords->x - ((t_sphere*)(sp_list->content))->center.x;
		oc->y = camera_coords->y - ((t_sphere*)(sp_list->content))->center.y;
		oc->z = camera_coords->z - ((t_sphere*)(sp_list->content))->center.z;
		v->x -= camera_coords->x;
		v->y -= camera_coords->y;
		v->z -= camera_coords->z;
		if (!(solution = intersect_sphere(sp_list->content, (t_vector3*)v, oc)))
			return (NULL);
		if (solution->d >= 0)
		{
			if ((solution->x1 >= min && solution->x1 <= max)
			|| (solution->x2 >= min && solution->x2 <= max))
				return (&((t_sphere*)(sp_list->content))->color);
		}
		sp_list = sp_list->next;
	}
	return (&elements->backgound_color);
	// sphere = elements->sphere_list->content;
}

void		*display(t_elements *elements)
{
	t_mlx		*mlx;
	t_color		*color;
	t_coords	*v;

	if (!(mlx = malloc(sizeof(t_mlx))))
		return (NULL);
	mlx->x = 0;

	mlx->mlx = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx, elements->resolution->w,
	elements->resolution->h, "Mandatory part");
	mlx->img_ptr = mlx_new_image(mlx->mlx,
	elements->resolution->w, elements->resolution->h);
	mlx->img_data = (int*)mlx_get_data_addr(mlx->img_ptr,
	&mlx->bpp, &mlx->size_line, &mlx->endian);

	while(mlx->x < elements->resolution->w)
	{
		mlx->y = 0;
		while (mlx->y < elements->resolution->h)
		{
			// printf("x = %d y = %d\n", mlx->x, mlx->y);
			if (!(v = canvas_to_viewport(mlx->x, mlx->y, elements)))
				return (NULL);
			color = trace_ray(&((t_camera*)(elements->camera_list->content))->coords, v, 1, 1000000, elements);
			free(v);
			mlx->img_data[mlx->y * elements->resolution->w + mlx->x] =
			color->r * 65536 +
			color->g * 256 +
			color->b;
			mlx->y++;
		}
		mlx->x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_loop(mlx->mlx);
	return (NULL);
}


// TODO : add --save param handler
int		main(int argc, char *argv[])
{
	t_elements *elements;

	elements = NULL;
	if (argc != 2)
	{
		errors_handler(4, elements);
		return (-1);
	}
	if (!(elements = parser(argv[1])))
		return (-1);
	// parcer_printer(elements);
	display(elements);
	return (0);
}
