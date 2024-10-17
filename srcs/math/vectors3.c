#include "mini_rt.h"

t_vector	cross_product(t_vector one, t_vector two)
{
	t_vector	result;

	result.x = one.y * two.z - one.z * two.y;
	result.y = one.z * two.x - one.x * two.z;
	result.z = one.x * two.y - one.y * two.x;
	return (result);
}

t_vector	rotate_on_x(t_vector vector)
{
	t_vector	result;

	result.x = vector.x;
	result.y = vector.y * cos(ROTATE_DEGREE) - vector.z * sin(ROTATE_DEGREE);
	result.z = vector.y * sin(ROTATE_DEGREE) + vector.z * cos(ROTATE_DEGREE);
	return (result);
}

t_vector	rotate_on_y(t_vector vector)
{
	t_vector	result;

	result.x = vector.x * cos(ROTATE_DEGREE) + vector.z * sin(ROTATE_DEGREE);
	result.y = vector.y;
	result.z = -vector.x * sin(ROTATE_DEGREE) + vector.z * cos(ROTATE_DEGREE);
	return (result);
}

t_vector	rotate_on_z(t_vector vector)
{
	t_vector	result;

	result.x = vector.x * cos(ROTATE_DEGREE) - vector.y * sin(ROTATE_DEGREE);
	result.y = vector.x * sin(ROTATE_DEGREE) + vector.y * cos(ROTATE_DEGREE);
	result.z = vector.z;
	return (result);
}

t_vector	rotate_vector(float m[3][3], t_vector v)
{
	return ((t_vector){.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
		.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z, .z = m[2][0] * v.x
		+ m[2][1] * v.y + m[2][2] * v.z});
}
