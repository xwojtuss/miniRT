#include "mini_rt.h"
#include "phong_reflection.h"

/*
returns an integer value of the color
*/
int	phong_reflection(t_vector normal_vector, t_vector ray_direction, t_scene scene)
{
	/*
    
    The wikipedia article specifies the light as only one value
    but in our program it has a brightness and a colour (i think as bonus)
    how would we calculate it?
    we need the direction to all the lights
    we need the normals, they are passed as parameters
    we need the value for the lights (again, single value from brightness and colour)
    we need the perfectly reflected ray from light = 2(intersection point to lights * normal)normal - intersection point to lights
    we need the direction to the camera
    shininess of material as a constant or a map of some sorts
    jesus the article is not that readable
    it makes sense but only in my mind, how tf to implement it ?!?1
    
    */
}