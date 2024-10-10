#include "mini_rt.h"

t_vector	cross_product(t_vector one, t_vector two)
{
	t_vector	result;

	result.x = one.y * two.z - one.z * two.y;
	result.y = one.z * two.x - one.x * two.z;
	result.z = one.x * two.y - one.y * two.x;
	return (result);
}
