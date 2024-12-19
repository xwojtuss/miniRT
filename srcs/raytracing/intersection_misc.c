#include "mini_rt.h"

t_vector	get_inter(t_ray ray, double t)
{
	return (add_v(ray.origin, multiply_v(ray.direction, t)));
}

void	retrieve_t(double a, double b, double disc, double *t1, double *t2)
{
	double	temp;
	double	sqrt_disc;

	if (disc < 0)
	{
		*t1 = DBL_MAX;
		*t2 = DBL_MAX;
		return ;
	}
	sqrt_disc = sqrt(disc);
	*t1 = (-b - sqrt_disc) / (2.0 * a);
	*t2 = (-b + sqrt_disc) / (2.0 * a);
	if (*t1 > *t2)
	{
		temp = *t1;
		*t1 = *t2;
		*t2 = temp;
	}
}

double	is_intersect_cylinder_caps(t_ray ray, t_cylinder *cylinder,
		double *prev_t)
{
	t_vector cap_top, cap_bottom, p;
	double t_cap_top, t_cap_bottom;
	cap_bottom = cylinder->position;
	cap_top = add_v(cylinder->position, multiply_v(cylinder->orientation,
				cylinder->height));
	t_cap_bottom = dot_product(subtract_v(cap_bottom, ray.origin),
			cylinder->orientation) / dot_product(ray.direction,
			cylinder->orientation);
	t_cap_top = dot_product(subtract_v(cap_top, ray.origin),
			cylinder->orientation) / dot_product(ray.direction,
			cylinder->orientation);
	if (t_cap_bottom > DBL_EPSILON && t_cap_bottom < *prev_t
		&& (t_cap_bottom < t_cap_top || t_cap_top < 0))
	{
		p = get_inter(ray, t_cap_bottom);
		if (vector_length(subtract_v(p, cap_bottom)) <= cylinder->diam / 2)
			return (cylinder->is_caps = BOTTOM, t_cap_bottom);
	}
	if (t_cap_top > DBL_EPSILON && t_cap_top < *prev_t)
	{
		p = get_inter(ray, t_cap_top);
		if (vector_length(subtract_v(p, cap_top)) <= cylinder->diam / 2)
			return (cylinder->is_caps = TOP, t_cap_top);
	}
	return (0);
}

void	get_t_cylinder(t_cylinder *cylinder, t_ray ray, double *t1, double *t2)
{
	t_vector	oc;
	t_vector	d;

	double a, b, discriminant;
	oc = subtract_v(ray.origin, cylinder->position);
	d = subtract_v(ray.direction, multiply_v(cylinder->orientation,
				dot_product(ray.direction, cylinder->orientation)));
	oc = subtract_v(oc, multiply_v(cylinder->orientation, dot_product(oc,
					cylinder->orientation)));
	a = dot_product(d, d);
	b = 2.0 * dot_product(d, oc);
	discriminant = b * b - 4.0 * a * (dot_product(oc, oc) - pow(cylinder->diam
				/ 2.0, 2));
	*t1 = DBL_MAX;
	*t2 = DBL_MAX;
	if (discriminant >= 0)
		retrieve_t(a, b, discriminant, t1, t2);
}