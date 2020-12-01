/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bashleig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:26:14 by bashleig          #+#    #+#             */
/*   Updated: 2020/12/01 19:11:29 by bashleig         ###   ########.fr       */
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
t_vector3	canvas_to_viewport(float x, float y, t_elements *elements)
{
	t_vector3 d;

	d.x = (x - elements->resolution->w / 2) /
		minint(elements->resolution->w, elements->resolution->h);
	d.y = (y - elements->resolution->h / 2) /
		minint(elements->resolution->w, elements->resolution->h);
	d.z = 1;
    return (d);
}



t_vector3	subtract_vectors(t_vector3 *v1, t_vector3 *v2)
{
	t_vector3 res;

	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	res.z = v1->z - v2->z;
	return (res);
}

t_vector3	add_vectors(t_vector3 *v1, t_vector3 *v2)
{
	t_vector3 res;

	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	res.z = v1->z + v2->z;
	return (res);
}

t_vector3	n_vector(float n, t_vector3 *v1)
{
	t_vector3 res;

	res.x = v1->x * n;
	res.y = v1->y * n;
	res.z = v1->z * n;
	return (res);
}

//malloc

t_sq_eq_sol	intersect_sphere(t_sphere *sphere, t_vector3 *v, t_vector3 *camera_coords)
{
	float		a;
	float		b;
	float		c;
	t_vector3	oc;
	t_sq_eq_sol	solution;

	oc = subtract_vectors((t_vector3*)camera_coords, (t_vector3*)&sphere->center);
	*v = subtract_vectors(v, (t_vector3*)camera_coords);
	a = scalar_mul((t_vector3*)v, (t_vector3*)v);
	b = 2 * scalar_mul(&oc, (t_vector3*)v);
	c = scalar_mul(&oc, &oc) - pow(sphere->diameter / 2, 2);
	solution = square_equasion(a, b, c);
	return (solution);
}


int			is_new_solution_better(t_sq_eq_sol *new_sol, t_sq_eq_sol *old_sol)
{
	int new_min;
	int old_min;

	new_min = MAX_INT;
	old_min = MAX_INT;
	if (new_sol->x1 < new_sol->x2 && new_sol->x1 > 1)
		new_min = new_sol->x1;
	else if (new_sol->x2 > 1)
		new_min = new_sol->x2;
	if (old_sol->x1 < old_sol->x2 && old_sol->x1 > 1)
		old_min = old_sol->x1;
	else if (old_sol->x2 > 1)
		old_min = old_sol->x2;
	if (new_min < old_min)
		return (1);
	return (0);
}

float		compute_lighting(t_elements *elements, t_vector3 p, t_vector3 n)
{
	float		i;
	float		n_dot_l;
	t_list		*node;
	t_vector3	l;

	node = elements->light_list;
	i = elements->ambient->ratio;
	while (node)
	{
		l = subtract_vectors(
			&((t_light*)(node->content))->coords,
			&p);
		if ((n_dot_l = scalar_mul(&n, &l)) > 0)
		{
			i += ((t_light*)(node->content))->bright * n_dot_l /
			(vect_len(n) * vect_len(l));
		}
		node = node->next;
	}
	return (i);
}

t_color		compute_color(t_elements *elements, t_vector3 *camera_coords,
	t_sphere* sphere, t_sq_eq_sol *solution, t_vector3 d)
{
	t_color		color;
	t_vector3	p;
	t_vector3	n;
	float		closest_t;
	float		light;

	if (solution->x1 < solution->x2 && solution->x1 > 1)
		closest_t = solution->x1;
	else
		closest_t = solution->x2;
	d = n_vector(closest_t, &d);
	p = add_vectors(camera_coords, &d);
	n = subtract_vectors(&p, &sphere->center);
	n.x /= sqrt(scalar_mul(&n, &n));
	n.y /= sqrt(scalar_mul(&n, &n));
	n.z /= sqrt(scalar_mul(&n, &n));
	light = compute_lighting(elements, p, n);
	color.r = (light * (float)sphere->color.r);
	color.g = (light * (float)sphere->color.r);
	color.b = (light * (float)sphere->color.r);
	return (color);
}
//danger !!! could returns NULL
t_color		trace_ray(t_vector3 *camera_coords, t_vector3 v, t_elements *elements)
{
	t_list		*sp_list;
	t_sphere	*closest_sphere;
	t_sq_eq_sol	solution;
	t_sq_eq_sol	closest_solution;

	closest_sphere = NULL;
	closest_solution.x1 = 0;
	closest_solution.x2 = 0;
	sp_list = elements->sphere_list;
	while (sp_list)
	{
		solution = intersect_sphere(sp_list->content, (t_vector3*)(&v), camera_coords);
		if (solution.d >= 0)
		{
			if (is_new_solution_better(&solution, &closest_solution))
			{
				closest_solution = solution;
				closest_sphere = ((t_sphere*)(sp_list->content));
			}
		}
		sp_list = sp_list->next;
	}
	if (closest_sphere)
		return (compute_color(elements, camera_coords, closest_sphere,
		&closest_solution, subtract_vectors(&v, (t_vector3*)camera_coords)));
	return (elements->backgound_color);
	// sphere = elements->sphere_list->content;
}

void		*mlx_setup(t_mlx *mlx, t_elements *elements)
{
	mlx->x = 0;
	if (!(mlx->mlx = mlx_init()))
		return (NULL);
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx, elements->resolution->w,
	elements->resolution->h, "Mandatory part")))
		return (NULL);
	if (!(mlx->img_ptr = mlx_new_image(mlx->mlx,
	elements->resolution->w, elements->resolution->h)))
		return (NULL);
	mlx->img_data = (int*)mlx_get_data_addr(mlx->img_ptr,
	&mlx->bpp, &mlx->size_line, &mlx->endian);
	return (mlx);
}

void		set_pixel_to_img(t_elements *elements, t_mlx *mlx, t_color *color)
{
	mlx->img_data[mlx->y * elements->resolution->w + mlx->x] =
		color->r * 65536 +
		color->g * 256 +
		color->b;
		mlx->y++;
}

void		*display(t_elements *elements)
{
	t_mlx		mlx;
	t_color		color;
	t_vector3	v;

	if (!(mlx_setup(&mlx, elements)))
		return (NULL);
	while(mlx.x < elements->resolution->w)
	{
		mlx.y = 0;
		while (mlx.y < elements->resolution->h)
		{
			v = canvas_to_viewport(mlx.x, mlx.y, elements);
			color = trace_ray(&((t_camera*)
			(elements->camera_list->content))->coords,
			v, elements);
			set_pixel_to_img(elements, &mlx, &color);
		}
		mlx.x++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win_ptr, mlx.img_ptr, 0, 0);
	mlx_loop(mlx.mlx);
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
	destructor(elements);
	return (0);
}
