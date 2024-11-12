#include "mini_rt.h"

float	get_max_float(float *t, int size)
{
	float	max_t;
	int		i;

	i = 0;
	max_t = t[0];
	while (++i < size)
	{
		if (t[i] > max_t)
			max_t = t[i];
	}
	return (max_t);
}

float	get_min_float(float *t, int size)
{
	float	min_t;
	int		i;

	i = 0;
	min_t = t[0];
	while (++i < size)
	{
		if (t[i] < min_t && t[i] > 0)
			min_t = t[i];
	}
	return (min_t);
}