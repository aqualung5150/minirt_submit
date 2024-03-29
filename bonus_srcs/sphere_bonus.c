/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:19:33 by seungjoon         #+#    #+#             */
/*   Updated: 2023/01/17 13:53:10 by seungjoon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_sphere	*sphere(t_vec origin, double radius, t_color albedo)
{
	t_sphere	*new;

	if (vec_range(&albedo, 0.0, 1.0))
		return (NULL);
	new = (t_sphere *)malloc(sizeof(t_sphere));
	if (new == NULL)
		return (NULL);
	new->o = origin;
	new->r = radius;
	new->albedo = albedo;
	return (new);
}

static int	sphere_root(t_ray *ray, t_sphere *sp, t_hit_record *rec, \
		double *root)
{
	t_vec	oc;
	double	half_b;
	double	c;
	double	discriminant;
	double	sqrtd;

	oc = v_sub(ray->o, sp->o);
	half_b = dot(ray->d, oc);
	c = len_pow(oc) - (sp->r * sp->r);
	discriminant = (half_b * half_b) - c;
	if (discriminant < 0)
		return (0);
	sqrtd = sqrt(discriminant);
	*root = -half_b - sqrtd;
	if (*root < rec->t_min || *root > rec->t_max)
	{
		*root = -half_b + sqrtd;
		if (*root < rec->t_min || *root > rec->t_max)
			return (0);
	}
	return (1);
}

int	hit_sphere(t_ray *ray, t_sphere *sp, t_hit_record *rec)
{
	double	root;

	if (sphere_root(ray, sp, rec, &root))
	{
		rec->t = root;
		rec->t_max = rec->t;
		rec->p = ray_at(ray, root);
		rec->n = v_div(v_sub(rec->p, sp->o), sp->r);
		rec->albedo = sp->albedo;
		return (1);
	}
	return (0);
}
